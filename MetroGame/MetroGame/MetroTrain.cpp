#include "MetroTrain.h"
#include <cmath>
#include <limits>
#include <iostream>

using namespace mg_gameLogic;
using namespace std;

inline Vec2f MetroTrain::pos2d_from_pos(float pos)
{
	int index = line->getIndexByPosition(pos);

	Vec2f far = line->operator[](index+1), close = line->operator[](index);

	Vec2f normal(close.x - far.x, close.y - far.y);
	float mag = sqrt(normal.x*normal.x + normal.y*normal.y);
	normal.x /= mag;
	normal.y /= mag;

	float dist = line->getDistance(index) - pos;
	normal.x *= dist;
	normal.y *= dist;

	Vec2f pos2d(close.x + normal.x, close.y + normal.y);
	return pos2d;
}

inline float MetroTrain::checkAndSetPosRange(float pos)
{
	switch (state)
	{
	case State::FORWARD:
		if (pos >= line->getDistance(line->size() - 1))
		{
			state = State::BACKWARD;
			return line->getDistance(line->size() - 1) - ((size-1)*(train_length+train_spacing));
		}
		break;
	case State::BACKWARD:
		if (pos <= 0)
		{
			state = State::FORWARD;
			return (size-1)*(train_length+train_spacing);
		}
		break;
	}

	return pos;
}

// @TODO optimize away, this version is written for clarity and is not efficient in any way shape or form
inline std::pair<Vec2f, float> mg_gameLogic::MetroTrain::findComplementaryPositionAndDistance(float pos)
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
												c <= 0 || c > line->size()
											; };
	const auto back = [this]()->int {return state == State::FORWARD ? 0 : line->size() - 1; };

	const Vec2f B = line->operator[](index);
	const Vec2f A = line->operator[](next(index));
	const Vec2f P = (A - B).unit() * (con_pos(pos) - get_dist(index)) + B;
	
	if ((P - B).magnitude() >= train_length) // we check if P' is between P and line[index]
	{
		const float dist_from_B = con_pos(pos) - get_dist(index) - train_length;
		const Vec2f P_comp((P - B).unit() * dist_from_B + B);
		return pair<Vec2f, float>(P_comp, con_pos( dist_from_B + get_dist(index)));
	}
	else // we go over the previus line pieces
	{
		for (index = prev(index); is_invalid(index) == false; index = prev(index))
		{
			const Vec2f L = line->operator[](index);

			// if L_i is with the circle then P' can't be on L_i L_i+1
			if ((L - P).magnitude() < train_length) continue;

#ifdef _DEBUG
			if ((P - line->operator[](next(index))).magnitude() > train_length)
				throw "Invalid line";
#endif

			const Vec2f LV(line->operator[](next(index)) - L);


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
			const Vec2f I_1(x_1, y_1);
			const Vec2f I_2(x_2, y_2);

			// we callculate the distance between L and the intersection points
			const float dist_1 = (I_1 - L).magnitude();
			const float dist_2 = (I_2 - L).magnitude();

			// we select the closest intersection point
			using Ret = pair<Vec2f, float>;
			Ret ret = dist_1 < dist_2 ? Ret(I_1, dist_1) : Ret(I_2, dist_2);
			ret.second += get_dist(index);
			ret.second = con_pos(ret.second);

			//if ((ret.first - P).magnitude() >= train_length * 1.1f)
			//	exit(-1);

			return ret;
		}

		// if the point isn't on the line, we return a vector of [NaN, NaN] and a distance of NaN
		return pair<Vec2f, float>({ NAN, NAN }, NAN);
	}
}

MetroTrain::MetroTrain(Line* line, float init_pos, State state, int size) :
	line(line), line_pos(init_pos), state(state), size(size), trains(0)
{
	
}

float totalTimeSpend = 0;
float speeddif = 0;
int stopState = 0;	//0= normaal rijden // 1 = gestopt // 2 = optrekken 
int oldIndex = -1;  //zorgt voor de eerste check zodat niet meerdere keren stopt.
bool called = false;

float mg_gameLogic::MetroTrain::getSpeed(float elapsedTime)
{

	int index = line->getIndexByPosition(line_pos);
	totalTimeSpend += elapsedTime;
	for (pair<int, MetroStation> p : line->getStationPosistion())
	{
		int pcompare = p.first - (state == State::FORWARD ? 1 : 2);				// -1 voor eerste punt -2 voor achteruit want fuck flobo
		if ((pcompare == index /*|| (p.first+1)==index*/)&& stopState==0 && oldIndex != index)	//Eerstvolgende punt is het huidige punt
		{
			//snelheid verminderen als groter dan 0
			if (speed > 0) {
				speed -= 0.01;
			}
		}
		//bevestigen dat de snelheid niet negatief wordt.
		if (speed < 0) {
			//Tijd resetten zodat stilstaan bij 0 begint.
			totalTimeSpend = 0;
			stopState = 1;		//bevesigen dat de trein stil staat.
			oldIndex = index;
			speed = 0; }
		if (totalTimeSpend > 3 && stopState ==1) 
		{
			stopState = 2;		//Toestemming voor optrekken
		}
		//Opstrekken
		if ( stopState ==2)
		{
			if (speed <= 0.5f) 
				{
					speed += 0.1;
				}
		}//Voorkomen dat snelheid boven max gaat.
		if (speed >= 0.5f) 
		{
			stopState = 0;
			speed = 0.5f;
		}
		//zorgen dat stop niet meerdere keren per traject gebeurt.
		if (index != pcompare) 
		{
			oldIndex = -1;
		}
	}
	

	//snelheid keer tijd zodat gelijk blijft.
	return speed*elapsedTime;
}

void MetroTrain::Recalculate(float elapsedTime)
{
	// ensuring we have the correct size
	if (trains.size() < size) // if we have to little trains
	{
		int diff = size - trains.size(); // we need 'diff' new trains
		for (int i = 0; i < diff; ++i) // we allocate new Renderables 
			trains.push_back(allocate_renderable(Renderable(METRO, Vec3f(0, -92.0f, 0), 0.0f, Vec3f(0, 1, 0), Vec3f(1, 1, 1))));
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

	


	auto tmp_line_pos = line_pos;

	for (int i = 0; i < size; i++)
	{
		auto npos = pos2d_from_pos(tmp_line_pos);
		auto cpos = findComplementaryPositionAndDistance(tmp_line_pos);

		if (isnan(cpos.second)) break;

		trains[i]->position.x = npos.x * 50;
		trains[i]->position.z = npos.y * 50;
		auto y = (npos - cpos.first).y;
		auto x = (npos - cpos.first).x;
		auto at = atan2f(x, y);
		auto conv = at * 180.f / 3.14159265358979323846f - 90;
		trains[i]->angle = conv;

		tmp_line_pos = cpos.second + (state == State::FORWARD ? -train_spacing : train_spacing);
	}

	//trains[1]->position.x = cpos.first.x * 50;
	//trains[1]->position.z = cpos.first.y * 50;
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
	Vec2f trainPosition = pos2d_from_pos(line_pos);		//Get Vector for current position
	int index = 0;		
	float minimumDistance = 9999999;
	float trainDistance;

	for (int i = 0; i < line->size(); i++)				//Search through all the points of the new line
	{
		if (trainPosition.distance(line->operator[](i)) < minimumDistance)
		{
			index = i;
			trainDistance = line->getDistance(i);
			minimumDistance = trainPosition.distance(line->operator[](i));
		}
	}
	int seconIndex=0;
	if (index > 0) 
	{
		if (trainPosition.distance(line->operator[](index-1)) > trainPosition.distance(line->operator[](index+1)))
		{
			seconIndex = index + 1;
		}
		else { seconIndex = index - 1; }
	}
	else 
	{
		seconIndex = 1;
	}
	trainPosition = line->operator[](index)- trainPosition;
	Vec2f vectorB = line->operator[](index) - line->operator[](seconIndex); //Vector A is train Vector
	Vec2f vectorA1((vectorB*(trainPosition.dotProduct(vectorB)))/(vectorB.dotProduct(vectorB)));

	if (seconIndex > index) 
	{
		trainDistance +=  vectorA1.magnitude();
	}
	else 
	{
		trainDistance -=  vectorA1.magnitude();
	}
	line_pos = trainDistance;

	
	this->line = line;
}
