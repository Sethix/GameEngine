// TODO : Clean-up

#include "ShaderLoader.h"

unsigned long getFileLength(std::ifstream& f)
{
	if (!f.good()) return 0;

	unsigned long pos = f.tellg();
	f.seekg(0, std::ios::end);
	unsigned long len = f.tellg();
	f.seekg(std::ios::beg);

	return len;
}

int loadShader(const char* filename, char** shaderSource, unsigned long len)
{
	std::ifstream f;

	f.open(filename, std::ios::in);
	if (!f) return -1;

	len = getFileLength(f);
	if (len == 0) return -2;

	*shaderSource = new char[len + 1];
	if (*shaderSource == 0) return -3;

	*shaderSource[len] = 0;

	unsigned int i = 0;
	while (f.good())
	{
		*shaderSource[i] = f.get();
		if (!f.eof())
			++i;
	}
	*shaderSource[i] = 0;

	f.close();

	return 1;
}

void unloadShader(unsigned** shaderSource)
{
	if (*shaderSource != 0)
		delete[] * shaderSource;
	*shaderSource = 0;
}