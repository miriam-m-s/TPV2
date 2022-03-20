// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL_scancode.h>

class FighterControl: public ecs::Component {
public:


	__CMPID_DECL__(ecs::_FIGHTERCTRL)


	FighterControl() :
		up_(SDL_SCANCODE_UP), //
		right_(SDL_SCANCODE_RIGHT), //
		left_(SDL_SCANCODE_LEFT), //
		speed_(5.0f) //
	{
	}

	inline void setKeys(SDL_Scancode up, SDL_Scancode right, SDL_Scancode left) {
		up_ = up;
		right_ = right;
		left_ = left;
	}

	inline void setSpeed(float speed) {
		speed_ = speed;
	}

	SDL_Scancode up_;
	SDL_Scancode right_;
	SDL_Scancode left_;
	float speed_;
};

