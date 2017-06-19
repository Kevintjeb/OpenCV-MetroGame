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

	Passengers(float x, float y, Passengers::Priority people);
	~Passengers();
	void draw();
	void update();
	void updatePriority(Priority newPriority);
	Priority getPriority();

private:
	Color color = Color(0.0f,0.0f,0.0f);
	float x, z, radius1 = 0, radius2 = 3, radius3 = 6, radius4 = 9, step = 0.05f, max = 10.0f;
	Passengers::Priority people;
	void DrawCircle(float cx, float cy, float r, Color color);
};

