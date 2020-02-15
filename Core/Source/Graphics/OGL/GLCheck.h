#pragma once
#include "Containers/String.h"
#include "Defines.h"

static void GLCheck(const char* function, const char* file, int line)
{
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		LOG("OGL error: (" + Forge::String(error) + ") at: " + Forge::String(function) + Forge::String(line) + Forge::String(file) + "\n");
	}
}

#ifdef DBG

#define glCheck(expr) do { expr; GLCheck(#expr, __FILE__, __LINE__); } while (false)

#else

#define glCheck(expr) (expr)

#endif