#pragma once

#include <cstdarg>
#include <string>
#include <GL\freeglut.h>

namespace mg_system
{
	void init(int &argc, char **argv);
	void start();

	namespace _internal
	{
		void OnGlutError(const char *fmt, va_list ap);
		void OnGlutWarning(const char *fmt, va_list ap);

		// note: doesn't init window(s)
		void freeglutInit(int &argc, char **argv);

		// OpenCV
	}
}