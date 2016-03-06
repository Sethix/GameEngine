#pragma once

#define PI_F 3.14159265f
#define PI_D 3.1415926535897932
#define DEG2RAD(v) v * 0.0174533
#define RAD2DEG(v) v * 57.2958

int		iclamp(const int		&v, const int		&min, const int		&max);
float	fclamp(const float		&v, const float		&min, const float	&max);
double	dclamp(const double		&v, const double	&min, const double	&max);