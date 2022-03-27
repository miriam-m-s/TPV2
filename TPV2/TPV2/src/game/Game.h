// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include "AsteroidsManager.h"
namespace ecs {
class Manager;
}

class FighterSystem;
class RenderSystem;
class BulletsSystem;
class AsteroidsSystem;
class CollisionsSystem;
class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:

	ecs::Manager *mngr_;

	FighterSystem* fighterSystem_;
	RenderSystem* rendersys_;
	BulletsSystem* bulletSys_;
	AsteroidsSystem* asteroidSystem_;
	CollisionsSystem* colSystem_;
};

