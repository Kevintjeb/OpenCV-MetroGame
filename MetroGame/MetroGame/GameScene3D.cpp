#include "GameScene3D.h"
#include "GameEndScene.h"

using namespace mg_system;
using namespace mg_gameLogic;
using std::cout;
using std::endl;

#define WIDTH 600
#define HEIGHT 600
#define STEP 0.2f

Font* GameScene3D::largeFont3D = nullptr;
IScene* GameScene3D::endScene = nullptr;


//Random scale factor for a city model
float GameScene3D::randScale(float standScale)
{
	standScale += 0.1f;
	
	float randNum = 0 + (rand() % (int)(10 - 0 + 1));
	float scale = (randNum / 10.0f) * standScale;
	return scale;
}

//create the 3D city
void GameScene3D::createCityList()
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

//create the groundplane.
void GameScene3D::initGroundPlane()
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

//methode to draw a vertex array. 
//GLenum mode -> Could be Quad, Line, Points.
void GameScene3D::drawVertexArray(std::vector<VertexClass> verts, GLenum mode, int start, int end)
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

//Load a 3D model
void GameScene3D::prepareModel(std::string modelPath)
{
	modelLoader.insertModel(modelPath);
	modelsMap.insert(std::pair<std::string, int>(modelPath, modelsMap.size()));
}

//Move the camera. 
void GameScene3D::move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

//draw Renderables -> All 3D models.
void GameScene3D::drawRenderables()
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

//draw Renderables for 2D world -> Streetmap
void GameScene3D::draw2DRenderables()
{
	for (Renderable &renderable : mg_gameLogic::get_renderables())
	{
		glPushMatrix();

		glRotatef(45,0,1,0);

		glTranslatef(renderable.position.x, renderable.position.y, renderable.position.z);
		glRotatef(renderable.angle, renderable.rotation.x, renderable.rotation.y, renderable.rotation.z);

		glScalef(renderable.scale.x, 0.0f, renderable.scale.z);

		if (renderable.model == "models/city/city.obj")
		{
			it = modelsMap.find("models/city2/city2d.obj");
		}
		else
		{
			glPopMatrix();
			continue;
		}

		modelLoader.getModel(it->second)->draw();
		glPopMatrix();
	}
}

//Get Color for metroline
Color GameScene3D::getLineColor(LineType color)
{
	Color lineColor = Color(0.0f, 0.0f, 0.0f);

	switch (color)
	{
	case LineType::Red:
		lineColor = Color(1.0f, 0.0f, 0.0f);
		break;
	case LineType::Green:
		lineColor = Color(0.0f, 1.0f, 0.0f);
		break;
	case LineType::Blue:
		lineColor = Color(0.0f, 0.0f, 1.0f);
		break;
	default:
		lineColor = Color(0.0f, 0.0f, 0.0f);
		break;
	}

	return lineColor;
}

//get the metrolines from gamelogic and convert them to vertexclass. So drawVertexArray can draw them in the 3D world.
void GameScene3D::prepare_lines()
{
	int position = 0;
	metroLines.clear();
	metroLinesPosition.clear();
	for (RenderableLine Rline : mg_gameLogic::get_lines())
	{

		Color color = getLineColor(Rline.type);

		int start = position;
		for (int index = 0; index < Rline.line.size(); index++)
		{
			if (index > 0 && index < Rline.line.size() - 1)
			{
				metroLines.push_back(VertexClass(Rline.line[index].x * 25, -50 + 3.1f, Rline.line[index].y * 25, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f));
				position++;
			}
			metroLines.push_back(VertexClass(Rline.line[index].x * 25, -50 + 3.1f, Rline.line[index].y * 25, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f));
			position++;
		}
		metroLinesPosition.push_back(std::make_pair(start, position));
	}
}

//get the metrolines from gamelogic and convert them to vertexclass. So drawVertexArray can draw them in the 2D world.
void GameScene3D::prepare_lines2D()
{
	int position = 0;
	metroLines2D.clear();
	metroLinesPosition2D.clear();
	for (RenderableLine Rline : mg_gameLogic::get_lines())
	{
		Color color = getLineColor(Rline.type);

		int start = position;
		for (int index = 0; index < Rline.line.size(); index++)
		{
			if (index > 0 && index < Rline.line.size() - 1)
			{
				metroLines2D.push_back(VertexClass(Rline.line[index].x * 50, 4.5f, Rline.line[index].y * 50, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f));
				position++;
			}
			metroLines2D.push_back(VertexClass(Rline.line[index].x * 50, 4.5f, Rline.line[index].y * 50, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f));
			position++;
		}
		metroLinesPosition2D.push_back(std::make_pair(start, position));
	}
}

GameScene3D::GameScene3D()
{
	cb.OnPointIncrease = [this](size_t p) {this->score.points += p; };
	cb.OnGameOver = [this]() {this->score.is_game_over = true; };
	width = SceneManager::getInstance().getWidth();
	height = SceneManager::getInstance().getHeight();

	SceneManager::getInstance().switchWindow3D();
	largeFont3D = new Font("font_0.fnt");
	endScene = new GameEndScene();
	//init ground plane
	initGroundPlane();

	//init textures
	textures.push_back(new Texture("textures/dirt.png"));

	//load models
	prepareModel("models/Metro/metro.obj");
	prepareModel("models/city/city.obj");
	prepareModel("models/track/track_2.obj");
	prepareModel("models/station/station.obj");

	SceneManager::getInstance().switchWindow2D();
	prepareModel("models/city2/city2d.obj");


	//debug data
	passengers.clear();
	passengers.push_back(Passengers(50, 50, Passengers::Priority::LOW));
	passengers.push_back(Passengers(-50, -50, Passengers::Priority::HIGH));
	passengers.push_back(Passengers(-50, 50, Passengers::Priority::EMERENCY));
	passengers.push_back(Passengers(50, -50, Passengers::Priority::EMERENCY));



	SceneManager::getInstance().switchWindow3D();
	//create city
	createCityList();

	MetroStation m1 = MetroStation(Vec2f(0.5f,	0.5f), 1);
	MetroStation m2 = MetroStation(Vec2f(0.25f, 0.25f), 2);
	MetroStation m3 = MetroStation(Vec2f(0.75f, 0.75f), 3);

	//debug data
	line = new Line({ { -1.0f, -1.0f },{ 0.0, -0.25f },{ 0.75f, 0.5f },{ 0.0f, 0.90f },{ -0.75f, 0.25f },{ -1.0f, -0.5f },{ -1.0f, 0.0f },{ 0.0f, 1.1f },{ 0.5f, 0.5f },{ 0.75f, 0.25f },{ -1.0f, -0.90f } }, {m1,m2,m3});
	train = new MetroTrain(cb, line);
	handle = mg_gameLogic::allocate_line(RenderableLine(line->getLine(), LineType::Red));

	line2 = new Line({ { 0.5f, 0.5f },{ -0.5, -0.5f } }, {m2});
	train2 = new MetroTrain(cb, line2);
	handle2 = mg_gameLogic::allocate_line(RenderableLine(line2->getLine(), LineType::Green));

	line3 = new Line({ { -0.5f, 0.5f },{ 0.5f, -0.5f } }, {m3});
	train3 = new MetroTrain(cb, line3);
	handle3 = mg_gameLogic::allocate_line(RenderableLine(line3->getLine(), LineType::Blue));

	line4 = new Line({ { -1.0f, 0.0f },{ 0.0f, -1.0f } }, {m1});
	train4 = new MetroTrain(cb, line4);
	handle4 = mg_gameLogic::allocate_line(RenderableLine(line4->getLine(), LineType::Red));

	line5 = new Line({ { 0.0f, 1.0f },{ 1.0f, 0.0f } }, {m2});
	train5 = new MetroTrain(cb, line5);
	handle5 = mg_gameLogic::allocate_line(RenderableLine(line5->getLine(), LineType::Green));
	std::list<Line*> lines = {line, line2, line3, line4, line5 };
	std::vector<MetroStation> stations = { m1,m2,m3 };
	Timetable t = Timetable(lines, stations);


}


GameScene3D::~GameScene3D()
{
	delete largeFont3D;
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
	if (metroLinesPosition.size() > 0)
	{
		drawVertexArray(metroLines, GL_LINES, metroLinesPosition.at(0).first, metroLinesPosition.at(metroLinesPosition.size() - 1).second);
	}

	glPopMatrix();

	//drawRenderable
	drawRenderables();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(0, 0, 0, 1);
	
	largeFont3D->drawText(timeString, width - largeFont3D->textLength(timeString) - 10, 10);
	largeFont3D->drawText(fps, width - largeFont3D->textLength(fps) - 10, 40);
	largeFont3D->drawText("score: " + std::to_string(this->score.points), width - 160, 70);
}

void GameScene3D::render2D() {
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-75,75,-75,75,-100,100);
	//gluPerspective(90.0f, WIDTH / (float)HEIGHT, 0.1f, 5000.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);

	//set camera
	glLoadIdentity();
	glRotatef(camera2D.rotX, 1, 0, 0);
	glRotatef(camera2D.rotY, 0, 1, 0);
	glTranslatef(camera2D.posX, camera2D.height, camera2D.posY);

	//draw map and lines
	//glRotatef(45, 0, 1, 0);
	draw2DRenderables();

	glDisable(GL_TEXTURE_2D);
	//glRotatef(45, 0, 1, 0);
	//prepare_lines2D();
	//glLineWidth(5.0);
	glScalef(1.4f, 1.0f, 1.4f);
	/*if (metroLinesPosition2D.size() > 0)
	{
		drawVertexArray(metroLines2D, GL_LINES, metroLinesPosition2D.at(0).first, metroLinesPosition2D.at(metroLinesPosition2D.size() - 1).second);
	}*/

	//draw passangers and their destination.
	for (Passengers &p : passengers)
	{
		p.draw();
	}
	glEnable(GL_TEXTURE_2D);

}

void GameScene3D::update()
{
	//TIMETABLE AANMAKEN EN OPNIEUW ALLE PADEN BEREKENEN. 
	//CALL UPDATE FOR EVERY STATION
	train->Recalculate(deltaTime);
	train2->Recalculate(deltaTime);
	train3->Recalculate(deltaTime);
	train4->Recalculate(deltaTime);
	train5->Recalculate(deltaTime);
}

void GameScene3D::onEnter()
{
	lastTime = glutGet(GLUT_ELAPSED_TIME);
	setAllKeysFalse();
}

void GameScene3D::setAllKeysFalse() {
	for (size_t i = 0; i < 255; i++)
	{
		if (keys[i])
			keys[i] = false;
	}
}

void GameScene3D::onExit()
{
	/*delete train;
	delete line;*/
	clear_renderables();
}


void GameScene3D::onKeyUP(unsigned char key)
{
	keys[key] = false;
	/*if (key == ' ') {
		SceneManager::getInstance().pauseSceneVar();
	}*/
}

void GameScene3D::onKeyDown(unsigned char key)
{
	if (key == 27) {
		SceneManager::getInstance().loadScene(endScene);
		return;
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
		timeString = "0" + std::to_string(Time.minutes) + ":0" + std::to_string((int)Time.seconds);
	else if(Time.minutes < 10)
		timeString = "0" + std::to_string(Time.minutes) + ":" + std::to_string((int)Time.seconds);
	else
		timeString = std::to_string(Time.minutes) + ":" + std::to_string((int)Time.seconds);

	
}

void GameScene3D::onIdle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	rotation += deltaTime * 15;

	prepareTime(deltaTime);

	////TODO
	////FIX THIS! IN COMBINATION WITH 2D WINDOW. 2D LINES NOT RIGHT VISIBLE.

	////update metro
	/*int newTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime2 = oldTime >= 0 ? newTime - oldTime : 0;
	oldTime = newTime;
	train->Recalculate(deltaTime2 / 1000.0f);
	train2->Recalculate(deltaTime2 / 1000.0f);
	train3->Recalculate(deltaTime2 / 1000.0f);
	train4->Recalculate(deltaTime2 / 1000.0f);
	train5->Recalculate(deltaTime2 / 1000.0f);*/

	//Update passangers
	for (Passengers &p : passengers)
	{
		p.update();
	}
	

	/*if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);*/
	if (keys['q']) {
		SceneManager::getInstance().loadScene(endScene);
		return;
	}
	
	if (keys['p']) {
		SceneManager::getInstance().pauseScene();
		return;
	}

	/*if (keys[' ']) camera.height -= 25 * deltaTime;
	if (shiftActive) {
		camera.height += 5 * deltaTime;
	}*/
	fps = std::to_string((int)(1 / deltaTime));
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
