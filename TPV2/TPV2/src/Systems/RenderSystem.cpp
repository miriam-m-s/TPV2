#include "RenderSystem.h"

#include <SDL_rect.h>

#include "../components/FramedImage.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/State.h"

#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

RenderSystem::RenderSystem() {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawFighter();
	drawBullet();
	drawAsteroids();
	drawState();
}
void RenderSystem::drawBullet(){

	for (auto i : mngr_->getEntities(ecs::_grp_BULLETS)){

		auto bulletTr = mngr_->getComponent<Transform>(i);
		auto bulletImg = mngr_->getComponent<Image>(i);

		SDL_Rect dest = build_sdlrect(bulletTr->pos_, bulletTr->width_,
			bulletTr->height_);

		assert(bulletImg->tex_ != nullptr);
		bulletImg->tex_->render(dest, bulletTr->rot_);
		
	}

}

void RenderSystem::drawAsteroids() {
	for (auto i : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {

		auto astTr = mngr_->getComponent<Transform>(i);
		auto astImg = mngr_->getComponent<FramedImage>(i);

		astImg->draw();

		SDL_Rect dest = build_sdlrect(astTr->pos_, astTr->width_,
			astTr->height_);

		assert(astImg->tex_ != nullptr);
		astImg->tex_->render(astImg->m_clip, dest, astTr->rot_);

	}
}

void RenderSystem::drawFighter() {

	auto fighter = mngr_->getHandler(ecs::_hdlr_FIGHTER);
	auto fighterTr = mngr_->getComponent<Transform>(fighter);
	auto fighterImg = mngr_->getComponent<Image>(fighter);
	auto fighterHp = mngr_->getComponent<Health>(fighter);

	SDL_Rect dest = build_sdlrect(fighterTr->pos_, fighterTr->width_,
		fighterTr->height_);

	assert(fighterImg->tex_ != nullptr);
	fighterImg->tex_->render(dest, fighterTr->rot_);

	dest = build_sdlrect(
		20.0f / 2.0f,10.0f,30,30);

	for (int i = 0; i < fighterHp->vidas_; i++) {
		sdlutils().images().at("heart").render(dest);
		dest.x += 60;
	}
}

void RenderSystem::drawState()
{
	auto info = mngr_->getHandler(ecs::_hdlr_GAMEINFO);

	auto state = mngr_->getComponent<State>(info);

	if (state->state != State::RUNNING) {

		// game over message
		if (state->state == State::GAMEOVER) {
		 	auto& t = sdlutils().msgs().at("gameover");
		 	t.render((sdlutils().width() - t.width()) / 2,
		 		(sdlutils().height() - t.height()) / 2);
		}

		// new game message
		else if (state->state == State::NEWGAME) {
		 	auto& t = sdlutils().msgs().at("start");
		 	t.render((sdlutils().width() - t.width()) / 2,
		 		sdlutils().height() / 2 + t.height() * 2);
		}
		else {
		 	auto& t = sdlutils().msgs().at("continue");
		 	t.render((sdlutils().width() - t.width()) / 2,
		 		sdlutils().height() / 2 + t.height() * 2);
		}
	}
}
