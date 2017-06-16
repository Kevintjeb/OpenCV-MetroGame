#include "Passengers.h"



Passengers::Passengers(float x, float z, Passengers::Priority people) : x(x), z(z), people(people)
{
	switch (people)
	{
	case Priority::LOW:
		max = 6;
		break;
	case Priority::HIGH:
		max = 8;
		break;
	case Priority::EMERENCY:
		max = 12;
		break;
	default:
		break;
	}
}


Passengers::~Passengers()
{
}


//draw passangers and destination
void Passengers::draw()
{
	switch (people)
	{
		case Priority::LOW:
			DrawCircle(x, z, radius1, color);
			DrawCircle(x, z, radius2, color);
			break;
		case Priority::HIGH:
			DrawCircle(x, z, radius1, color);
			DrawCircle(x, z, radius2, color);
			DrawCircle(x, z, radius3, color);
			break;
		case Priority::EMERENCY:
			DrawCircle(x, z, radius1, color);
			DrawCircle(x, z, radius2, color);
			DrawCircle(x, z, radius3, color);
			DrawCircle(x, z, radius4, color);
			break;
		default:
			break;
	}
}


void Passengers::update()
{
	radius1 += step;
	radius2 += step;
	radius3 += step;
	radius4 += step;

	if (radius1 > max)
		radius1 = 0;
	if (radius2 > max)
		radius2 = 0;
	if (radius3 > max)
		radius3 = 0;
	if (radius4 > max)
		radius4 = 0;
}

void Passengers::updatePriority(Priority newPriority)
{
	people = newPriority;
	switch (people)
	{
	case Priority::LOW:
		max = 6;
		break;
	case Priority::HIGH:
		max = 8;
		break;
	case Priority::EMERENCY:
		max = 10;
		break;
	default:
		break;
	}
	radius1 = 0;
	radius2 = 3;
	radius3 = 6;
	radius4 = 9;

}

Passengers::Priority Passengers::getPriority()
{
	return people;
}

void Passengers::DrawCircle(float cx, float cy, float r, Color color)
{
	glBegin(GL_LINE_LOOP);
	glEnable(GL_COLOR);
	glColor3f(color.r, color.g, color.b);
	for (int ii = 0; ii < 360; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(360);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex3f(x + cx, 4.5f, y + cy);//output vertex

	}
	glEnd();
	glDisable(GL_COLOR);
}
