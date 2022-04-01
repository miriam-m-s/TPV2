#pragma once
#include "../ecs/Component.h"
#include <SDL_scancode.h>

struct Gun: public ecs::Component {
public:


	__CMPID_DECL__(ecs::_GUNCTRL);


	Gun() :
		s_(SDL_SCANCODE_S),
		cooldown_(250.0f) //
	{
	}

	SDL_Scancode s_;
	float cooldown_;
};


