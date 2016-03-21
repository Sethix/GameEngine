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

using namespace JTL;

int main()
{
	auto &window = Window::instance();
	window.init(1920, 1080, "WHAT", false, true);

	auto &time = Time::instance();
	time.init();

	auto &input = Input::instance();
	input.init();

	CollisionDetection collisionDetection;
	DynamicResolution dynamicResolution;
	StaticResolution staticResolution;
	RigidbodyDynamics rigidbodyDynamics;
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

	player->sprite->assetName = "test";

	player->controller->gravity = 600;

	//player->rigidbody->drag = 1;
	
	player->collider->shape = Collider::e_AABB;
	player->collider->aabb.min = {-(float)(assets.getTextures("test").width  / assets.getTextures("test").rows) / 2,
								  -(float)(assets.getTextures("test").height / assets.getTextures("test").cols) / 2 };
	player->collider->aabb.max = { (float)(assets.getTextures("test").width  / assets.getTextures("test").rows) / 2,
								   (float)(assets.getTextures("test").height / assets.getTextures("test").cols) / 2 };

	auto ground = Entity::make();
	ground->collider = Collider::make();
	ground->transform = Transform::make();

	ground->collider->shape = Collider::e_AABB;
	ground->collider->aabb.min = { -500,-50 };
	ground->collider->aabb.max = {  500, 50 };

	ground->transform->setPosition({ 0,-400 });

	DebugDraw temp(ground->collider->getData().at(ground->collider->getIndex()));

	while (window.step())
	{
		input.step();

		rigidbodyDynamics.step();
		collisionDetection.step();
		dynamicResolution.step();
		staticResolution.step();

		playerUpdate.step();

		//player->sprite->tint = { cosf(time.getTotalTime()) * 1.2f, sinf(time.getTotalTime()) * 1.35f, tanf(time.getTotalTime()) * 1.78f, 1 };

		camera->camera->pos = -player->transform->getPosition();

		renderSystem.step();

		temp.draw(ground->transform->getData().at(ground->transform->getIndex()), camera->camera->getProj() * camera->camera->getView());
		time.step();
	}

	time.term();
	input.term();
	window.term();

	return 0;
}