#include "Transform.h"

namespace JTL
{

	Transform::Transform()
		: e_parent(nullptr),
		scale({ 1,1 }),
		position({ 0,0 }),
		angle(0) { }


	Transform::~Transform()
	{
		auto t = e_children;
		for each(Transform *child in t)
			child->setParent(e_parent);

		setParent(nullptr);
	}

	void Transform::setParent(Transform *a_parent)
	{
		if (e_parent)
			e_parent->e_children.remove(this);

		if (a_parent)
			a_parent->e_children.push_front(this);

		e_parent = a_parent;
	}

	Matrix3 Transform::getGlobalTransform() const
	{
		return
			Matrix3::rotate(angle)
			* Matrix3::scale(scale)
			* Matrix3::translate(position)
			* (e_parent ? e_parent->getGlobalTransform()
				: ID_MAT3);
	}

	void Transform::setPosition(const Vector2 &a_position)
	{
		position = a_position;
	}

	void Transform::setScale(const Vector2 &a_scale)
	{
		scale = a_scale;
	}

	void Transform::setAngle(float a_angle)
	{
		angle = a_angle;
	}

	Vector2 Transform::getPosition() const
	{
		return position;
	}

	Vector2 Transform::getScale() const
	{
		return scale;
	}

	float Transform::getAngle() const
	{
		return angle;
	}

	Vector2 Transform::getRight() const
	{
		return fromAngle(angle);
	}

	Vector2 Transform::getUp() const
	{
		return perp(fromAngle(angle));
	}

}