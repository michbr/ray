#ifndef SHADER_LOADER_LIB
#define SHADER_LOADER_LIB

#include <GL/glew.h>

#include <GL/gl.h>

#include <GL/glext.h>

GLuint LoadShaders(const char * vertexFilePath, const char * fragmentFilePath);

#endif
