#pragma once
#include <fstream>

#define GLSL(version, shader) "#version " #version "\n" #shader "\0"

#pragma region DefaultShaders

static const char* DEFAULT_VERT_3D = GLSL(430,
									 layout(location = 0) in vec4 position;
									 layout(location = 1) in vec4 color;
									 layout(location = 2) uniform mat4 model;
									 layout(location = 3) uniform mat4 view;
									 layout(location = 4) uniform mat4 proj;

									 out vec4 inColor;

									 void main()
									 {
										 gl_Position = proj * view * model * position;
										 inColor = color;
									 });

static const char* DEFAULT_VERT = GLSL(430,
									 layout(location = 0) in vec4 position;
									 layout(location = 1) in vec4 texCoord;

									 layout(location = 2) uniform vec4 color;
									 layout(location = 3) uniform mat4 model;
									 layout(location = 4) uniform mat4 view;
									 layout(location = 5) uniform mat4 proj;
									 layout(location = 6) uniform int rows = 1;
									 layout(location = 7) uniform int cols = 1;
									 layout(location = 8) uniform int index = 0;

									 out vec4 vColor;
									 out vec2 vTexCoord;

									 void main()
									 {
										 int i = index % (rows*cols);
										 float c = (i % rows);
										 float r = (i / rows);
										 vTexCoord = (vec2(c, r) + texCoord.xy) / vec2(rows, cols);
										 gl_Position = proj * view * model * position;
										 vColor = color;
									 });

static const char* DEFAULT_FRAG = GLSL(430,
									 in vec4 vColor;
									 in vec2 vTexCoord;

									 layout(location = 9) uniform sampler2D Texture;
									 
									 out vec4 outColor;
									 void main()
									 {
										 outColor = texture(Texture, vTexCoord) * vColor;
									 });

static const char* DEBUG_VERT = GLSL(430,
									   layout(location = 0) in vec4 position;
									   layout(location = 1) in vec4 vertColor;
									   layout(location = 2) uniform mat4 transform;
									   out vec4 inColor;
									   void main()
									   {
									   	   gl_Position = transform * position;
										   inColor = vertColor;
									   });

static const char* DEBUG_FRAG = GLSL(430,
									   in vec4 inColor;
									   out vec4 outColor;
									   void main()
									   {
										   outColor = inColor;
									   });



#pragma endregion

unsigned long getFileLength(std::ifstream& f);
int loadShader(const char* filename, char** shaderSource, unsigned long len);
void unloadShader(unsigned** shaderSource);