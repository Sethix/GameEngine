// TODO : Remake the whole thing

#include "DebugDraw.h"
#include "glfw3.h"
#include "JMath.h"
#include <vector>

namespace JTL
{
	DebugDraw::DebugDraw(const Transform &tform)
	{

		isRigidBody = false;

		Vertex vertices[] = 
		{ 	Vertex(Vector2{ 0,1 }, SHAPECOLOR),
			Vertex(Vector2{ 0,0 }, SHAPECOLOR),
			Vertex(Vector2{ 1,0 }, SHAPECOLOR) };
		mesh = new Mesh(vertices, 3, GL_LINE_STRIP);
	}

	DebugDraw::DebugDraw(const Rigidbody &rbody)
	{

		isRigidBody = true;

		Vertex vertices[] =
		{	Vertex(Vector2{ 1,0 }, SHAPECOLOR),
			Vertex(Vector2{ 0,0 }, SHAPECOLOR)};
		mesh = new Mesh(vertices, 2, GL_LINE_STRIP);
	}

	DebugDraw::DebugDraw(const Collider &coll)
	{

		isRigidBody = false;

		switch (coll.shape)
		{
			case Collider::e_AABB:
			{
				Vertex vertices[] = { Vertex(coll.aabb.max, SHAPECOLOR),
									  Vertex(Vector2{ coll.aabb.min.x, coll.aabb.max.y }, SHAPECOLOR),
									  Vertex(coll.aabb.min, SHAPECOLOR),
									  Vertex(Vector2{ coll.aabb.max.x, coll.aabb.min.y }, SHAPECOLOR) };
				mesh = new Mesh(vertices, 4);
				break;
			}
			case Collider::e_CIRCLE:
			{
				int step = 36;
				
				std::vector<Vertex> vertices;

				float anglePerStep = DEG2RAD(360.0f / step);

				for (unsigned i = 0; i < step; ++i)
					vertices.push_back(Vertex{ Vector2{coll.circle.position.x + cosf(i * anglePerStep) * coll.circle.radius,
													   coll.circle.position.y + sinf(i * anglePerStep) * coll.circle.radius},Vector4{(float)i / step, ((float)i+3) / step * 2, ((float)i + 8) / step * 3 , 1 } });

				mesh = new Mesh(&vertices[0], step);
				break;
			}
			case Collider::e_RAY:
			{
				Vertex vertices[] = { Vertex(coll.ray.position, SHAPECOLOR),
									  Vertex(coll.ray.position +
											(coll.ray.direction *
											 coll.ray.length) , SHAPECOLOR) };
				mesh = new Mesh(vertices, 2);
				break;
			}
			case Collider::e_PLANE:
			{
				Vertex vertices[] = { Vertex(coll.plane.position + (perp(coll.plane.normal) * 30), SHAPECOLOR),
									  Vertex(coll.plane.position - (perp(coll.plane.normal) * 30), SHAPECOLOR) };
				mesh = new Mesh(vertices, 2);
				break;
			}
			case Collider::e_CONVEX:
			{
				std::vector<Vertex> vertices;
			
				for (unsigned i = 0; i < coll.chull.size; ++i)
					vertices.push_back(Vertex{ coll.chull.verts[i], SHAPECOLOR });

				mesh = new Mesh(&vertices[0], coll.chull.size);
				break;
			}
		}
	}

	DebugDraw::~DebugDraw()
	{
		mesh->~Mesh();
		delete mesh;
	}

	void DebugDraw::draw(const Transform &tform, const Matrix4 &proj)
	{
		shader.Bind();
		mesh->DebugDraw(proj * tform.getDrawMatrix());
	}

	void DebugDraw::draw(const Transform &tform, const Rigidbody &rbody, const Matrix4 &proj)
	{
		Transform t;
		t = tform;
		t.setAngle(toAngle(rbody.velocity));
		t.setScale(Vector2{ mag(rbody.velocity) * 100, 1 });

		shader.Bind();
		mesh->DebugDraw(proj * t.getDrawMatrix());

		t = tform;
		t.setAngle(toAngle(rbody.acceleration));
		t.setScale(Vector2{ mag(rbody.acceleration) * 100, 1 });

		mesh->DebugDraw(proj * t.getDrawMatrix());
	}

}
