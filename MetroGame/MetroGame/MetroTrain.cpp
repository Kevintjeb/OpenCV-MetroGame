#include "MetroTrain.h"
#include <cmath>
#include <limits>

using namespace mg_gameLogic;
using namespace std;

inline Vec2f MetroTrain::pos2d_from_pos(float pos)
{
	int index = line.getIndexByPosition(pos);

	Vec2f far = line[index+1], close = line[index];

	Vec2f normal(close.x - far.x, close.y - far.y);
	float mag = sqrt(normal.x*normal.x + normal.y*normal.y);
	normal.x /= mag;
	normal.y /= mag;

	float dist = line.getDistance(index) - pos;
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
		if (pos >= line.getDistance(line.size() - 1))
		{
			state = State::BACKWARD;
			return line.getDistance(line.size() - 1) - (size*train_length);
		}
		break;
	case State::BACKWARD:
		if (pos <= 0)
		{
			state = State::FORWARD;
			return size*train_length;
		}
		break;
	}

	return pos;
}

// @TODO optimize away, this version is written for clarity and is not efficient in any way shape or form
inline std::tuple<Vec2f, float> mg_gameLogic::MetroTrain::findComplementaryPositionAndDistance(float pos)
{
	int index = line.getIndexByPosition(pos) + (state == State::FORWARD ? 0 : +1);
	
	// some lamdas to ensure the rest of the code can ignore direction
	const auto get_dist = [this](int i)->float {return state == State::FORWARD ? 
												line.getDistance(i) : 
												line.getDistance(line.size() - 1) - line.getDistance(i); 
											};
	const auto con_pos = [this](float pos)->float {return state == State::FORWARD ?
													pos :
													line.getDistance(line.size()-1) - pos
												; };
	const auto next = [this](int c)->int {return state == State::FORWARD ? c + 1 : c - 1; };
	const auto prev = [this](int c)->int {return state == State::FORWARD ? c - 1 : c + 1; };
	const auto is_invalid = [this](int c)->bool {return state == State::FORWARD ?
												c > line.size() - 1 || c < 0 :
												c <= 0 || c > line.size()
											; };
	const auto back = [this]()->int {return state == State::FORWARD ? 0 : line.size() - 1; };

	const Vec2f B = line[index];
	const Vec2f A = line[next(index)];
	const Vec2f P = (A - B).unit() * (pos - get_dist(index)) + B;
	
	if ((P - B).magnitude() >= train_length) // we check if P' is between P and line[index]
	{
		const float dist_from_B = pos - get_dist(index) - train_length;
		const Vec2f P_comp((P - B).unit() * dist_from_B + B);
		return tuple<Vec2f, float>(P_comp, con_pos( dist_from_B + get_dist(index)));
	}
	else // we go over the previus line pieces
	{
		for (index = prev(index); is_invalid(index) == false; index = prev(index))
		{
			const Vec2f L = line[index];

			// if L is with the circle and next(L) is per definition, P' can't be on LP
			if ((L - P).magnitude() < train_length) continue;

			const Vec2f PL(L - P);

			// since we use the slope often we precompute it
			const float s = PL.y / PL.x;

			// we calculate the abc for the abc formula
			const float a = 1 + s*s;
			const float b = -2 * (P.x - s*L.y + s*P.y + s*s*L.x);
			const float c = P.x*P.x + powf(L.y - P.y - s*L.x, 2) - train_length*train_length;

			// we calculate the x's of the intersection points
			const float x_1 = (-b + sqrtf(b*b - 4 * a*c)) / 2 * a;
			const float x_2 = (-b - sqrtf(b*b - 4 * a*c)) / 2 * a;

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

			return ret;
		}

		// if the point isn't on the line, we return a vector of [-∞, -∞] and a distance of -∞
		return pair<Vec2f, float>({ numeric_limits<float>::infinity(), numeric_limits<float>::infinity() }, numeric_limits<float>::infinity());
	}
}

MetroTrain::MetroTrain(const Line& line, float init_pos, State state, int size) :
	line(line), line_pos(init_pos), state(state), size(size), trains(0)
{
	
}

void MetroTrain::Recalculate(float elapsedTime)
{
	// ensuring we have the correct size
	if (trains.size() < size) // if we have to little trains
	{
		int diff = size - trains.size(); // we need 'diff' new trains
		for (int i = 0; i < diff; ++i) // we allocate new Renderables 
			trains.push_back(allocate_renderable(Renderable(METRO, Vec3f(0, -92.0f, 0), 0.0f, Vec3f(0, 1, 0), Vec3f(2, 2, 2))));
	}
	else if (trains.size() > size) // if we have to many trains
	{
		for (int i = trains.size() - 1; i >= size; --i) // from back to front
		{
			deallocate_renderable(trains[i]); // remove it from the list
			trains.pop_back(); // remove it from the vector
		}
	}

	line_pos += elapsedTime*speed * (state == State::FORWARD ? 1 : -1);

	line_pos = checkAndSetPosRange(line_pos);

	auto npos = pos2d_from_pos(line_pos);
	trains[0]->position.x = npos.x*50;
	trains[0]->position.z = npos.y*50;
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