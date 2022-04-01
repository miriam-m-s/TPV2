// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../Systems/FighterSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/BulletsSystem.h"
#include "../Systems/AsteroidsSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/GameControlSystem.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"


using ecs::Manager;

Game::Game() :
		mngr_(nullptr),fighterSystem_(nullptr),rendersys_(nullptr),bulletSys_(nullptr),asteroidSystem_(nullptr), collisionSystem_(nullptr){
}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/asteroid.resources.json");

	mngr_ = new Manager();
	//CAZA COMPONENTS
	
	fighterSystem_ = mngr_->addSystem<FighterSystem>();
    rendersys_=mngr_->addSystem<RenderSystem>();
	bulletSys_ = mngr_->addSystem<BulletsSystem>();
	asteroidSystem_ = mngr_->addSystem<AsteroidsSystem>();
	collisionSystem_ = mngr_->addSystem<CollisionSystem>();
	gameControlSystem_ = mngr_->addSystem<GameControlSystem>();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->refresh();

		gameControlSystem_->update();

		fighterSystem_->update();
		bulletSys_->update();
		asteroidSystem_->update();
		collisionSystem_->update();

		sdlutils().clearRenderer();
		rendersys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}