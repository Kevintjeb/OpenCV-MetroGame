#pragma once

#include <cstdarg>
#include <string>
#include <GL\freeglut.h>

namespace mg_system
{
	void init(int &argc, char **argv);
	void start();

	//void redraw();

	GLuint initWindow(std::string name, int width, int height, void(* renderer)());

	namespace _internal
	{
		void OnGlutError(const char *fmt, va_list ap);
		void OnGlutWarning(const char *fmt, va_list ap);

		// note: doesn't init window(s)
		void freeglutInit(int &argc, char **argv);

		// OpenGL
		//void RenderInit();
		//void OnDisplay3D();
		//void OnDisplay2D();

		// Game logic
		void GameInit();
		void OnIdle();
		void OnKey(unsigned char key);
		void OnKeyUp(unsigned char key);

		// OpenCV
	}
}