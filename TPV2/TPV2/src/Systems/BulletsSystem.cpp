#include "BulletsSystem.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/Image.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void BulletsSystem::recieve(const Message& m)
{

}

void BulletsSystem::initSystem() {
}

void BulletsSystem::update()
{

	for (auto i : mngr_->getEntities(ecs::_grp_BALAS)){

		auto bullettr_ = mngr_->getComponent<Transform>(i);

		//limites de X
		if (bullettr_->pos_.getX() + bullettr_->width_ <= 0 || bullettr_->pos_.getX() >= sdlutils().width()- bullettr_->width_) {
			//i->setAlive(false);
		}

		//limites de Y
		if (bullettr_->pos_.getY() + bullettr_->height_ <= 0 || bullettr_->pos_.getY() >= sdlutils().height() - bullettr_->height_) {
			//ent_->setAlive(false);
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	auto bullet = mngr_->addEntity(ecs::_grp_BALAS);
	
	//tranform of the bullet
	auto bullettr_ = mngr_->addComponent<Transform>(bullet);
	auto s = 20;

	auto rot = bullettr_->rot_;
	auto pos = pos;
	auto& vel = vel;

	auto bPos = bullettr_->pos_ + Vector2D(bullettr_->width_ / 2.0f, 
	bullettr_->width_ / 2.0f) - Vector2D(0.0f, bullettr_->height_ / 2.0f + 5.0f + 12.0f).rotate(rot) - Vector2D(2.0f, 10.0f);

	auto bVel = Vector2D(0.0f, -1.0f).rotate(rot) * (vel.magnitude() + 5.0f);
	bullettr_->init(bPos, bVel, s, s, rot);

	mngr_->addComponent<Image>(bullet, &sdlutils().images().at("fire"));
	
}
