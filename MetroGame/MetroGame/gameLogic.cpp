#include "system.h"

#include <GL\freeglut.h>
#include "Line.h"
#include "MetroTrain.h"
#include <list>
#include "MetroStation.h"

using namespace mg_gameLogic;
using namespace mg_system;
extern bool keys[255];

Line *line;
MetroTrain *train;
MetroStation station;

void mg_system::_internal::GameInit()
{
	
	line = new Line({ {-1.0f,-0.25f}, {0,-0.25f}, {1, -0.25f} }, { { MetroStation(Vec2f(0.5,-0.25f)) } });
	train = new MetroTrain(line);
}

int oldTime = -1;

void mg_system::_internal::OnIdle()
{
	int newTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = oldTime >= 0 ? newTime - oldTime : 0;
	oldTime = newTime;

	train->Recalculate(deltaTime / 1000.0f);

	redraw();
}

void mg_system::_internal::OnKey(unsigned char key)
{
	if (key == 27) {
		exit(0);
	}
	keys[key] = true;
}

void mg_system::_internal::OnKeyUp(unsigned char key)
{
	keys[key] = false;
}