#include "BulletsSystem.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/messages.h"

#include "../components/Transform.h"
#include "../components/Image.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void BulletsSystem::recieve(const Message& m)
{
	switch (m.id)
	{
		case _m_ROUND_START:
			onRoundStart();
			break;

		case _m_ROUND_OVER:
			onRoundOver();
			break;
		case _m_FIGHTER_SHOOT:
			shoot(m.fighter_shoot.pos, m.fighter_shoot.vel, m.fighter_shoot.width, m.fighter_shoot.height, m.fighter_shoot.rot);
			active_ = true;
			break;

		case _m_COLLISION_BULLET:
			onCollision_BulletAsteroid(m.bullet_collision.bul);
			break;

		default:
			break;
	}
}

void BulletsSystem::initSystem() {
	active_ = false;
}

void BulletsSystem::update()
{

	if (!active_) return;

	for (auto i : mngr_->getEntities(ecs::_grp_BULLETS)){

		auto bullettr_ = mngr_->getComponent<Transform>(i);

		//limites de X
		if (bullettr_->pos_.getX() + bullettr_->width_ <= 0 || bullettr_->pos_.getX() >= sdlutils().width()- bullettr_->width_) {
			mngr_->setAlive(i,false);
		}

		//limites de Y
		if (bullettr_->pos_.getY() + bullettr_->height_ <= 0 || bullettr_->pos_.getY() >= sdlutils().height() - bullettr_->height_) {
			mngr_->setAlive(i, false);
		}

		bullettr_->move();
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, double rot)
{
	auto bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	
	//tranform of the bullet
	auto bullettr_ = mngr_->addComponent<Transform>(bullet);

	auto s = 20;

	//vel.angle(Vector2D(0.0f,-1.0f));

	auto bPos = pos + Vector2D(width / 2.0f, 
	width / 2.0f) - Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate(rot) - Vector2D(2.0f, 10.0f);

	auto bVel = Vector2D(0.0f, -1.0f).rotate(rot) * (vel.magnitude() + 5.0f);
	bullettr_->init(bPos, bVel, s, s, rot);

	mngr_->addComponent<Image>(bullet, &sdlutils().images().at("fire"));
	//sound
	sdlutils().soundEffects().at("fire").play(0, 1);
}

void BulletsSystem::onCollision_BulletAsteroid(ecs::Entity* b)
{
	mngr_->setAlive(b, false);
}

void BulletsSystem::onRoundOver()
{
	active_ = false;

	for (auto i : mngr_->getEntities(ecs::_grp_BULLETS)) {

		mngr_->setAlive(i, false);
	}
}

void BulletsSystem::onRoundStart()
{
	active_ = true;
}
