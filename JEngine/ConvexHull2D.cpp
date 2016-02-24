#include <cassert>
#include <vector>
#include "ConvexHull2D.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "AABB2D.h"
#include "Circle.h"
#include "Plane.h"
#include "Ray2D.h"


namespace JTL
{

	ConvexHull2D operator*(const Matrix3 &m, const ConvexHull2D &a)
	{
		ConvexHull2D r;
		r.size = a.size;

		for (int i = 0; i < a.size; ++i)
		{
			r.verts[i] = (m * Vector3{ a.verts[i].x, a.verts[i].x, 0 }).xy;
		}
		return r;
	}

#pragma region CollisionFunctions

	CollisionData iTest_data(const ConvexHull2D &a, const ConvexHull2D &b)
	{
		std::vector<Vector2> axes;

		CollisionData cd{ INFINITY };

		for (size_t i = 0; i < a.size; ++i)
			axes.push_back(perp(normal(a.verts[i] - a.verts[(i + 1) % a.size])));

		for (size_t i = 0; i < b.size; ++i)
			axes.push_back(perp(normal(b.verts[i] - b.verts[(i + 1) % b.size])));

		for (size_t i = 0; i < axes.size(); ++i)
		{
			float amin = INFINITY;
			float bmin = INFINITY;
			float amax = -INFINITY;
			float bmax = -INFINITY;

			cd.collisionNormal = axes[i];

			for (size_t j = 0; j < a.size; ++j)
			{
				float pp = JTL::dot(axes[i], a.verts[j]);

				amin = fminf(pp, amin);
				amax = fmaxf(pp, amax);
			}

			for (size_t j = 0; j < b.size; ++j)
			{
				float pp = JTL::dot(axes[i], b.verts[j]);

				bmin = fminf(pp, bmin);
				bmax = fmaxf(pp, bmax);
			}

			float pdepth = fminf(amax - bmin, bmax - amin);

			if (pdepth < cd.penDepth)
				cd = { pdepth, axes[i] };

			if (pdepth < 0)
			{
				cd.penDepth = 0;
				return cd;
			}
		}

		return cd;

	}

	CollisionData iTest_data(const ConvexHull2D &a, const AABB2D &b)
	{
		ConvexHull2D temp;

		temp.size = 4;
		
		temp.verts[0] = b.min;
		temp.verts[1] = Vector2{ b.min.x, b.max.y };
		temp.verts[2] = b.max;
		temp.verts[3] = Vector2{ b.max.x, b.min.y };

		std::vector<Vector2> axes;

		CollisionData cd{ INFINITY };

		for (size_t i = 0; i < a.size; ++i)
			axes.push_back(perp(normal(a.verts[i] - a.verts[(i + 1) % a.size])));

		for (size_t i = 0; i < temp.size; ++i)
			axes.push_back(perp(normal(temp.verts[i] - temp.verts[(i + 1) % temp.size])));

		for (size_t i = 0; i < axes.size(); ++i)
		{
			float amin = INFINITY;
			float bmin = INFINITY;
			float amax = -INFINITY;
			float bmax = -INFINITY;

			cd.collisionNormal = axes[i];

			for (size_t j = 0; j < a.size; ++j)
			{
				float pp = JTL::dot(axes[i], a.verts[j]);

				amin = fminf(pp, amin);
				amax = fmaxf(pp, amax);
			}

			for (size_t j = 0; j < temp.size; ++j)
			{
				float pp = JTL::dot(axes[i], temp.verts[j]);

				bmin = fminf(pp, bmin);
				bmax = fmaxf(pp, bmax);
			}

			float pdepth = fminf(amax - bmin, bmax - amin);

			if (pdepth < cd.penDepth)
				cd = { pdepth, axes[i] };

			if (pdepth < 0)
			{
				cd.penDepth = 0;
				return cd;
			}
		}

		return cd;

	}

	CollisionData iTest_data(const ConvexHull2D &a, const Circle &b)
	{
		std::vector<Vector2> axes;

		CollisionData cd{ INFINITY };

		for (size_t i = 0; i < a.size; ++i)
			axes.push_back(perp(normal(a.verts[i] - a.verts[(i + 1) % a.size])));

		for (size_t i = 0; i < axes.size(); ++i)
		{
			float amin = INFINITY;
			float bmin = INFINITY;
			float amax = -INFINITY;
			float bmax = -INFINITY;

			cd.collisionNormal = axes[i];

			for (size_t j = 0; j < a.size; ++j)
			{
				float pp = JTL::dot(axes[i], a.verts[j]);

				amin = fminf(pp, amin);
				amax = fmaxf(pp, amax);
			}


			float pp = JTL::dot(axes[i], b.position);

			bmin = pp - b.radius;
			bmax = pp + b.radius;

			float pdepth = fminf(amax - bmin, bmax - amin);

			if (pdepth < cd.penDepth)
				cd = { pdepth, axes[i] };

			if (pdepth < 0) 
			{ 
				cd.penDepth = 0;
				return cd;
			}
		}

		return cd;

	}

	CollisionData iTest_data(const ConvexHull2D &a, const Plane &b)
	{
		
		CollisionData cd{ INFINITY };

		Vector2 axis = perp(b.normal);

		float amin = INFINITY;
		float bmin = INFINITY;
		float amax = -INFINITY;
		float bmax = -INFINITY;

		cd.collisionNormal = axis;

		for (size_t j = 0; j < a.size; ++j)
		{
			float pp = JTL::dot(axis, a.verts[j]);

			amin = fminf(pp, amin);
			amax = fmaxf(pp, amax);
		}


		float pp = JTL::dot(axis, b.position);

		bmin = fminf(pp, bmin);
		bmax = fmaxf(pp, bmax);

		float pdepth = fminf(amax - bmin, bmax - amin);

		if (pdepth < cd.penDepth)
			cd = { pdepth, axis };

		if (pdepth < 0)
		{
			cd.penDepth = 0;
			return cd;
		}

		return cd;

	}

	CollisionData iTest_data(const ConvexHull2D &a, const Ray2D &b)
	{
		CollisionData cd = { false, INFINITY }; // setup return value

		std::vector<Vector2> axes;

		axes.reserve(a.size);
		for (int i = 0; i < a.size; ++i)
			axes.push_back(perp(normal(a.verts[i] - a.verts[(i + 1) % a.size])));


		float tmin = 0,  //"Entering" scalar for the ray
			tmax = 1;  //"Leaving"  scalar for the ray            

		Vector2 cnormal;

		for (int i = 0; i < axes.size(); ++i)
		{
			float N = dot(axes[i], b.position - a.verts[i]);
			float D = -dot(axes[i], b.direction);

			float t = N / D;

			if (D < 0 && t > tmin)
			{
				tmin = fmaxf(tmin, t);
				cnormal = axes[i];
				cd = {(tmax - tmin) * b.length, axes[i]};
			}
			else    tmax = fminf(tmax, t);

			if (tmin > tmax) 
			{
				cd.penDepth = 0;
				return cd;
			}
		}
		return cd;
	}

#pragma endregion


	void DebugHull2D()
	{
		Vector2 objAptA{ 10,10 };
		Vector2 objAptB{ 20,10 };
		Vector2 objAptC{ 20,20 };
		Vector2 objAptD{ 10,20 };

		Vector2 objBptA{ 150,150 };
		Vector2 objBptB{ 250,150 };
		Vector2 objBptC{ 250,250 };
		Vector2 objBptD{ 150,250 };

		Vector2 objCptA{ 8 , 8 };
		Vector2 objCptB{ 15,25 };
		Vector2 objCptC{ 22, 8 };

		ConvexHull2D objA;
		ConvexHull2D objB;
		ConvexHull2D objC;

		objA.size = 4;
		objB.size = 4;
		objC.size = 3;

		objA.verts[0] = objAptA;
		objA.verts[1] = objAptB;
		objA.verts[2] = objAptC;
		objA.verts[3] = objAptD;

		objB.verts[0] = objBptA;
		objB.verts[1] = objBptB;
		objB.verts[2] = objBptC;
		objB.verts[3] = objBptD;

		objC.verts[0] = objCptA;
		objC.verts[1] = objCptB;
		objC.verts[2] = objCptC;

		assert(iTest_data(objA, objB).penDepth < 0);
		assert(iTest_data(objA, objC).penDepth >= 0);
		assert(iTest_data(objB, objC).penDepth < 0);
	}

}