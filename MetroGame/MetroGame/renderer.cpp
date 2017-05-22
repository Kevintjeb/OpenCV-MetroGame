#include "system.h"

#include <GL\freeglut.h>
#include "Vect.h"
#include "Renderable.h"
#include "Test.h"
#include "Line.h"

using namespace mg_system;
using namespace mg_gameLogic;
GLuint window_db;
Test test{};
Renderable testTrain;

#include "iostream"
#include <GL\freeglut.h>
#include "ModelLoader.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdio>
#include <map>

#include "VertexClass.h"
#include "Renderable.h"

#include "Model.h"
#include "Texture.h"

#include "stb_image.h"
#include "RenderableOutput.h"

#define WIDTH 600
#define HEIGHT 600

#define STEP 0.5f

GLuint WindowID1, WindowID2;
ModelLoader modelLoader;

std::map<std::string, int> modelsMap;
std::map<std::string, int>::iterator it;

int lastTime;
float rotation;
using std::cout;
using std::endl;
int speed = 25;
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

std::vector < VertexClass> TopPlane;
std::vector < VertexClass> GroundPlane;
std::vector < VertexClass > metroLines;
std::vector < std::pair<int, int>> metroLinesPosition;
std::vector<GLuint> textureIDs;

void createDummyRenderableList()
{
	Vec3f pos = Vec3f(0.0f, 4.0f, 100.0f);
	Vec3f rot = Vec3f(0.0f, 1.0f, 0.0f);
	float angle = 45;
	Vec3f scale = Vec3f(0.79f, 0.79f, 0.79f);
	std::string model = "models/city/city.obj";
	auto handle = mg_gameLogic::allocate_renderable(Renderable(model, pos, angle, rot, scale));
}

void loadTexture(std::string filepath)
{
	int width2, height2, bpp2;


	stbi_set_flip_vertically_on_load(1);
	unsigned char* imgData = stbi_load(filepath.c_str(), &width2, &height2, &bpp2, 4);

	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	textureIDs.push_back(textureId);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width2,
		height2,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(imgData);
}

void initTopPlane()
{
	//onderste vlak
	TopPlane.push_back(VertexClass(0, 0, 0, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	TopPlane.push_back(VertexClass(-50, 0, 50, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	TopPlane.push_back(VertexClass(0, 0, 100, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	TopPlane.push_back(VertexClass(50, 0, 50, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));

	//bovenste vlak
	TopPlane.push_back(VertexClass(0, 3, 0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	TopPlane.push_back(VertexClass(-50, 3, 50, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	TopPlane.push_back(VertexClass(0, 3, 100, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	TopPlane.push_back(VertexClass(50, 3, 50, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));

	//rechtsvoor vlak
	TopPlane.push_back(VertexClass(0, 3, 0, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(0, 0, 0, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(-50, 0, 50, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(-50, 3, 50, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));

	//links voor vlak
	TopPlane.push_back(VertexClass(0, 3, 0, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(0, 0, 0, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(50, 0, 50, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(50, 3, 50, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));

	//rechts achter vlak
	TopPlane.push_back(VertexClass(0, 3, 100, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(0, 0, 100, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(-50, 0, 50, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(-50, 3, 50, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));

	//links achter vlak
	TopPlane.push_back(VertexClass(0, 3, 100, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(0, 0, 100, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(50, 0, 50, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	TopPlane.push_back(VertexClass(50, 3, 50, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
}

void initGroundPlane()
{
	//onderste vlak
	GroundPlane.push_back(VertexClass(0, -50, 0, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	GroundPlane.push_back(VertexClass(-50, -50, 50, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	GroundPlane.push_back(VertexClass(0, -50, 100, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	GroundPlane.push_back(VertexClass(50, -50, 50, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));

	//bovenste vlak
	GroundPlane.push_back(VertexClass(0, -50+3, 0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	GroundPlane.push_back(VertexClass(-50, -50 + 3, 50, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	GroundPlane.push_back(VertexClass(0, -50 + 3, 100, 0.0f, 1.0f, 0.0f, 10.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	GroundPlane.push_back(VertexClass(50, -50 + 3, 50, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f));

	//rechts voor vlak
	GroundPlane.push_back(VertexClass(0, -50 + 3, 0, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(0, -50, 0, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(-50, -50, 50, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(-50, -50 + 3, 50, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));

	//links voor vlak
	GroundPlane.push_back(VertexClass(0, -50 + 3, 0, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(0, -50, 0, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(50, -50, 50, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(50, -50 + 3, 50, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));

	//rechts achter vlak
	GroundPlane.push_back(VertexClass(0, -50 + 3, 100, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(0, -50, 100, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(-50, -50, 50, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(-50, -50 + 3, 50, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));

	//links achter vlak
	GroundPlane.push_back(VertexClass(0, -50 + 3, 100, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(0, -50, 100, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(50, -50, 50, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));
	GroundPlane.push_back(VertexClass(50, -50 + 3, 50, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.2f, 1.0f));


}

void drawVertexArray(std::vector<VertexClass> verts, GLenum mode, int start, int end)
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glColorPointer(4, GL_FLOAT, sizeof(VertexClass), ((float*)verts.data()) + 8);
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexClass), ((float*)verts.data()) + 6);
	glNormalPointer(GL_FLOAT, sizeof(VertexClass), ((float*)verts.data()) + 3);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexClass), ((float*)verts.data()) + 0);

	glDrawArrays(mode, start, end);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

void prepareModel(std::string modelPath)
{
	modelLoader.insertModel(modelPath);
	modelsMap.insert(std::pair<std::string, int>(modelPath, modelsMap.size()));
}
/*
void initDebug()
{
	Vec3f pos(0, 0, 0);
	Vec3f rot(0, 0.0, 1.0);
	Vec3f scale(0.225f,0.225f,0.225f);
	testTrain = Redenderable(pos,45, rot, scale);
}*/
void mg_system::_internal::RenderInit()
{
	/*
		GLuint window_id = initWindow("hans", 600, 600, OnDisplay);
		GLuint window_it = initWindow("jollie", 600, 600, OnDisplay);
		window_db = initWindow("Debug", 400, 400, OnDisplay);
		glClearColor(1.0f, 1.0f, 1.0f, 1);
		initDebug();*/

	ZeroMemory(keys, sizeof(keys));
	WindowID2 = initWindow("2D Panel", WIDTH, HEIGHT, OnDisplay2D);
	WindowID1 = initWindow("3D Panel", WIDTH, HEIGHT, OnDisplay3D);

	//init planes
	initTopPlane();
	initGroundPlane();

	//init textures
	loadTexture("textures/dirt.png");

	//load models
	prepareModel("models/steve/steve.obj");
	prepareModel("models/Metro/metro.obj");
	prepareModel("models/city/city.obj");

	//createdummyRenderable
	createDummyRenderableList();
}


void drawRail(Vec2f v1, Vec2f vold) 
{
	glLineWidth(2.5);
	glBegin(GL_LINES);	
	glVertex2f(v1.x, v1.y);
	glVertex2f(vold.x, vold.y);
	glEnd();
}

/*
void drawRenderable(Redenderable& redenderable)		//Draws and Rotates a renderable
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
	

}*/




/*
void drawLine(Line &line) 
{
	for (int i = 1; i < line.size(); i++) 
	{
		drawRail(line[i], line[i - 1]);
	}
}
int i = 0;
int timePassed = 10000;

int oldTime = 0;

void debug()
{
	int newTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTime - oldTime;
	oldTime = newTime;

	glutSetWindow(window_db);
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glColor3f(0.1f, 1.0f, 0.2f);

	drawLine(test.line);
	glColor3f(1.0f, 0.0f, 0.2f);
	//drawRenderable(testTrain);
	//testTrain.position.x = test.line[i].x;
	//testTrain.position.y = test.line[i].y;
	/*timePassed--;
	if (i < test.line.size()-1 && timePassed<0) {
		i++;
		timePassed = 10000;
	}
	test.train.Recalculate(static_cast<float>(/*deltaTime) / 1000 0.00001f));
	for (auto& r : get_renderables())
		drawRenderable(r);
	glutSwapBuffers();
}
*/
/*
void mg_system::_internal::OnDisplay()
{
}
*/
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

void drawCube(float x, float y, float z)
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(x, y, z);
	glVertex3f(x, y+ 1, z);
	glVertex3f(x + 1, y, z);

	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y+ 1, z);
	glVertex3f(x, y + 1, z);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glVertex3f(x, y, z+1);
	glVertex3f(x, y+1, z+1);
	glVertex3f(x+1, y, z+1);

	glVertex3f(x+1, y, z+1);
	glVertex3f(x+1, y+1, z+1);
	glVertex3f(x, y+1, z+1);

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

	glVertex3f(x, y, z);
	glVertex3f(x, y, z+1);
	glVertex3f(x, y+1, z);

	glVertex3f(x, y, z+1);
	glVertex3f(x, y+1, z+1);
	glVertex3f(x, y+1, z);

	glColor4f(1.0f, 0.5f, 0.5f, 1.0f);

	glVertex3f(x+1, y, z);
	glVertex3f(x+1, y, z+1);
	glVertex3f(x+1, y+1, z);

	glVertex3f(x+1, y, z+1);
	glVertex3f(x+1, y+1, z+1);
	glVertex3f(x+1, y+1, z);

	glColor4f(0.5f, 1.0f, 0.5f, 1.0f);

	glVertex3f(x, y, z);
	glVertex3f(x, y, z+1);
	glVertex3f(x+1, y, z+1);

	glVertex3f(x+1, y, z+1);
	glVertex3f(x+1, y, z);
	glVertex3f(x, y, z);

	glColor4f(0.5f, 0.5f, 1.0f, 1.0f);

	glVertex3f(x, y+1, z);
	glVertex3f(x, y+1, z+1);
	glVertex3f(x+1, y+1, z+1);

	glVertex3f(x+1, y+1, z+1);
	glVertex3f(x+1, y+1, z);
	glVertex3f(x+1, y+1, z);
	glEnd();

	glPopMatrix();
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
	modelLoader.getModel(METRO)->draw();
	glPopMatrix();

	glutSwapBuffers();
}


void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void drawRenderables()
{
	for (Renderable &renderable : mg_gameLogic::get_renderables())
	{
		glPushMatrix();
		
		//zorgen dat het object met de wereld mee draait
		glRotatef(rotation, 0, 1, 0);

		glTranslatef(renderable.position.x, renderable.position.y, renderable.position.z);
		glRotatef(renderable.angle, renderable.rotation.x, renderable.rotation.y, renderable.rotation.z);
		glScalef(renderable.scale.x, renderable.scale.y, renderable.scale.z);

		it = modelsMap.find(renderable.model);

		modelLoader.getModel(it->second)->draw(); 
		glPopMatrix();
	}
}

void prepare_lines()
{
	int position = 0;
	metroLines.clear();
	metroLinesPosition.clear();
	for (Line* line : mg_gameLogic::get_lines())
	{
		int start = position;
		for (int index = 0; index < line->size(); index++)
		{
			if (index > 0 && index < line->size() - 1)
			{
				metroLines.push_back(VertexClass(line->operator[](index).x * 25, -50 + 3.1f, line->operator[](index).y * 25, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f));
				position++;
			}
			metroLines.push_back(VertexClass(line->operator[](index).x*25, -50 + 3.1f, line->operator[](index).y*25, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f));
			position++;
		}
		metroLinesPosition.push_back(std::make_pair(start, position));
		position++;
	}
}

void drawRails()
{
	for (int i = 0; i < metroLinesPosition.size(); i++)
	{
		for (int b = metroLinesPosition.at(i).first; b < metroLinesPosition.at(i).second - 1; b++)
		{
			float deltaX = metroLines.at(b + 1).x - metroLines.at(b).x;
			float deltaZ = metroLines.at(b + 1).z - metroLines.at(b).z;
			float rc;

			if (deltaX > 0)
			{
				if (deltaZ > 0)
				{
					if (deltaX > deltaZ)
					{
						rc = deltaX / deltaZ;
						for (float j = 0; j < deltaZ; j += STEP)
						{
							drawCube(metroLines.at(b).x + (rc*j), metroLines.at(b).y, metroLines.at(b).z + j);
						}
					}
					else
					{
						rc = deltaZ / deltaX;
						for (float j = 0; j < deltaX; j += STEP)
						{
							drawCube(metroLines.at(b).x + j, metroLines.at(b).y, metroLines.at(b).z + (rc*j));
						}
					}
				}
				else if (deltaZ < 0)
				{
					deltaZ = deltaZ*-1;
					if (deltaX > deltaZ)
					{
						rc = deltaX / deltaZ;
						for (float j = 0; j < deltaZ; j += STEP)
						{
							drawCube(metroLines.at(b).x + (rc*j), metroLines.at(b).y, metroLines.at(b).z - j);
						}
					}
					else
					{
						rc = deltaZ / deltaX;
						for (float j = 0; j < deltaX; j += STEP)
						{
							drawCube(metroLines.at(b).x + j, metroLines.at(b).y, metroLines.at(b).z - (rc*j));
						}
					}
				}
				else
				{
					for (float j = 0; j < deltaX; j += STEP)
					{
						drawCube(metroLines.at(b).x + j, metroLines.at(b).y, metroLines.at(b).z);
					}
				}
			}
			else if (deltaX < 0)
			{
				deltaX = deltaX * -1;
				if (deltaZ > 0)
				{
					if (deltaX > deltaZ)
					{
						rc = deltaX / deltaZ;
						for (float j = 0; j < deltaZ; j += STEP)
						{
							drawCube(metroLines.at(b).x - (rc*j), metroLines.at(b).y, metroLines.at(b).z + j);
						}
					}
					else
					{
						rc = deltaZ / deltaX;
						for (float j = 0; j < deltaX; j += STEP)
						{
							drawCube(metroLines.at(b).x - j, metroLines.at(b).y, metroLines.at(b).z + (rc*j));
						}
					}
				}
				else if (deltaZ < 0)
				{
					deltaZ = deltaZ*-1;
					if (deltaX > deltaZ)
					{
						rc = deltaX / deltaZ;
						for (float j = 0; j < deltaZ; j += STEP)
						{
							drawCube(metroLines.at(b).x - (rc*j), metroLines.at(b).y, metroLines.at(b).z - j);
						}
					}
					else
					{
						rc = deltaZ / deltaX;
						for (float j = 0; j < deltaX; j += STEP)
						{
							drawCube(metroLines.at(b).x - j, metroLines.at(b).y, metroLines.at(b).z - (rc*j));
						}
					}
				}
				else
				{
					for (float j = 0; j < deltaX; j += STEP)
					{
						drawCube(metroLines.at(b).x - j, metroLines.at(b).y, metroLines.at(b).z);
					}
				}
			}
			else
			{
				if (deltaZ > 0)
				{
					for (float j = 0; j < deltaZ; j += STEP)
					{
						drawCube(metroLines.at(b).x, metroLines.at(b).y, metroLines.at(b).z + j);
					}
				}
				else if (deltaZ < 0)
				{
					deltaZ = deltaZ*-1;
					for (float j = 0; j < deltaZ; j += STEP)
					{
						drawCube(metroLines.at(b).x, metroLines.at(b).y, metroLines.at(b).z - j);
					}
				}
				else
				{
				}
			}





		}
	}
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

	//drawVertexArray(TopPlane);

	glBindTexture(GL_TEXTURE_2D, textureIDs.at(DIRT));
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	drawVertexArray(GroundPlane, GL_QUADS, 0, GroundPlane.size());

	//translation for drawing rails correct
	glTranslatef(0, 0, 50);

	//draw rails
	glLineWidth(1.5);
	prepare_lines();
	for (int i = 0; i < metroLinesPosition.size(); i++)
	{
		drawVertexArray(metroLines, GL_LINES, metroLinesPosition.at(i).first, metroLinesPosition.at(i).second);
	}
	drawRails();

	glPopMatrix();



	//drawRenderable
	drawRenderables();

	glutSwapBuffers(); 
}

void mg_system::redraw() {
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	//cout << "Camera X <" << camera.posX << ">";
	//cout << "Camera Y <" << camera.posY << ">";
	//cout << "Camera Z <" << camera.height << ">" << endl;

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