#pragma once

#include "Vector2.h"
#include <vector>

namespace JTL
{

	struct CollisionData
	{
		float penDepth;
		Vector2 collisionNormal;
	};

	struct ConvexHull
	{
		Vector2 verts[16];
		size_t size;

		//ConvexHull operator*();
	};

	CollisionData iTest_SAT(const ConvexHull &a, const ConvexHull &b)
	{
		std::vector<Vector2> axes;

		CollisionData cd{ INFINITY };

		for (size_t i = 0; i < a.size; ++i)
			axes.push_back(JTL::normal(a.verts[i] - a.verts[(i + 1) % a.size]).perp());

		for (size_t i = 0; i < b.size; ++i)
			axes.push_back(JTL::normal(b.verts[i] - b.verts[(i + 1) % b.size]).perp());

		for (size_t i = 0; i < axes.size(); ++i)
		{
			float amin = INFINITY;
			float bmin = INFINITY;
			float amax = -INFINITY;
			float bmax = -INFINITY;

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

			if (pdepth < 0) return cd;
		}

		return cd;

	}

	void DebugHull()
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

		ConvexHull objA;
		ConvexHull objB;
		ConvexHull objC;

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

		assert(iTest_SAT(objA, objB).penDepth <  0);
		assert(iTest_SAT(objA, objC).penDepth >= 0);
		assert(iTest_SAT(objB, objC).penDepth <  0);
	}

}