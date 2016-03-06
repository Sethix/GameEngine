#include "JMath.h"

int iclamp(const int &v, const int &min, const int &max)
{
	int		 r = v;
	if		(r > max) r = max;
	else if (r < min) r = min;
	return	 r;
}

float fclamp(const float &v, const float &min, const float &max)
{
	float	 r = v;
	if		(r > max) r = max;
	else if (r < min) r = min;
	return	 r;
}

double dclamp(const double &v, const double &min, const double &max)
{
	double	 r = v;
	if		(r > max) r = max;
	else if (r < min) r = min;
	return	 r;
}