#ifndef SHADER_LOADER_LIB
#define SHADER_LOADER_LIB

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#include <GL/glext.h>


GLuint LoadShaders(const char * vertexFilePath, const char * fragmentFilePath);

#endif
