#include "FighterSystem.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/messages.h"

#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/Image.h"
#include "../components/FighterControl.h"
#include "../components/Gun.h"
#include "../components/Health.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

using ecs::Manager;

void FighterSystem::recieve(const Message& m)
{
	switch (m.id)
	{

		case _m_ROUND_START:
			onRoundStart();
			break;

		case _m_ROUND_OVER:
			onRoundOver();
			break;

		default:
			break;
	}
}

void FighterSystem::initSystem()
{
	auto fighter = mngr_->addEntity();
	
	mngr_->setHandler(ecs::_hdlr_FIGHTER, fighter);
	
    fighter_tr = mngr_->addComponent<Transform>(fighter);

    auto s = 50.0f;
    auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;

	fighter_tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	mngr_->addComponent<Image>(fighter, &sdlutils().images().at("fighter"));
	mngr_->addComponent<FighterControl>(fighter);
    mngr_->addComponent<DeAcceleration>(fighter);
    mngr_->addComponent<Gun>(fighter);
	mngr_->addComponent<Health>(fighter);

	initTime = sdlutils().currRealTime();

	active_ = false;

}

void FighterSystem::update()
{

	if (!active_) return;

	auto fighter = mngr_->getHandler(ecs::_hdlr_FIGHTER);

	moveFighter(fighter);

	desaccelarateFighter(fighter);

	showAtOpposideSide();

	fighter_tr->move();

	shoot(fighter);
}

void FighterSystem::desaccelarateFighter(ecs::Entity *fighter){
	//DEACCELERATION

	auto desacceleration = mngr_->getComponent<DeAcceleration>(fighter);

	fighter_tr->vel_.set(fighter_tr->vel_ * desacceleration->desa_);

 	if (fighter_tr->vel_.magnitude() < 0.05f) {
		fighter_tr->vel_.set(0.0f, 0.0f);
 	}
}

void FighterSystem::shoot(ecs::Entity* fighter)
{

	auto shoot_ = mngr_->getComponent<Gun>(fighter);

	auto& ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
	
		if (ihdlr.isKeyDown(shoot_->s_) && sdlutils().currRealTime() - initTime >= shoot_->cooldown_) {

			initTime = sdlutils().currRealTime();

			Message m;

			m.id = _m_FIGHTER_SHOOT;
			m.fighter_shoot.height = fighter_tr->height_;
			m.fighter_shoot.width = fighter_tr->width_;
			m.fighter_shoot.pos = fighter_tr->pos_;
			m.fighter_shoot.rot = fighter_tr->rot_;
			m.fighter_shoot.vel = fighter_tr->vel_;

			mngr_->send(m);

		}

	}
}

void FighterSystem::onRoundOver()
{
	active_ = false;

}

void FighterSystem::onRoundStart()
{
	active_ = true;
	auto fighter = mngr_->getHandler(ecs::_hdlr_FIGHTER);


	auto &health = mngr_->getComponent<Health>(fighter)->vidas_;
	if (health <= 0) {
		health = 3;
	}
}

void FighterSystem::showAtOpposideSide()
{
	auto& pos = fighter_tr->pos_;
 	auto& vel = fighter_tr->vel_;

 	if (pos.getX() < -fighter_tr->width_) {
 		pos.set(sdlutils().width(), pos.getY());
 	}
 	else if (pos.getY() <= -fighter_tr->height_) {
 		pos.set(pos.getX(), sdlutils().height() );
 	}
 	else if (pos.getX() > sdlutils().width()) {
 		pos.set(-fighter_tr->width_, pos.getY());
 	}
 	else if (pos.getY() >= sdlutils().height()) {
 		pos.set(pos.getX(), -fighter_tr->height_);
 	}
}

void FighterSystem::moveFighter(ecs::Entity* fighter)
{

	auto fighterCtrl = mngr_->getComponent<FighterControl>(fighter);

	auto& ihdlr = ih();

	if (ihdlr.keyDownEvent()) {

		if (ihdlr.isKeyDown(fighterCtrl->up_)) {

			float speed = std::min(3.0f, fighter_tr->vel_.magnitude() + 1.0f);
			
			fighter_tr->vel_ = Vector2D(0, -speed).rotate(fighter_tr->rot_);
		}
		else if (ihdlr.isKeyDown(fighterCtrl->right_)) {
			fighter_tr->rot_ = fighter_tr->rot_ + fighterCtrl->speed_;
		}
		else if (ihdlr.isKeyDown(fighterCtrl->left_)) {
			fighter_tr->rot_ = fighter_tr->rot_ - fighterCtrl->speed_;
		}
	}
}
