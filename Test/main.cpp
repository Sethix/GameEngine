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

using namespace JTL;

int main()
{
	auto &window = Window::instance();
	window.init(800, 800, "WHAT", true, false);

	auto &time = Time::instance();
	time.init();

	auto &input = Input::instance();
	input.init();

	CollisionDetection collisionDetection;
	DynamicResolution dynamicResolution;
	StaticResolution staticResolution;
	RigidbodyDynamics rigidbodyDynamics;
	LifetimeSystem lifetimeSystem;
	PlayerUpdate playerUpdate;
	RenderSystem renderSystem;

	auto &assets = Asset::instance();
	assets.loadTexture("test", 1, 1, "../res/textures/alpacaButBetter.png");

	auto camera = Entity::make();
	camera->camera = Camera::make();
	camera->camera->space = Camera::FULL;

	auto player = Entity::make();
	player->controller = PlayerController::make();
	player->rigidbody = Rigidbody::make();
	player->transform = Transform::make();
	player->collider = Collider::make();
	player->sprite = Sprite::make();
	player->health = Health::make();
	player->mana = Mana::make();

	Vector2 curveTest[8];

	for (int i = 0; i < 8; ++i)
		curveTest[i] = hermite({ 0,0 }, { 10,10 }, { 10,0 }, { 0,10 }, (float)(i + 1) / (float)8);

	//player->lifespan = Lifespan::make();

	player->sprite->assetName = "test";

	player->controller->PlayerNumber = 0;

	player->controller->gravity = 600;

	player->rigidbody->drag = 1;
	
	player->collider->shape = Collider::e_AABB;

	//player->collider->chull.size = 5;
	//player->collider->chull.verts[1] = { -20,-10 };
	//player->collider->chull.verts[2] = { -10,-20 };
	//player->collider->chull.verts[3] = {  10,-20 };
	//player->collider->chull.verts[4] = {  20,-10 };
	//player->collider->chull.verts[0] = {  0 , 10 };

	//player->transform->setScale({ 3,3 });
	player->collider->aabb.min = {-(float)(assets.getTextures("test").width  / assets.getTextures("test").rows) / 2,
								  -(float)(assets.getTextures("test").height / assets.getTextures("test").cols) / 2 };
	player->collider->aabb.max = { (float)(assets.getTextures("test").width  / assets.getTextures("test").rows) / 2,
								   (float)(assets.getTextures("test").height / assets.getTextures("test").cols) / 2 };

	//player->collider->circle.radius = 32;
	player->collider->isTrigger = false;

	player->controller->grounded = true;

	auto ground = Entity::make();
	ground->collider = Collider::make();
	ground->transform = Transform::make();
	ground->lifespan = Lifespan::make();

	ground->collider->shape = Collider::e_AABB;
	ground->collider->aabb.min = { -500,-50 };
	ground->collider->aabb.max = {  500, 50 };

	/*ground->collider->circle.position = { 0, -40 };
	ground->collider->circle.radius = 100;*/

	//ground->collider->chull.size = 5;
	//ground->collider->chull.verts[1] = { -8,-12 };
	//ground->collider->chull.verts[2] = { -4,-24 };
	//ground->collider->chull.verts[3] = {  4,-24 };
	//ground->collider->chull.verts[4] = {  8,-12 };
	//ground->collider->chull.verts[0] = {  0 , 4 };

	auto triangle = Entity::make();
	triangle->collider = Collider::make();
	triangle->transform = Transform::make();
	triangle->lifespan = Lifespan::make();

	triangle->collider->shape = Collider::e_CIRCLE;
	triangle->collider->circle.radius = 1;
	/*triangle->collider->chull.size = 3;
	triangle->collider->chull.verts[0] = { 0,0 };
	triangle->collider->chull.verts[2] = { 1,0 };
	triangle->collider->chull.verts[1] = { 0,1 };*/
	triangle->collider->isTrigger = false;

	triangle->transform->setPosition({ -40,-300 });
	triangle->transform->setScale({ 20,20 });

	ground->transform->setPosition({ 0,-400 });

	//ground->transform->setScale({ 10,10 });

	ground->collider->isTrigger = false;

	DebugDraw temp(ground->collider->getData().at(ground->collider->getIndex()));
	DebugDraw tri(triangle->collider->getData().at(triangle->collider->getIndex()));
	//DebugDraw tempb(player->collider->getData().at(ground->collider->getIndex()));

	player->controller->gamepad = false;
	player->controller->LEFT = KEY_A;
	player->controller->RIGHT = KEY_D;
	player->controller->JUMP = KEY_W;

	while (window.step())
	{
		input.step();

		rigidbodyDynamics.step();
		collisionDetection.step();
		dynamicResolution.step();
		staticResolution.step();
		//lifetimeSystem.step();

		playerUpdate.step();

		player->sprite->tint = { cosf(time.getTotalTime()) * 1.2f, sinf(time.getTotalTime()) * 1.35f, tanf(time.getTotalTime()) * 1.78f, 0.5f };

		camera->camera->pos = -player->transform->getPosition();

		renderSystem.step();

		if(ground > -1) temp.draw(ground->transform->getData().at(ground->transform->getIndex()), camera->camera->getProj() * camera->camera->getView());
		if (triangle > -1) tri.draw(triangle->transform->getData().at(triangle->transform->getIndex()), camera->camera->getProj() * camera->camera->getView());
		//tempb.draw(player->transform->getData().at(player->transform->getIndex()), camera->camera->getProj() * camera->camera->getView());

		//triangle->transform->setAngle(triangle->transform->getAngle() + time.getDeltaTime());

		time.step();
	}

	time.term();
	input.term();
	window.term();

	return 0;
}