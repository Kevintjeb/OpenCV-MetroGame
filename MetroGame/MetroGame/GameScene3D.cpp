#include <GL\freeglut.h>
#include "system.h"
#include "iostream"
#include "ModelLoader.h"
#define _USE_MATH_DEFINES
#include "GameScene3D.h"

#include "Vect.h"
#include "Test.h"
#include "Line.h"
#include <math.h>
#include <cstdio>
#include <map>
#include <time.h>

#include "VertexClass.h"
#include "Renderable.h"

#include "Model.h"
#include "Texture.h"

#include "stb_image.h"
#include "RenderableOutput.h"

#include "SceneManager.h"
#include "MainMenuScene.h"
#include "Passengers.h"

using namespace mg_system;
using namespace mg_gameLogic;
using std::cout;
using std::endl;

#define WIDTH 600
#define HEIGHT 600

#define STEP 0.2f
Font* GameScene3D::largeFont3D = nullptr;

ModelLoader modelLoader;

std::map<std::string, int> modelsMap;
std::map<std::string, int>::iterator it;

GLuint window_db;

LinePointer handle;
Test test{};
Renderable testTrain;
Line *line;
MetroTrain *train;

LinePointer handle2;
Line *line2;
MetroTrain *train2;

LinePointer handle3;
Line *line3;
MetroTrain *train3;

LinePointer handle4;
Line *line4;
MetroTrain *train4;

LinePointer handle5;
Line *line5;
MetroTrain *train5;

int oldTime = -1;

int lastTime;
float rotation;

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

struct Camera2D
{
	float posX = 0;
	float posY = 0;
	float rotX = 90;
	float rotY = 0;
	float height = -80;
}camera2D;

std::vector <VertexClass> TopPlane;
std::vector <VertexClass> GroundPlane;
std::vector <VertexClass> metroLines;
std::vector <std::pair<int, int>> metroLinesPosition;
std::vector <VertexClass> metroLines2D;
std::vector <std::pair<int, int>> metroLinesPosition2D;
std::vector<Texture*> textures;
std::vector<RenderablePointer> renderablePointers;
std::vector<Passengers> passengers;

float randScale(float standScale)
{
	standScale += 0.1f;

	float randNum = 0 + (rand() % (int)(10 - 0 + 1));
	float scale = (randNum / 10.0f) * standScale;
	return scale;
}

void createDummyRenderableList()
{
	srand(time(NULL));
	Vec3f rot = Vec3f(0.0f, 1.0f, 0.0f);
	float angle = 45;
	std::string model = "models/city/city.obj";

	int layer = 0;
	float standScale = 0.2f;
	Vec3f pos, scale;

	for (float z = 100.0f; z > -100.0f; z -= 25.0f)
	{
		switch (layer)
		{
		case 0:
			pos = Vec3f(0.0f, 4.0f, 100.0f);
			scale = Vec3f(standScale, randScale(standScale), standScale);
			renderablePointers.push_back(mg_gameLogic::allocate_renderable(Renderable(model, pos, angle, rot, scale)));
			break;
		case 1:
			for (float x = 25.0f; x > -26.0f; x -= 50.0f)
			{
				pos = Vec3f(x, 4.0f, z);
				scale = Vec3f(standScale, randScale(standScale), standScale);
				renderablePointers.push_back(mg_gameLogic::allocate_renderable(Renderable(model, pos, angle, rot, scale)));
			}
			break;
		case 2:
			for (float x = 50.0f; x > -51.0f; x -= 50.0f)
			{
				pos = Vec3f(x, 4.0f, z);
				scale = Vec3f(standScale, randScale(standScale), standScale);
				renderablePointers.push_back(mg_gameLogic::allocate_renderable(Renderable(model, pos, angle, rot, scale)));
			}
			break;
		case 3:
			for (float x = 75.0f; x > -76.0f; x -= 50.0f)
			{
				pos = Vec3f(x, 4.0f, z);
				scale = Vec3f(standScale, randScale(standScale), standScale);
				renderablePointers.push_back(mg_gameLogic::allocate_renderable(Renderable(model, pos, angle, rot, scale)));
			}
			break;
		case 4:
			for (float x = 50.0f; x > -51.0f; x -= 50.0f)
			{
				pos = Vec3f(x, 4.0f, z);
				scale = Vec3f(standScale, randScale(standScale), standScale);
				renderablePointers.push_back(mg_gameLogic::allocate_renderable(Renderable(model, pos, angle, rot, scale)));
			}
			break;
		case 5:
			for (float x = 25.0f; x > -26.0f; x -= 50.0f)
			{
				pos = Vec3f(x, 4.0f, z);
				scale = Vec3f(standScale, randScale(standScale), standScale);
				renderablePointers.push_back(mg_gameLogic::allocate_renderable(Renderable(model, pos, angle, rot, scale)));
			}
			break;
		case 6:
			pos = Vec3f(0.0f, 4.0f, -50.0f);
			scale = Vec3f(standScale, randScale(standScale), standScale);
			renderablePointers.push_back(mg_gameLogic::allocate_renderable(Renderable(model, pos, angle, rot, scale)));
			break;

		default:
			break;
		}

		layer++;
	}
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
	GroundPlane.push_back(VertexClass(0, -50 + 3, 0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f));
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

void drawRail(Vec2f v1, Vec2f vold)
{
	glLineWidth(2.5);
	glBegin(GL_LINES);
	glVertex2f(v1.x, v1.y);
	glVertex2f(vold.x, vold.y);
	glEnd();
}

void drawTopPlane() {
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(-50, 0, 50);
	glVertex3f(0, 0, 100);
	glVertex3f(50, 0, 50);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glVertex3f(0, 3, 0);
	glVertex3f(-50, 3, 50);
	glVertex3f(0, 3, 100);
	glVertex3f(50, 3, 50);

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

		if (renderable.model != "models/city/city.obj")
		{
			glRotatef(45, 0, 1, 0);
		}
		
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

void draw2DRenderables()
{
	for (Renderable &renderable : mg_gameLogic::get_renderables())
	{
		glPushMatrix();

		glTranslatef(renderable.position.x, renderable.position.y, renderable.position.z);
		glRotatef(renderable.angle, renderable.rotation.x, renderable.rotation.y, renderable.rotation.z);

		glScalef(renderable.scale.x, 0.0f, renderable.scale.z);

		if (renderable.model == "models/city/city.obj")
		{
			it = modelsMap.find("models/city2/city2d.obj");
		}
		else
		{
			continue;
			it = modelsMap.find(renderable.model);
		}

		modelLoader.getModel(it->second)->draw();
		glPopMatrix();
	}
}

Vec3f getLineColor(LineType color)
{
	Vec3f lineColor;

	switch (color)
	{
	case LineType::Red:
		lineColor = Vec3f(1.0f, 0.0f, 0.0f);
		break;
	case LineType::Green:
		lineColor = Vec3f(0.0f, 1.0f, 0.0f);
		break;
	case LineType::Blue:
		lineColor = Vec3f(0.0f, 0.0f, 1.0f);
		break;
	default:
		lineColor = Vec3f(1.0f, 1.0f, 0.0f);
		break;
	}

	return lineColor;
}

void prepare_lines()
{
	int position = 0;
	metroLines.clear();
	metroLinesPosition.clear();
	for (Line* line : mg_gameLogic::get_lines())
	{

		Vec3f color = getLineColor(line->type);

		int start = position;
		for (int index = 0; index < line->size(); index++)
		{
			if (index > 0 && index < line->size() - 1)
			{
				metroLines.push_back(VertexClass(line->operator[](index).x * 25, -50 + 3.1f, line->operator[](index).y * 25, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, color.x, color.y, color.z, 1.0f));
				position++;
			}
			metroLines.push_back(VertexClass(line->operator[](index).x * 25, -50 + 3.1f, line->operator[](index).y * 25, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, color.x, color.y, color.z, 1.0f));
			position++;
		}
		metroLinesPosition.push_back(std::make_pair(start, position));
	}
}

void prepare_lines2D()
{
	int position = 0;
	metroLines2D.clear();
	metroLinesPosition2D.clear();
	for (Line* line : mg_gameLogic::get_lines())
	{
		Vec3f color = getLineColor(line->type);

		int start = position;
		for (int index = 0; index < line->size(); index++)
		{
			if (index > 0 && index < line->size() - 1)
			{
				metroLines2D.push_back(VertexClass(line->operator[](index).x * 50, 10.0f, line->operator[](index).y * 50, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, color.x, color.y, color.z, 1.0f));
				position++;
			}
			metroLines2D.push_back(VertexClass(line->operator[](index).x * 50, 10.0f, line->operator[](index).y * 50, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, color.x, color.y, color.z, 1.0f));
			position++;
		}
		metroLinesPosition2D.push_back(std::make_pair(start, position));
	}
}

void drawTrack(float x, float y, float z, Vec2f line)
{
	float rot = atan2f(line.x, line.y);
	rot = rot * 180.0f / M_PI;

	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(rot, 0, 1, 0);
	it = modelsMap.find("models/track/track_2.obj");
	modelLoader.getModel(it->second)->draw();
	glPopMatrix();
}

void drawRails()
{
	for (int i = 0; i < metroLinesPosition.size(); i++)
	{
		volatile int grens = metroLinesPosition.at(i).second;

		for (int b = metroLinesPosition.at(i).first; b < metroLinesPosition.at(i).second; b++)
		{
			float deltaX = metroLines.at(b + 1).x - metroLines.at(b).x;
			float deltaZ = metroLines.at(b + 1).z - metroLines.at(b).z;
			float rc;

			Vec2f vectorLine = Vec2f(deltaX, deltaZ);

			if (deltaX > 0)
			{
				if (deltaZ > 0)
				{
					if (deltaX > deltaZ)
					{
						rc = deltaX / deltaZ;
						for (float j = 0; j < deltaZ; j += STEP)
						{
							drawTrack(metroLines.at(b).x + (rc*j), metroLines.at(b).y, metroLines.at(b).z + j, vectorLine);
						}
					}
					else
					{
						rc = deltaZ / deltaX;
						for (float j = 0; j < deltaX; j += STEP)
						{
							drawTrack(metroLines.at(b).x + j, metroLines.at(b).y, metroLines.at(b).z + (rc*j), vectorLine);
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
							drawTrack(metroLines.at(b).x + (rc*j), metroLines.at(b).y, metroLines.at(b).z - j, vectorLine);
						}
					}
					else
					{
						rc = deltaZ / deltaX;
						for (float j = 0; j < deltaX; j += STEP)
						{
							drawTrack(metroLines.at(b).x + j, metroLines.at(b).y, metroLines.at(b).z - (rc*j), vectorLine);
						}
					}
				}
				else
				{
					for (float j = 0; j < deltaX; j += STEP)
					{
						drawTrack(metroLines.at(b).x + j, metroLines.at(b).y, metroLines.at(b).z, vectorLine);
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
							drawTrack(metroLines.at(b).x - (rc*j), metroLines.at(b).y, metroLines.at(b).z + j, vectorLine);
						}
					}
					else
					{
						rc = deltaZ / deltaX;
						for (float j = 0; j < deltaX; j += STEP)
						{
							drawTrack(metroLines.at(b).x - j, metroLines.at(b).y, metroLines.at(b).z + (rc*j), vectorLine);
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
							drawTrack(metroLines.at(b).x - (rc*j), metroLines.at(b).y, metroLines.at(b).z - j, vectorLine);
						}
					}
					else
					{
						rc = deltaZ / deltaX;
						for (float j = 0; j < deltaX; j += STEP)
						{
							drawTrack(metroLines.at(b).x - j, metroLines.at(b).y, metroLines.at(b).z - (rc*j), vectorLine);
						}
					}
				}
				else
				{
					for (float j = 0; j < deltaX; j += STEP)
					{
						drawTrack(metroLines.at(b).x - j, metroLines.at(b).y, metroLines.at(b).z, vectorLine);
					}
				}
			}
			else
			{
				if (deltaZ > 0)
				{
					for (float j = 0; j < deltaZ; j += STEP)
					{
						drawTrack(metroLines.at(b).x, metroLines.at(b).y, metroLines.at(b).z + j, vectorLine);
					}
				}
				else if (deltaZ < 0)
				{
					deltaZ = deltaZ*-1;
					for (float j = 0; j < deltaZ; j += STEP)
					{
						drawTrack(metroLines.at(b).x, metroLines.at(b).y, metroLines.at(b).z - j, vectorLine);
					}
				}
				else
				{
				}
			}
		}
	}
}

void DrawCircle(float cx, float cy, float r, Vec3f color)
{
	
}


GameScene3D::GameScene3D()
{
	width = SceneManager::getInstance().getWidth();
	height = SceneManager::getInstance().getHeight();
	
	SceneManager::getInstance().switchWindow3D();
	largeFont3D = new Font("font_0.fnt");
	//init planes
	initTopPlane();
	initGroundPlane();

	//init textures
	textures.push_back(new Texture("textures/dirt.png"));

	//load models
	prepareModel("models/Metro/metro.obj");
	prepareModel("models/city/city.obj");
	prepareModel("models/track/track_2.obj");
	
	SceneManager::getInstance().switchWindow2D();
	prepareModel("models/city2/city2d.obj");


	//debug
	passengers.push_back(Passengers(0, 0, Passengers::Priority::LOW));
	passengers.push_back(Passengers(-50, 0, Passengers::Priority::HIGH));
	passengers.push_back(Passengers(50, 50, Passengers::Priority::HIGH));
	passengers.push_back(Passengers(40, 10, Passengers::Priority::LOW));
	passengers.push_back(Passengers(-5, -25, Passengers::Priority::EMERENCY));
	passengers.push_back(Passengers(20, -25, Passengers::Priority::HIGH));

	SceneManager::getInstance().switchWindow3D();
	//create city
	createDummyRenderableList();

	//debug data
	line = new Line({ { -1.0f, -1.0f },{ 0.0, -0.25f },{ 0.75f, 0.5f },{ 0.0f, 0.90f },{ -0.75f, 0.25f },{ -1.0f, -0.5f },{ -1.0f, 0.0f },{ 0.0f, 1.1f },{ 0.5f, 0.5f },{ 0.75f, 0.25f },{ -1.0f, -0.90f } }, LineType::Red);
	train = new MetroTrain(*line);
	handle = mg_gameLogic::allocate_line(line);

	line2 = new Line({ { 0.5f, 0.5f },{ -0.5, -0.5f } }, LineType::Green);
	train2 = new MetroTrain(*line2);
	handle2 = mg_gameLogic::allocate_line(line2);

	line3 = new Line({ { -0.5f, 0.5f },{ 0.5f, -0.5f } }, LineType::Blue);
	train3 = new MetroTrain(*line3);
	handle3 = mg_gameLogic::allocate_line(line3);

	line4 = new Line({ { -1.0f, 0.0f },{ 0.0f, -1.0f } }, LineType::Red);
	train4 = new MetroTrain(*line4);
	handle4 = mg_gameLogic::allocate_line(line4);

	line5 = new Line({ { 0.0f, 1.0f },{ 1.0f, 0.0f } }, LineType::Green);
	train5 = new MetroTrain(*line5);
	handle5 = mg_gameLogic::allocate_line(line5);
}


GameScene3D::~GameScene3D()
{
}

void GameScene3D::render3D()
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
	textures[0]->Bind();
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	drawVertexArray(GroundPlane, GL_QUADS, 0, GroundPlane.size());

	//translation for drawing rails correct
	glTranslatef(0, 0, 50);
	glRotatef(45, 0, 1, 0);

	//draw rails as line
	prepare_lines();
	glDisable(GL_TEXTURE_2D);
	glLineWidth(1.5);
	drawVertexArray(metroLines, GL_LINES, metroLinesPosition.at(0).first, metroLinesPosition.at(metroLinesPosition.size()-1).second);

	glPopMatrix();

	//drawRenderable
	drawRenderables();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(0, 0, 0, 1);
	
	largeFont3D->drawText(time, width - largeFont3D->textLength(time) - 10, 10);
}

void GameScene3D::render2D() {
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90.0f, WIDTH / (float)HEIGHT, 0.1f, 5000.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	glRotatef(camera2D.rotX, 1, 0, 0);
	glRotatef(camera2D.rotY, 0, 1, 0);
	glTranslatef(camera2D.posX, camera2D.height, camera2D.posY);

	//draw map and lines
	glRotatef(45, 0, 1, 0);
	draw2DRenderables();
	glDisable(GL_TEXTURE_2D);
	glRotatef(45, 0, 1, 0);
	prepare_lines2D();
	glLineWidth(5.0);
	drawVertexArray(metroLines2D, GL_LINES, metroLinesPosition2D.at(0).first, metroLinesPosition2D.at(metroLinesPosition2D.size()-1).second);

	for (Passengers &p : passengers)
	{
		p.draw();
	}

}

void GameScene3D::update()
{

}

void GameScene3D::onEnter()
{
	lastTime = glutGet(GLUT_ELAPSED_TIME);
}

void setAllKeysFalse() {
	for (size_t i = 0; i < 255; i++)
	{
		if (keys[i])
			keys[i] = false;
	}
}

void GameScene3D::onExit()
{
	delete train;
	delete line;
	setAllKeysFalse();
	clear_renderables();
}


void GameScene3D::onKeyUP(unsigned char key)
{
	keys[key] = false;
	/*if (key == ' ') {
		SceneManager::getInstance().pauseScene();
	}*/
}

void GameScene3D::onKeyDown(unsigned char key)
{
	if (key == 27) {
		exit(0);
	}
	keys[key] = true;
}

void GameScene3D::prepareTime(float deltaTime) {
	Time.seconds += deltaTime;
	if (Time.seconds > 60) {
		Time.seconds = 0;
		Time.minutes++;
	}

	if (Time.minutes < 10 && Time.seconds < 10)
		time = "0" + std::to_string(Time.minutes) + ":0" + std::to_string((int)Time.seconds);
	else if(Time.minutes < 10)
		time = "0" + std::to_string(Time.minutes) + ":" + std::to_string((int)Time.seconds);
	else
		time = std::to_string(Time.minutes) + ":" + std::to_string((int)Time.seconds);

	
}

void GameScene3D::onIdle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	rotation += deltaTime * 15;

	prepareTime(deltaTime);

	//update metro
	int newTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime2 = oldTime >= 0 ? newTime - oldTime : 0;
	oldTime = newTime;
	train->Recalculate(deltaTime2 / 1000.0f);
	train2->Recalculate(deltaTime2 / 1000.0f);
	train3->Recalculate(deltaTime2 / 1000.0f);
	train4->Recalculate(deltaTime2 / 1000.0f);
	train5->Recalculate(deltaTime2 / 1000.0f);


	for (Passengers &p : passengers)
	{
		p.update();
	}
	

	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);
	if (keys['q']) {
		SceneManager::getInstance().loadScene(new MainMenuScene());
	}

	if (keys[' ']) camera.height -= 25 * deltaTime;
	if (shiftActive) {
		camera.height += 5 * deltaTime;
	}

	cout << "FPS:" << (int)(1 / deltaTime) << endl;
}

void GameScene3D::onSpecialFunc(int)
{
	shiftActive = true;
}

void GameScene3D::onSpecialUpFunc(int)
{
	shiftActive = false;
}

void GameScene3D::reshapeFunc(int, int)
{
}
