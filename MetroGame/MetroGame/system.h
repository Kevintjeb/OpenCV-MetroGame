#pragma once

#include <cstdarg>

namespace mg_system
{
	void init(int &argc, char **argv);
	void start();

	void redraw();

	namespace _internal
	{
		void OnGlutError(const char *fmt, va_list ap);
		void OnGlutWarning(const char *fmt, va_list ap);

		// note: doesn't init window(s)
		void freeglutInit(int &argc, char **argv);

		// OpenGL
		void RenderInit();
		void OnDisplay();

		// Game logic
		void GameInit();
		void OnIdle();
		void OnKey(unsigned char key);

		// OpenCV
	}
}