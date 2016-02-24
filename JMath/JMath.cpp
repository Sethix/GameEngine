#include "JMath.h"

float fclamp(const float &v, const float &min, const float &max)
{
	float r = v;
	if (r > max) r = max;
	if (r < min) r = min;
	return r;
}