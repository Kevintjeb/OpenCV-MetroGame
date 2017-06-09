#include "MetroTrain.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>
#include <iostream>

using namespace mg_gameLogic;
using namespace std;

inline GameLogic::Vec2f MetroTrain::pos2d_from_pos1d(float pos)
{
	// since the position is on a vector between two points, we first get the points

	int index = line->getIndexByPosition(pos); 

	GameLogic::Vec2f far = line->operator[](index+1), close = line->operator[](index);

	// we then calculate the vector between them, and then normalize it
	GameLogic::Vec2f normal(close.x - far.x, close.y - far.y);
	float mag = sqrt(normal.x*normal.x + normal.y*normal.y);
	normal.x /= mag;
	normal.y /= mag;

	// we then calculate the length of the vector, and scale the vector with it
	float dist = line->getDistance(index) - pos;
	normal.x *= dist;
	normal.y *= dist;

	GameLogic::Vec2f pos2d(close.x + normal.x, close.y + normal.y);
	return pos2d;
}

inline float MetroTrain::checkAndSetPosRange(float pos)
{

	switch (state)
	{
	case State::FORWARD:
		if (pos >= line->getDistance(line->size() - 1)) // if we are off the line
		{
			state = State::BACKWARD; // we revert our direction
			// and set our new position, base + total train length
			return line->getDistance(line->size() - 1) - ((size)*(train_length+train_spacing) - train_spacing);
		}
		break;
	case State::BACKWARD:
		if (pos <= 0) // if we are off the line 
		{
			state = State::FORWARD; // we revert our position
			// and set our new psoition, base + total tran length
			return (size)*(train_length+train_spacing) - train_spacing;
		}
		break;
	}

	return pos;
}

// @TODO optimize away, this version is written for clarity and is not efficient in any way shape or form
inline std::pair<GameLogic::Vec2f, float> mg_gameLogic::MetroTrain::findComplementaryPositionAndDistance(float pos)
{
	int index = line->getIndexByPosition(pos) + (state == State::FORWARD ? 0 : +1);
	
	// some lamdas to ensure the rest of the code can ignore direction
	const auto get_dist = [this](int i)->float {return state == State::FORWARD ? 
												line->getDistance(i) : 
												line->getDistance(line->size() - 1) - line->getDistance(i); 
											};
	const auto con_pos = [this](float pos)->float {return state == State::FORWARD ?
													pos :
													line->getDistance(line->size()-1) - pos
												; };
	const auto next = [this](int c)->int {return state == State::FORWARD ? c + 1 : c - 1; };
	const auto prev = [this](int c)->int {return state == State::FORWARD ? c - 1 : c + 1; };
	const auto is_invalid = [this](int c)->bool {return state == State::FORWARD ?
												c > line->size() - 1 || c < 0 :
												c <= 0 || c > line->size()-1
											; };
	const auto back = [this]()->int {return state == State::FORWARD ? 0 : line->size() - 1; };

	const GameLogic::Vec2f B = line->operator[](index);
	const GameLogic::Vec2f A = line->operator[](next(index));
	const GameLogic::Vec2f P = (A - B).unit() * (con_pos(pos) - get_dist(index)) + B;
	
	if ((P - B).magnitude() >= train_length) // we check if P' is between P and line[index]
	{
		const float dist_from_B = con_pos(pos) - get_dist(index) - train_length;
		const GameLogic::Vec2f P_comp((P - B).unit() * dist_from_B + B);
		return pair<GameLogic::Vec2f, float>(P_comp, con_pos( dist_from_B + get_dist(index)));
	}
	else // we go over the previus line pieces
	{
		for (index = prev(index); is_invalid(index) == false; index = prev(index))
		{
			const GameLogic::Vec2f L = line->operator[](index);

			// if L_i is with the circle then P' can't be on L_i L_i+1
			if ((L - P).magnitude() < train_length) continue;

#ifdef _DEBUG
			if ((P - line->operator[](next(index))).magnitude() > train_length)
				throw "Invalid line";
#endif

			const GameLogic::Vec2f LV(line->operator[](next(index)) - L);


			// since we use the slope often we precompute it
			const float s = LV.y / LV.x;

			// we calculate the abc for the abc formula
			const float a = 1 + s*s;
			const float b = -2 * (P.x - s*L.y + s*P.y + s*s*L.x);
			const float c = P.x*P.x + powf(L.y - P.y - s*L.x, 2) - train_length*train_length;

			// we calculate the x's of the intersection points
			const float x_1 = (-b + sqrtf(b*b - 4 * a*c)) / (2 * a);
			const float x_2 = (-b - sqrtf(b*b - 4 * a*c)) /( 2 * a);

			// we calculate the y's of the intersection points
			const float y_1 = s*(x_1 - L.x) + L.y;
			const float y_2 = s*(x_2 - L.x) + L.y;

			// we convert the intersection points to positions
			const GameLogic::Vec2f I_1(x_1, y_1);
			const GameLogic::Vec2f I_2(x_2, y_2);

			// we callculate the distance between L and the intersection points
			const float dist_1 = (I_1 - L).magnitude();
			const float dist_2 = (I_2 - L).magnitude();

			// we select the closest intersection point
			using Ret = pair<GameLogic::Vec2f, float>;
			Ret ret = dist_1 < dist_2 ? Ret(I_1, dist_1) : Ret(I_2, dist_2);
			ret.second += get_dist(index);
			ret.second = con_pos(ret.second);

			//if ((ret.first - P).magnitude() >= train_length * 1.1f)
			//	exit(-1);

			return ret;
		}

		// if the point isn't on the line, we return a vector of [NaN, NaN] and a distance of NaN
		return pair<GameLogic::Vec2f, float>({ NAN, NAN }, NAN);
	}
}

MetroTrain::MetroTrain(Line* line, float init_pos, State state, int size) :
	line(line), line_pos(init_pos), state(state), size(size), trains(0)
{
	
}

float mg_gameLogic::MetroTrain::getSpeed(float elapsedTime)
{

	int index = line->getIndexByPosition(line_pos);
	totalTimeSpend += elapsedTime;
	for (pair<int, MetroStation> p : line->getStationIndexes())
	{
		int pcompare = p.first - (state == State::FORWARD ? 1 : 2);				// -1 for the first point -2 for reverse
		if ((pcompare == index /*|| (p.first+1)==index*/) && stopState == 0 && oldIndex != index)	//Nextpoint = currentPoint
		{
			//Decrease speed while it's greater than 0
			if (speed > 0) {
				speed -= 0.01;
			}
		}
		//Preventing the train from going in reverse
		if (speed < 0) {
			//Time Resetten when the train stopped
			totalTimeSpend = 0;
			stopState = 1;		//confirm that the train stopped
			oldIndex = index;
			speed = 0;
		}
		if (totalTimeSpend > 3 && stopState == 1)
		{
			stopState = 2;		//Permission to continue
		}
		//Opstrekken
		if (stopState == 2)
		{
			if (speed <= 0.5f)
			{
				speed += 0.1;
			}
		}//Preventing the speed from going over the safetylimit
		if (speed >= 0.5f)
		{
			stopState = 0;
			speed = 0.5f;
		}
		//preventing from stopping again for the same station.
		if (index != pcompare)
		{
			oldIndex = -1;
		}

		//DEBUG for LINE SWITCHING

		//if (totalTimeSpend > 5 && !called) 
		//{
		//	called = true;
		//	reposistion(new Line({ { { -1.0f,0.25f },{ 0,0.25f },{ 1, 0.25f } } }, { { MetroStation(Vec2f(0.5f,0.25f)) } }));
		//	totalTimeSpend = 0;
		//}
	}
	return speed*elapsedTime;	//keeping speed the same
}

void MetroTrain::Recalculate(float elapsedTime)
{
	// ensuring we have the correct size
	if (trains.size() < size) // if we have to little trains
	{
		int diff = size - trains.size(); // we need 'diff' new trains
		for (int i = 0; i < diff; ++i) // we allocate new Renderables 
			trains.push_back(allocate_renderable(Renderable("models/Metro/metro.obj", GameLogic::Vec3f(0, -90.8f, 0), 0.0f, GameLogic::Vec3f(0, 1, 0), GameLogic::Vec3f(scale, scale, scale))));
	}
	else if (trains.size() > size) // if we have to many trains
	{
		for (int i = trains.size() - 1; i >= size; --i) // from back to front
		{
			deallocate_renderable(trains[i]); // remove it from the list
			trains.pop_back(); // remove it from the vector
		}
	}

	line_pos += getSpeed(elapsedTime) * (state == State::FORWARD ? 1 : -1);

	line_pos = checkAndSetPosRange(line_pos);

	// we initialize tmp_line_pos, so we can do our carrt update in one loop
	auto tmp_line_pos = line_pos;

	// @TODO to prevent stutering, we could attemt to use the train_spacing as a spring

	for (int i = 0; i < size; i++) // we go over all trains
	{
		auto npos = pos2d_from_pos1d(tmp_line_pos); // we convert our position from 1 to 2 D
		auto cpos = findComplementaryPositionAndDistance(tmp_line_pos); // we calculate the second position

		if (isnan(cpos.second)) // @TODO this is a temporary fix, but this should never happen during corners
		{
			if (__debug_output) cout << "caridge " << i << " is not on the line, breaking" << endl;
			break;
		}

		// we set the position, and convert it to world space
		trains[i]->position.x = npos.x * 50;
		trains[i]->position.z = npos.y * 50;

		// we calculate the angle of the train, and set it
		auto y = (npos - cpos.first).y;
		auto x = (npos - cpos.first).x;
		auto at = atan2f(x, y);
		auto conv = at * 180.f / M_PI - 90;
		trains[i]->angle = conv;

		// we set the 1D position of the next train
		tmp_line_pos = cpos.second + (state == State::FORWARD ? -train_spacing : train_spacing);
	}
}

int MetroTrain::get_size() const
{
	return size;
}

void MetroTrain::resize(int nsize)
{
	if (nsize > 0 && nsize <= max_size)
		size = nsize;
}

void mg_gameLogic::MetroTrain::reposistion(Line* line)
{
	GameLogic::Vec2f trainPosition = pos2d_from_pos1d(line_pos);		//Get Vector for current position
	int index = 0;		
	float minimumDistance = 9999999;
	float trainDistance;

	for (int i = 0; i < line->size(); i++)				//Search through all the points of the new line to find the one closest to the train
	{
		if (trainPosition.distance(line->operator[](i)) < minimumDistance)
		{
			index = i;
			trainDistance = line->getDistance(i);
			minimumDistance = trainPosition.distance(line->operator[](i));
		}
	}
	int secondIndex=0;
	if (index > 0)										//Zoek het op een na dichtsbijzijnde punt. (kon ff geen engels)
	{
		if (trainPosition.distance(line->operator[](index-1)) > trainPosition.distance(line->operator[](index+1)))
		{
			secondIndex = index + 1;
		}
		else { secondIndex = index - 1; }
	}
	//IF second index cannot be found it's zero.
	else 
	{
		secondIndex = 1;
	}
	trainPosition = line->operator[](index)- trainPosition;					//Get the trainsposition in a local vector
	GameLogic::Vec2f vectorB = line->operator[](index) - line->operator[](secondIndex); //Vector A is train Vector
	GameLogic::Vec2f vectorA1((vectorB*(trainPosition.dotProduct(vectorB)))/(vectorB.dotProduct(vectorB)));

	//Calculate the distance based on the length of the vector and the second point
	if (secondIndex > index) 
	{
		trainDistance +=  vectorA1.magnitude();
	}
	else 
	{
		trainDistance -=  vectorA1.magnitude();
	}
	line_pos = trainDistance;

	//set the new line.
	this->line = line;
}
