#include "Window.h"
#include "Time.h"
#include "Input.h"
#include "Asset.h"
#include "CollisionDetection.h"
#include "DynamicCollisionResolution.h"
#include "StaticCollisionResolution.h"
#include "PlayerUpdate.h"
#include "Render.h"
#include "RigidbodyDynamics.h"
#include "Entity.h"
#include "DebugDraw.h"
#include "LifetimeSystem.h"
#include "ShaderLoader.h"
#include "JMath.h"

using namespace JTL;

int main()
{
	auto &window = Window::instance();
	window.init(1280, 720, "WHAT", true, false);

	auto &time = Time::instance();
	time.init();

	auto &input = Input::instance();
	input.init();

	auto &assets = Asset::instance();
	
	RenderSystem renderSystem;

	assets.loadMesh("object", "../res/models/cube.obj");
	Shader objectShader(DEFAULT_VERT_3D, DEBUG_FRAG, false);

	assets.loadTexture("alpaca", 1, 1, "../res/textures/alpaca.png");
	Shader alpacaShader(DEFAULT_VERT, DEFAULT_FRAG, false);

	auto cam = Entity::make();
	cam->camera = Camera::make();
	cam->camera->space = Camera::FULL;
	cam->camera->pos = { 0.0,0.0 };
	cam->camera->near = 0.1f;
	cam->camera->far = 200;
	cam->camera->fov = 120;

	auto alp = Entity::make();
	alp->transform = Transform::make();
	alp->sprite = Sprite::make();

	alp->transform->setPosition({ 0.0,0.0 });
	alp->transform->setScale({ 10,10 });
	alp->sprite->assetName = "alpaca";

	Transform testform;
	Matrix4 tMat;
	tMat = ID_MAT4;

	float cSpeed = 20;

	//Matrix4 scalemat = {1,0,0,200,
	//					0,1,0,200,
	//					0,0,1,200,
	//					0,0,0,1 };

	//tMat = scalemat * tMat;

	while (window.step())
	{
		input.step();

		//tMat = Matrix4::translate({ 0,0,-time.getTotalTime() * 50.f}) * Matrix4::scale({ 50,50,50 }) * ID_MAT4;

		if (input.getKey(KEY_A))
			cam->camera->pos += {-1 * time.getDeltaTime() * cSpeed,0,0};

		if (input.getKey(KEY_D))
			cam->camera->pos += {1 * time.getDeltaTime() * cSpeed, 0, 0};

		if (input.getKey(KEY_W))
			cam->camera->pos += {0, 0, -1 * time.getDeltaTime() * cSpeed};

		if (input.getKey(KEY_S))
			cam->camera->pos += {0, 0, 1 * time.getDeltaTime() * cSpeed};

		if (input.getKey(KEY_LEFT_CONTROL))
			cam->camera->pos += {0, -1 * time.getDeltaTime() * cSpeed};

		if (input.getKey(KEY_SPACE))
			cam->camera->pos += {0, 1 * time.getDeltaTime() * cSpeed};

		assets.drawMesh("object", objectShader, { 1.0,1.0,1.0,1.0 }, tMat,cam->camera->getView(),cam->camera->getPersp());
		//assets.drawTexture("alpaca", alpacaShader, { 1.0,1.0,1.0,1.0 }, 0, tMat, cam->camera->getView(), cam->camera->getOrtho());

		//renderSystem.step();

		time.step();
	}

	time.term();
	input.term();
	window.term();

	return 0;
}