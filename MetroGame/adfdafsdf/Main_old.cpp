/*
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>

using namespace std;

int height = 300;
int width = 600;

float r = 0.0f;
float g = 0.0f;
float b = 0.0f;

int lastTime = 0;
int cubex, cubey, cubez = 0;
float rotation = 0;


float r2 = 0.0f;
float g2 = 0.0f;
float b2 = 0.0f;

int lastTime2 = 0;
int cubex2, cubey2, cubez2 = 0;

float rotation2 = 0;

bool ctrlToggled = false;
bool orthoToggled = false;
bool wireFrameToggled = false;
GLint WindowID1, WindowID2;                  // window ID numbers


void changeColor(int x, int y)
{
	r = ((float)rand() / (RAND_MAX));
	g = ((float)rand() / (RAND_MAX));
	b = ((float)rand() / (RAND_MAX));

	r2 = r;
	g2 = g;
	b2 = b;

	cout << "R value : <" << r << ">" << endl;
	cout << "G value : <" << g << ">" << endl;
	cout << "B value : <" << b << ">" << endl;
}


void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
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
	glPopMatrix();
}


void specialDrawCube()
{
	glBegin(GL_TRIANGLES);

	glColor4f(r, g, b, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 0, 0);

	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);

	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 0);

	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 1, 0);


	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 0);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);

	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glPopMatrix();
}


void specialDrawCube2()
{
	glBegin(GL_TRIANGLES);

	glColor4f(r2, g2, b2, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 0, 0);

	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);

	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 0);

	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 1, 0);


	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 0);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);

	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glPopMatrix();
}

void keyboard(unsigned char key, int x, int  y)
{
	switch (key) {
	case 27: exit(0);
		break;
	case 32: orthoToggled = !orthoToggled;
		break;
	case 9: wireFrameToggled = !wireFrameToggled;
		break;
	}

}

void keyboardSpecial(int key, int x, int y)
{
	cout << "key : <" << key << ">" << endl;
	if (key == 114) {
		ctrlToggled = !ctrlToggled;
	}
	if (!ctrlToggled) {
		switch (key) {
		case 100:
			cubex--;
			break;
		case 101:
			cubey++;
			break;
		case 102:
			cubex++;
			break;
		case 103:
			cubey--;
			break;
		}
	}
	else
	{
		switch (key) {
		case 101:
			cubez--;
			break;
		case 103:
			cubez++;
			break;
		}
	}
}
int currentWindow = 0;
void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (orthoToggled) {
		int ratio = width / (float)height;
		glOrtho(-10 * ratio, 10 * ratio, -10, 10, -10, 50);
	}
	else {
		gluPerspective(90.0f, width / (float)height, 0.1f, 50.0f);
	}
	if (wireFrameToggled)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();
	gluLookAt(0, 5, 5,
		0, 0, 0,
		0, 1, 0);

	glPushMatrix();
	glTranslatef(cubex, cubey, cubez);
	glRotatef(rotation, 1, 0, 0);
	glTranslatef(-.5, -.5, -.5);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 0, 0);
	glRotatef(rotation, 0, 1, 0);
	glTranslatef(-.5, -.5, -.5);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 0, 0);
	glRotatef(rotation, 0, 0, 1);
	glTranslatef(-.5, -.5, -.5);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -5);
	glRotatef(rotation, 1, 1, 1);
	glTranslatef(-.5, -.5, -.5);
	specialDrawCube();
	glPopMatrix();

	glutSwapBuffers();
}

void display2()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (orthoToggled) {
		int ratio = width / (float)height;
		glOrtho(-10 * ratio, 10 * ratio, -10, 10, -10, 50);
	}
	else {
		gluPerspective(90.0f, width / (float)height, 0.1f, 50.0f);
	}
	if (wireFrameToggled)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();
	gluLookAt(0, 5, 5,
		0, 0, 0,
		0, 1, 0);

	glPushMatrix();
	glTranslatef(cubex2, cubey2, cubez2);
	glRotatef(rotation2, 1, 0, 0);
	glTranslatef(-.5, -.5, -.5);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 0, 0);
	glRotatef(rotation2, 0, 1, 0);
	glTranslatef(-.5, -.5, -.5);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 0, 0);
	glRotatef(rotation2, 0, 0, 1);
	glTranslatef(-.5, -.5, -.5);
	drawCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -5);
	glRotatef(rotation2, 1, 1, 1);
	glTranslatef(-.5, -.5, -.5);
	specialDrawCube2();
	glPopMatrix();

	glutSwapBuffers();
}

void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	rotation += deltaTime * 180;
	rotation2 = rotation;

	glutSetWindow(WindowID1);
	glutPostRedisplay();

	glutSetWindow(WindowID2);
	glutPostRedisplay();
}


int
(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);

	WindowID1 = glutCreateWindow("Window One"); // Create window 1
	cout << "pane 1 :" << WindowID1 << endl;
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);

	glutInitWindowPosition(500, 50);             // set a window position
	WindowID2 = glutCreateWindow("Window Two"); // Create window 2
	cout << "pane 2 :" << WindowID2 << endl;
	glutDisplayFunc(display2);

	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutMotionFunc(changeColor);
	///opengl init

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 0;
}
*/