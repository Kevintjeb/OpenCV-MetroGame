#include "MetroTrain.h"
#include <cmath>

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

inline std::tuple<Vec2f, float> mg_gameLogic::MetroTrain::findComplementaryPositionAndDistance(float pos)
{
	
}

MetroTrain::MetroTrain(Line& line, float init_pos, State state, int size) :
	line(line), line_pos(init_pos), state(state), size(size), trains(0)
{
	
}
float totalTimeSpend = 0;
float speeddif = 0;
int stopState = 0;	//0= normaal rijden // 1 = gestopt // 2 = optrekken 
int oldIndex = -1;  //zorgt voor de eerste check zodat niet meerdere keren stopt.
float mg_gameLogic::MetroTrain::getSpeed(float elapsedTime)
{

	int index = line.getIndexByPosition(line_pos);
	totalTimeSpend += elapsedTime;
	for (pair<int, MetroStation> p : line.getStationPosistion())
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

	line_pos += getSpeed(elapsedTime) * (state == State::FORWARD ? 1 : -1);

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

void mg_gameLogic::MetroTrain::reposistion(Line& line)
{
	Vec2f trainPosition(trains[0]->position.x, trains[0]->position.z);
	int index = 0;
	float minimumDistance = 9999999;
	float distance;
	for (int i = 0; i < line.size(); i++) 
	{
		if (trainPosition.distance(line[i]) < minimumDistance) 
		{
			index = i;
			distance = line.getDistance(i);
		}
	}
	int seconIndex=0;
	if (index > 0) 
	{
		if (trainPosition.distance(line[index - 1]) > trainPosition.distance(line[index + 1])) 
		{
			seconIndex = index + 1;
		}
		else { seconIndex = index - 1; }
	}
	else 
	{
		seconIndex = 1;
	}
	Vec2f newVec = line[index] - line[seconIndex];

}
