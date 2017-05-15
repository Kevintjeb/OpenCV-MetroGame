#include "system.h"
#include <GL\freeglut.h>
#include "Vect.h"
#include "Renderable.h"
#include "Test.h"

using namespace mg_system;
using namespace mg_gameLogic;
GLuint window_db;
void mg_system::_internal::RenderInit()
{
	GLuint window_id = initWindow("hans", 600, 600, OnDisplay);
	GLuint window_it = initWindow("jollie", 600, 600, OnDisplay);
	window_db = initWindow("Debug", 400, 400, OnDisplay);
	glClearColor(1.0f, 1.0f, 1.0f, 1);
}

void drawRail(Vec2f v1, Vec2f vold) 
{
	glLineWidth(2.5);
	glBegin(GL_LINES);	
	glVertex2f(v1.x, v1.y);
	glVertex2f(vold.x, vold.y);
	glVertex2f(vold.x, vold.y);
	glVertex2f(v1.x, vold.y);
	glEnd();
}

void drawTrain(Redenderable renderable, Redenderable oldRend)
{
	glPushMatrix();
	glBegin(GL_QUADS);

	glTranslatef(renderable.rotation.x, renderable.rotation.y, renderable.rotation.z);
	
	glVertex2f(renderable.position.x, renderable.position.y);
	glVertex2f(renderable.position.x, renderable.position.y+0.025f);
	glVertex2f(renderable.position.x +0.025f, renderable.position.y+0.025f);
	glVertex2f(renderable.position.x+0.025f, renderable.position.y+0.025f);
	glEnd();
	glPopMatrix();
}


void debug()
{
	
	glutSetWindow(window_db);
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glColor3f(0.1f, 1.0f, 0.2f);
	//Vec2f preVector;
	//for (/*something containing vectors*/) 
	//{
	//	drawRail(newVector, preVector);
	//	preVector = newVector;
	//}
	
	glutSwapBuffers();
}

void mg_system::_internal::OnDisplay()
{
	debug();
}

