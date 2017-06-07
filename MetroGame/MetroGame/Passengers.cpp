#include "Passengers.h"



Passengers::Passengers(float x, float z, Passengers::Priority people, int number, float destX, float destY) : x(x), z(z), people(people), destinationX(destX), destinationZ(destY)
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

	switch (number)
	{
	case 0:
		color = Vec3f(1.0f, 0.5f, 0.0f);
		break;
	case 1:
		color = Vec3f(0.0f, 0.3f, 1.0f);
		break;
	case 2:
		color = Vec3f(1.0f, 1.0f, 0.0f);
		break;
	case 3:
		color = Vec3f(1.0f, 0.0f, 1.0f);
		break;
	case 4:
		color = Vec3f(1.0f, 0.5f, 0.5f);
		break;
	case 5:
		color = Vec3f(0.0f, 1.0f, 1.0f);
		break;
	case 6:
		color = Vec3f(0.5f, 0.5f, 1.0f);
		break;
	case 7:
		color = Vec3f(0.5f, 1.0f, 0.5f);
		break;
	case 8:
		color = Vec3f(1.0f, 0.3f, 0.0f);
		break;
	case 9:
		color = Vec3f(0.0f, 1.0f, 0.3f);
		break;
	case 10:
		color = Vec3f(0.3f, 0.0f, 1.0f);
		break;
	default:
		color = Vec3f(0.3f, 0.3f, 0.3f);
		break;
	}
}


Passengers::~Passengers()
{
}

void Passengers::draw()
{
	switch (people)
	{
		case Priority::LOW:
			DrawCircle(x, z, radius1, color);
			DrawCircle(x, z, radius2, color);
			if(drawDest)
				DrawDestination(destinationX, destinationZ, color);
			break;
		case Priority::HIGH:
			DrawCircle(x, z, radius1, color);
			DrawCircle(x, z, radius2, color);
			DrawCircle(x, z, radius3, color);
			if (drawDest)
				DrawDestination(destinationX, destinationZ, color);
			break;
		case Priority::EMERENCY:
			DrawCircle(x, z, radius1, color);
			DrawCircle(x, z, radius2, color);
			DrawCircle(x, z, radius3, color);
			DrawCircle(x, z, radius4, color);
			if (drawDest)
				DrawDestination(destinationX, destinationZ, color);
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

	destCounter++;
	if (destCounter > MAXCOUNTER)
	{
		drawDest = !drawDest;
		destCounter = 0;
	}
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

void Passengers::DrawCircle(float cx, float cy, float r, Vec3f color)
{
	glBegin(GL_LINE_LOOP);
	glEnable(GL_COLOR);
	glColor3f(color.x, color.y, color.z);
	for (int ii = 0; ii < 360; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(360);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex3f(x + cx, 9.0f, y + cy);//output vertex

	}
	glEnd();
	glDisable(GL_COLOR);
}

void Passengers::DrawDestination(float x, float z, Vec3f color)
{
	glEnable(GL_COLOR);
	glPointSize(30.0f);
	glBegin(GL_POINTS);
	glColor3f(color.x, color.y, color.z);
	glVertex3f(x, 9.5f, z);
	glEnd();
	glDisable(GL_COLOR);
}
