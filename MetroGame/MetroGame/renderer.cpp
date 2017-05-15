#include "system.h"
#include "iostream"
#include <GL\freeglut.h>
#include "ModelLoader.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdio>

#define WIDTH 600
#define HEIGHT 600

GLuint WindowID1, WindowID2;
ModelLoader modelLoader;

int lastTime;
float rotation;
using std::cout;
using std::endl;
int speed = 5;
bool keys[255];
bool shiftActive = false;

struct Camera
{
	float posX = 7.57;
	float posY = -103.79;
	float rotX = 0;
	float rotY = 0;
	float height = 41.07;
} camera;

void mg_system::_internal::RenderInit()
{
	ZeroMemory(keys, sizeof(keys));
	WindowID2 = initWindow("2D Panel", WIDTH, HEIGHT, OnDisplay2D);
	WindowID1 = initWindow("3D Panel", WIDTH, HEIGHT, OnDisplay3D);
	modelLoader.insertModel("models/steve/steve.obj");
	glClearColor(0, 0, 0, 1);
}

void drawTopPlane() {
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0,  0, 0);
	glVertex3f(-50, 0, 50);
	glVertex3f(0, 0, 100);
	glVertex3f(50, 0, 50);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glVertex3f(0, 3, 0);
	glVertex3f(-50, 3, 50);
	glVertex3f(0,3, 100);
	glVertex3f(50,3, 50);

	glColor4f(0.6f, 0.2f, 0.2f, 1.0f);

	glVertex3f(0, 3, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(-50, 0, 50);
	glVertex3f(-50, 3, 50);

	glVertex3f(0, 3, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(50, 0, 50);
	glVertex3f(50, 3, 50);

	glVertex3f(0, 3, 100);
	glVertex3f(0, 0, 100);
	glVertex3f(-50, 0, 50);
	glVertex3f(-50, 3, 50);

	glVertex3f(0, 3, 100);
	glVertex3f(0, 0, 100);
	glVertex3f(50, 0, 50);
	glVertex3f(50, 3, 50);
	glEnd();
}


void drawGroundPlane() {
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0, -50, 0);
	glVertex3f(-50, -50, 50);
	glVertex3f(0, -50, 100);
	glVertex3f(50, -50, 50);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	glVertex3f(0, -50 + 3, 0);
	glVertex3f(-50, -50 + 3, 50);
	glVertex3f(0, -50 + 3, 100);
	glVertex3f(50, -50 + 3, 50);

	glColor4f(0.6f, 0.2f, 0.2f, 1.0f);

	glVertex3f(0, -50 + 3, 0);
	glVertex3f(0, -50, 0);
	glVertex3f(-50, -50, 50);
	glVertex3f(-50, -50 + 3, 50);

	glVertex3f(0, -50 + 3, 0);
	glVertex3f(0, -50, 0);
	glVertex3f(50, -50, 50);
	glVertex3f(50, -50 + 3, 50);

	glVertex3f(0, -50 + 3, 100);
	glVertex3f(0, -50, 100);
	glVertex3f(-50, -50, 50);
	glVertex3f(-50, -50 + 3, 50);

	glVertex3f(0, -50 + 3, 100);
	glVertex3f(0, -50, 100);
	glVertex3f(50, -50, 50);
	glVertex3f(50, -50 + 3, 50);
	glEnd();
}

void drawCube()
{
	glBegin(GL_TRIANGLES);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 0, 0);

	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 0);

	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 1, 0);

	glColor4f(1.0f, 0.5f, 0.5f, 1.0f);

	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 0);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);

	glColor4f(0.5f, 1.0f, 0.5f, 1.0f);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);
		
	glColor4f(0.5f, 0.5f, 1.0f, 1.0f);

	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);

	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
}


void mg_system::_internal::OnDisplay2D()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, WIDTH / (float)HEIGHT, 0.1f, 200000);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(100, 100, 1000,
		0, 0, 0,
		0, 1, 0);

	glPushMatrix();
	glTranslatef(-1688, -900, -3435);
	glScalef(0.01, 0.01, 0.01);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	modelLoader.getModel(0)->draw();
	glPopMatrix();

	glutSwapBuffers();
}


void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}


void mg_system::_internal::OnDisplay3D()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0f, WIDTH / (float)HEIGHT, 0.1f, 5000.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.height, camera.posY);

	gluLookAt(0, 30, -50,
		0, 0, 0,
		0, 1, 0);

	glPushMatrix();
	glScalef(2, 2, 2);
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(0, 0, -50);
	drawTopPlane();
	drawGroundPlane();
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(0, 5, 0);
	modelLoader.getModel(0)->draw();
	glPopMatrix();

	glutSwapBuffers(); 
}

void mg_system::redraw() {
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	cout << "Camera X <" << camera.posX << ">";
	cout << "Camera Y <" << camera.posY << ">";
	cout << "Camera Z <" << camera.height << ">" << endl;

	rotation += deltaTime * 15;

	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);

	if (keys[' ']) camera.height -= 25 * deltaTime;
	if (shiftActive) {
		camera.height += 5 * deltaTime;
	}
	glutSetWindow(WindowID1);
	glutPostRedisplay();
	glutSetWindow(WindowID2);
	glutPostRedisplay();
}