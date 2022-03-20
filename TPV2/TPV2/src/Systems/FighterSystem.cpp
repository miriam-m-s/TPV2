#include "FighterSystem.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/Image.h"
#include "../components/FighterControl.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

using ecs::Manager;

void FighterSystem::initSystem()
{
	auto fighter = mngr_->addEntity();
	
	mngr_->setHandler(ecs::_hdlr_FIGHTER, fighter);
	
    fighter_tr = mngr_->addComponent<Transform>(fighter);

    auto s = 50.0f;
    auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;

	fighter_tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	auto fighterImg = mngr_->addComponent<Image>(fighter, &sdlutils().images().at("fighter"));

	auto fighterCtrl = mngr_->addComponent<FighterControl>(fighter);
    auto fighterDeAcc = mngr_->addComponent<DeAcceleration>(fighter);

}

void FighterSystem::update()
{

	auto fighter = mngr_->getHandler(ecs::_hdlr_FIGHTER);

	moveFighter(fighter);

	desaccelarateFighter(fighter);

	fighter_tr->move();
}

void FighterSystem::desaccelarateFighter(ecs::Entity *fighter){
	//DEACCELERATION

	auto desacceleration = mngr_->getComponent<DeAcceleration>(fighter);

	fighter_tr->vel_.set(fighter_tr->vel_ * desacceleration->desa_);

 	if (fighter_tr->vel_.magnitude() < 0.05f) {
		fighter_tr->vel_.set(0.0f, 0.0f);
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
