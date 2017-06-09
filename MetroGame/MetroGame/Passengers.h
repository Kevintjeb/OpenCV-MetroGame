#pragma once
#include "Vect.h"
#include <GL\freeglut.h>
#include <math.h>
#include <vector>
#include "VertexClass.h"
#include <string>
#include "Font.h"

#define MAXCOUNTER 20

class Passengers
{
public:
	enum class Priority
	{
		LOW, HIGH, EMERENCY
	};

	Passengers(float x, float y, Passengers::Priority people, int nmb, float destX, float z);
	~Passengers();
	void draw();
	void update();
	void updatePriority(Priority newPriority);
	Priority getPriority();

private:
	//TODO do something with destination
	int destCounter = 0;
	bool drawDest = true;
	GameLogic::Vec3f color;
	float x, z, radius1 = 0, radius2 = 3, radius3 = 6, radius4 = 9, step = 0.2f, max = 10.0f, destinationX, destinationZ;
	Passengers::Priority people;
	void DrawCircle(float cx, float cy, float r, GameLogic::Vec3f color);
	void DrawDestination(float x, float z, GameLogic::Vec3f color);
};

