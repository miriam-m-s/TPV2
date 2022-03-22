#include "RenderSystem.h"

#include <SDL_rect.h>
#include "../components/Image.h"
#include "../components/Transform.h"
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
}
void RenderSystem::drawBullet(){

	for (auto i : mngr_->getEntities(ecs::_grp_BALAS)){

		auto bulletTr = mngr_->getComponent<Transform>(i);
		auto bulletImg = mngr_->getComponent<Image>(i);

		SDL_Rect dest = build_sdlrect(bulletTr->pos_, bulletTr->width_,
			bulletTr->height_);

		assert(bulletImg->tex_ != nullptr);
		bulletImg->tex_->render(dest, bulletTr->rot_);
		
	}

}

void RenderSystem::drawFighter() {

	auto fighter = mngr_->getHandler(ecs::_hdlr_FIGHTER);
	auto fighterTr = mngr_->getComponent<Transform>(fighter);
	auto fighterImg = mngr_->getComponent<Image>(fighter);

	SDL_Rect dest = build_sdlrect(fighterTr->pos_, fighterTr->width_,
		fighterTr->height_);

	assert(fighterImg->tex_ != nullptr);
	fighterImg->tex_->render(dest, fighterTr->rot_);

}
