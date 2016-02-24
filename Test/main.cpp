#include "AABB2D.h"
#include "Circle.h"
#include "Plane.h"
#include "Ray2D.h"
//#include "Matrix4.h"

int main()
{
	JTL::DebugAABB2D();
	JTL::DebugCircle();
	JTL::DebugPlane();
	JTL::DebugRay2D();
	//JTL::determinant(JTL::Matrix4{ -9,-2,5,4,
	//								6,-2,-7,1,
	//								1,1,-5,4,
	//								19,15,-1,-16 });

	return 0;
}