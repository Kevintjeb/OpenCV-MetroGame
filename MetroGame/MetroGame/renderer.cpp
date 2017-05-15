#include "system.h"
#include <GL\freeglut.h>
#include "Vect.h"
#include "Renderable.h"
#include "Test.h"
#include "Line.h"

using namespace mg_system;
using namespace mg_gameLogic;
GLuint window_db;
Test test;
Redenderable testTrain;

void initDebug()
{
	test = Test();
	Vec3f pos(0, 0, 0);
	Vec3f rot(0, 0.0, 1.0);
	Vec3f scale(0.225f,0.225f,0.225f);
	testTrain = Redenderable(pos,45, rot, scale);
}
void mg_system::_internal::RenderInit()
{
	GLuint window_id = initWindow("hans", 600, 600, OnDisplay);
	GLuint window_it = initWindow("jollie", 600, 600, OnDisplay);
	window_db = initWindow("Debug", 400, 400, OnDisplay);
	glClearColor(1.0f, 1.0f, 1.0f, 1);
	initDebug();
}


void drawRail(Vec2f v1, Vec2f vold) 
{
	glLineWidth(2.5);
	glBegin(GL_LINES);	
	glVertex2f(v1.x, v1.y);
	glVertex2f(vold.x, vold.y);
	glEnd();
}

void drawRenderable(Redenderable redenderable)		//Draws and Rotates a renderable
{	
	

	glPushMatrix();
	glTranslatef(redenderable.position.x, redenderable.position.y, redenderable.position.z);
	glRotatef(redenderable.angle, redenderable.rotation.x, redenderable.rotation.y, redenderable.rotation.z);
	
	glScalef(redenderable.scale.x, redenderable.scale.y, redenderable.scale.z);
	glBegin(GL_QUADS);
	glVertex2f(-0.5, -0.5);            //Draw the four corners of the rectangle
	glVertex2f(-0.5, 0.25);
	glVertex2f(0.5, 0.25);
	glVertex2f(0.5, -0.5);
	glEnd();
	glPopMatrix();
	

}





void drawLine(Line &line) 
{
	for (int i = 1; i < line.size(); i++) 
	{
		drawRail(line[i], line[i - 1]);
	}
}
int i = 0;
int timePassed = 10000;
void debug()
{

	glutSetWindow(window_db);
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glColor3f(0.1f, 1.0f, 0.2f);



	drawLine(test.line);
	glColor3f(1.0f, 0.0f, 0.2f);
	drawRenderable(testTrain);
	testTrain.position.x = test.line[i].x;
	testTrain.position.y = test.line[i].y;
	timePassed--;
	if (i < test.line.size()-1 && timePassed<0) {
		i++;
		timePassed = 10000;
	}
	glutSwapBuffers();
}
void mg_system::_internal::OnDisplay()
{
	debug();
}
