// // This file is part of the course TPV2@UCM - Samir Genaim

// #include "GameCtrl.h"

// #include <algorithm>
// #include "../ecs/Manager.h"
// #include "../sdlutils/InputHandler.h"
// #include "../sdlutils/SDLUtils.h"
// #include "../sdlutils/Texture.h"
// #include "Image.h"
// #include "State.h"
// #include "Transform.h"
// #include "../game/AsteroidsManager.h"
// #include "Health.h"




// GameCtrl::GameCtrl(AsteroidsManager* ast):astmngr_(ast)
// {
// }

// GameCtrl::~GameCtrl() {
// }



// void GameCtrl::update() {
// 	auto &ihldr = ih();

// 	auto states =ent_->getComponent<State>();

// 	auto cazavida = mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Health>();
// 	auto state = states->getstate();
// 	if (state != State::RUNNING) {
// 		if (ihldr.keyDownEvent()) {
// 			auto& inhdlr = ih();
// 			if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
// 				switch (state) {
// 				case  State::NEWGAME:			
// 					states->setState(State::RUNNING);
// 					astmngr_->createAsteroids(10);
// 					cazavida->ResetVidas();
// 					break;
// 				case  State::PAUSED:
					
// 					states->setState(State::RUNNING);
// 					astmngr_->createAsteroids(10);
// 					break;
// 				case  State::GAMEOVER:
// 					states->setState(State::NEWGAME);
// 					break;
// 				default:
// 					break;
// 				}
// 			}
// 		}
// 	}
// }

