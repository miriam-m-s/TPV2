#include "RenderSystem.h"

#include <SDL_rect.h>
#include "../components/FramedImage.h"
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
	drawAsteroids();
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

	SDL_Rect dest = build_sdlrect(fighterTr->pos_, fighterTr->width_,
		fighterTr->height_);

	assert(fighterImg->tex_ != nullptr);
	fighterImg->tex_->render(dest, fighterTr->rot_);

}
