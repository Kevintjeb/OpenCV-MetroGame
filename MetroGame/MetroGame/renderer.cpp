#include "system.h"
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

#define WIDTH 600
#define HEIGHT 600

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
std::vector<GLuint> textureIDs;
std::vector<Renderable> renderables;

void createDummyRenderableList()
{
	Vec3f pos = Vec3f(0.0f, 4.0f, 100.0f);
	Vec3f rot = Vec3f(0.0f, 1.0f, 0.0f);
	float angle = 45;
	Vec3f scale = Vec3f(0.79f, 0.79f, 0.79f);
	std::string model = "models/city/city.obj";
	renderables.push_back(Renderable(pos, rot, angle, scale, model));

	Vec3f pos2 = Vec3f(10.0f, -92.0f, 10.0f);
	Vec3f rot2 = Vec3f(0.0f, 1.0f, 0.0f);
	float angle2 = 0;
	Vec3f scale2 = Vec3f(2.0f, 2.0f, 2.0f);
	std::string model2 = "models/Metro/metro.obj";
	renderables.push_back(Renderable(pos2, rot2, angle2, scale2, model2));

	Vec3f pos3 = Vec3f(-10.0f, -92.0f, -10.0f);
	Vec3f rot3 = Vec3f(0.0f, 1.0f, 0.0f);
	float angle3 = 270;
	Vec3f scale3 = Vec3f(2.0f, 2.0f, 2.0f);
	std::string model3 = "models/Metro/metro.obj";
	renderables.push_back(Renderable(pos3, rot3, angle3,  scale3, model3));
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

void drawVertexArray(std::vector<VertexClass> verts)
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glColorPointer(4, GL_FLOAT, sizeof(VertexClass), ((float*)verts.data()) + 8);
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexClass), ((float*)verts.data()) + 6);
	glNormalPointer(GL_FLOAT, sizeof(VertexClass), ((float*)verts.data()) + 3);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexClass), ((float*)verts.data()) + 0);

	glDrawArrays(GL_QUADS, 0, verts.size());

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

void mg_system::_internal::RenderInit()
{
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
	for (Renderable &renderable : renderables)
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
	drawVertexArray(GroundPlane);

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