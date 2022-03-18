#include "Gun.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"

#include "Transform.h"
#include "DisableOnExit.h"
#include "State.h"

Gun::Gun() :
	tr_(nullptr) {
	initime = sdlutils().currRealTime();
}

Gun::~Gun() {
}

void Gun::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Gun::update() {


	auto gmanager = mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>();

	auto& ihldr = ih();
	if (gmanager->getstate() == State::RUNNING) {

		if (ihldr.keyDownEvent()) {

			if (ihldr.isKeyDown(SDL_SCANCODE_S) && sdlutils().currRealTime() - initime >= 250) {
				// add and entity to the manager
				auto e = mngr_->addEntity(ecs::_grp_BALAS);
				//tranform of the bullet
				auto trS = e->addComponet<Transform>();
				auto s = 20;
				auto rot = tr_->getRot();
				auto pos = tr_->getPos();
				auto& vel = tr_->getVel();
				auto bPos = tr_->getPos() + Vector2D(tr_->getWidth() / 2.0f, tr_->getHeight() / 2.0f) - Vector2D(0.0f, tr_->getHeight() / 2.0f + 5.0f + 12.0f).rotate(rot) - Vector2D(2.0f, 10.0f);
				auto bVel = Vector2D(0.0f, -1.0f).rotate(rot) * (vel.magnitude() + 5.0f);
				trS->init(bPos, bVel, s, s, rot);

				e->addComponet<Image>(&sdlutils().images().at("fire"));
				e->addComponet<DisableOnExit>();
				initime = sdlutils().currRealTime();
				//sound
				sdlutils().soundEffects().at("fire").play(0, 1);

			}

		}
	}

}
