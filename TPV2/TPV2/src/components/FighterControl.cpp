// // This file is part of the course TPV2@UCM - Samir Genaim

// #include "FighterControl.h"

// #include <cassert>

// #include "../ecs/Entity.h"
// #include "../ecs/Manager.h"
// #include "../sdlutils/InputHandler.h"
// #include "../sdlutils/SDLUtils.h"
// #include "Image.h"
// #include "Transform.h"
// #include "State.h"

// FighterControl::FighterControl() :
// 		tr_(nullptr) {
// }

// FighterControl::~FighterControl() {
// }

// void FighterControl::initComponent() {
// 	tr_ = ent_->getComponent<Transform>();
// 	assert(tr_ != nullptr);
// }

// void FighterControl::update() {
// 	auto gmanager = mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>();

// 	auto &ihldr = ih();
// 	if (gmanager->getstate() == State::RUNNING) {
// 		if (ihldr.keyDownEvent()) {

// 			auto& vel_ = tr_->getVel();
// 			auto rot = tr_->getRot();

// 			if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
// 				tr_->setRot(rot + 5.0f);

			
// 				vel_ = vel_.rotate(5.0f);
// 			}
// 			else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
// 				tr_->setRot(rot - 5.0f);

			
// 				vel_ = vel_.rotate(-5.0f);
// 			}
// 			else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

// 				float speed = std::min(3.0f, vel_.magnitude() + 1.0f);

			
// 				vel_ = Vector2D(0, -speed).rotate(rot);
// 				sdlutils().soundEffects().at("thrust").play(0, 1);
// 			}
		
// 		}
// 	}
	
// }

