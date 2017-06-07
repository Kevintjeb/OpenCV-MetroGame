#pragma once
#include "Vect.h"
#include <GL\freeglut.h>
#include <math.h>
#include <vector>
#include "VertexClass.h"

class Passengers
{
public:
	enum class Priority
	{
		LOW, HIGH, EMERENCY
	};

	Passengers(float x, float y, Passengers::Priority people);
	~Passengers();
	void draw();
	void update();
	void updatePriority(Priority newPriority);
	Priority getPriority();

private:
	//TODO do something with destination
	float x, z, radius1 = 0, radius2 = 3, radius3 = 6, step = 0.2f, max = 10.0f, destinationX, destinationZ;
	Passengers::Priority people;
	void DrawCircle(float cx, float cy, float r, Vec3f color);
	void DrawArrow(float x, float z, Vec3f color);
};

