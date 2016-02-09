#include "sfwdraw.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Transform.h"
#include "Rigidbody.h"

using namespace JTL;

int main()
{

	sfw::initContext();

	int  handle = sfw::loadTextureMap("../SFW/alpacaButBetter.png");
	float x = 1, y = 1;
	float angle = 0;
	float speed = 800;
	float angularSpeed = 400;
	float drag = 10;
	float angularDrag = 5;

	Matrix3 mat;

	Transform t;

	Transform ta[4];

	Transform tb[4];

	Transform to;

	Transform tao[4];

	Rigidbody r;

	ta[0].setParent(&to);
	ta[1].setParent(&to);
	ta[2].setParent(&to);
	ta[3].setParent(&to);

	tb[0].setParent(&tao[0]);
	tb[1].setParent(&tao[1]);
	tb[2].setParent(&tao[2]);
	tb[3].setParent(&tao[3]);

	to.setParent(&t);

	tao[0].setParent(&ta[0]);
	tao[1].setParent(&ta[1]);
	tao[2].setParent(&ta[2]);
	tao[3].setParent(&ta[3]);

	t.setPosition({ x,y });
	t.setAngle(angle);
	t.setScale({ 80,80 });
	r.drag = drag;
	r.angularDrag = angularDrag;

	while (sfw::stepContext())
	{
		if (sfw::getKey('S')) r.addForce({  0,-speed });
		if (sfw::getKey('W')) r.addForce({  0, speed });
		if (sfw::getKey('A')) r.addForce({ -speed, 0 });
		if (sfw::getKey('D')) r.addForce({  speed, 0 });
		if (sfw::getKey('Q')) r.addTorque(-angularSpeed);
		if (sfw::getKey('E')) r.addTorque(angularSpeed);

		to.setPosition({ 0,0 });
		to.setAngle(sfw::getTime());
		to.setScale({ 1,1 });


		tao[0].setPosition({ 0,0 });
		tao[0].setAngle(-sfw::getTime());
		tao[0].setScale({ 1,1 });

		tao[1].setPosition({ 0,0 });
		tao[1].setAngle(-sfw::getTime());
		tao[1].setScale({ 1,1 });

		tao[2].setPosition({ 0,0 });
		tao[2].setAngle(-sfw::getTime());
		tao[2].setScale({ 1,1 });

		tao[3].setPosition({ 0,0 });
		tao[3].setAngle(-sfw::getTime());
		tao[3].setScale({ 1,1 });


		ta[0].setPosition({ 1,1 });
		ta[0].setAngle({ -sfw::getTime() });
		ta[0].setScale({ 0.8f, 0.8f });

		ta[1].setPosition({ 1,-1 });
		ta[1].setAngle({ -sfw::getTime() });
		ta[1].setScale({ 0.8f, 0.8f });

		ta[2].setPosition({ -1,1 });
		ta[2].setAngle({ -sfw::getTime() });
		ta[2].setScale({ 0.8f, 0.8f });

		ta[3].setPosition({ -1,-1 });
		ta[3].setAngle({ -sfw::getTime() });
		ta[3].setScale({ 0.8f, 0.8f });


		tb[0].setPosition({ 1,1 });
		tb[0].setAngle({ -sfw::getTime() });
		tb[0].setScale({ 0.8f, 0.8f });

		tb[1].setPosition({ 1,-1 });
		tb[1].setAngle({ -sfw::getTime() });
		tb[1].setScale({ 0.8f, 0.8f });

		tb[2].setPosition({ -1,1 });
		tb[2].setAngle({ -sfw::getTime() });
		tb[2].setScale({ 0.8f, 0.8f });

		tb[3].setPosition({ -1,-1 });
		tb[3].setAngle({ -sfw::getTime() });
		tb[3].setScale({ 0.8f, 0.8f });


		r.integrate(&t, sfw::getDeltaTime());


		sfw::drawTextureMatrix(handle, 0, WHITE, matrix3To4(t.getGlobalTransform()).m);

		sfw::drawTextureMatrix(handle, 0, CYAN, matrix3To4((ta[0].getGlobalTransform())).m);
		sfw::drawTextureMatrix(handle, 0, MAGENTA, matrix3To4((ta[1].getGlobalTransform())).m);
		sfw::drawTextureMatrix(handle, 0, YELLOW, matrix3To4((ta[2].getGlobalTransform())).m);
		sfw::drawTextureMatrix(handle, 0, BLACK, matrix3To4((ta[3].getGlobalTransform())).m);

		sfw::drawTextureMatrix(handle, 0, CYAN, matrix3To4((tb[0].getGlobalTransform())).m);
		sfw::drawTextureMatrix(handle, 0, MAGENTA, matrix3To4((tb[1].getGlobalTransform())).m);
		sfw::drawTextureMatrix(handle, 0, YELLOW, matrix3To4((tb[2].getGlobalTransform())).m);
		sfw::drawTextureMatrix(handle, 0, BLACK, matrix3To4((tb[3].getGlobalTransform())).m);

	}
	sfw::termContext();

	return 0;

}