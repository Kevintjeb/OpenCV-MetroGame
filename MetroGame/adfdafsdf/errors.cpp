#include "system.h"

#include <cstdio>

void mg_system::_internal::OnGlutError(const char *fmt, va_list ap)
{
	printf("GLUT_"); printf(fmt, ap);
}

void mg_system::_internal::OnGlutWarning(const char *fmt, va_list ap)
{
	printf("GLUT_"); printf(fmt, ap);
}