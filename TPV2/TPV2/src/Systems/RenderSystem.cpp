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
