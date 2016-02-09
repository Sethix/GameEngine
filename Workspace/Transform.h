#pragma once
#include "Vector2.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include <list>

namespace JTL
{

	class Transform
	{
		Transform *e_parent;
		std::list<Transform*> e_children;
		Vector2 position, scale;
		float angle;
		// Matrix3 local; Updates whenever a setter is used

	public:
		Transform();
		~Transform();

		//Matrix4 version to use with drawing.
		Matrix3 getGlobalTransform() const;

		void setParent(Transform *);
		void setPosition(const Vector2 &);
		void setScale(const Vector2 &);
		void setAngle(float);

		Vector2 getPosition() const;
		Vector2 getScale() const;
		float   getAngle() const;

		Vector2 getRight() const;
		Vector2 getUp() const;
	};

}