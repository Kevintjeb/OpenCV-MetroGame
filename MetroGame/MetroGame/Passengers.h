#pragma once
#include "Color.h"
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

	Passengers(float x, float y, Passengers::Priority people, float destX, float z);
	~Passengers();
	void draw();
	void update();
	void updatePriority(Priority newPriority);
	Priority getPriority();

private:
	//TODO do something with destination
	int destCounter = 0;
	bool drawDest = true;
	Color color = Color(0.0f,0.0f,0.0f);
	float x, z, radius1 = 0, radius2 = 3, radius3 = 6, radius4 = 9, step = 0.05f, max = 10.0f, destinationX, destinationZ;
	Passengers::Priority people;
	void DrawCircle(float cx, float cy, float r, Color color);
	void DrawDestination(float x, float z, Color color);
};

