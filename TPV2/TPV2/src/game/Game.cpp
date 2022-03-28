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

	//auto caza = mngr_->addEntity();
	//mngr_->setHandler(ecs::_hdlr_CAZA, caza);
	//auto tr = caza->addComponet<Transform>();
	//auto s = 50.0f;
	//auto x = (sdlutils().width() - s) / 2.0f;
	//auto y = (sdlutils().height() - s) / 2.0f;
	//tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	//caza->addComponet < Image >(&sdlutils().images().at("fighter"));
	//caza->addComponet<FighterControl>();
	//caza->addComponet<DeAcceleration>();
	//caza->addComponet<ShowAtOpposideSide>();
	//caza->addComponet<Gun>();
	//caza->addComponet<Health>();
	//// Create the asteroid manager
	//asteroidmanager = new AsteroidsManager(mngr_);
	////Game Control
	//auto gamemanager = mngr_->addEntity();
	//mngr_->setHandler(ecs::_hdlr_GAMEINFO, gamemanager);
	//gamemanager->addComponet<State>();
	//gamemanager->addComponet<GameCtrl>(asteroidmanager);
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();
	//auto gmanager = mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		//mngr_->update();
		mngr_->refresh();
		//if (gmanager->getstate() == State::RUNNING) {
		//	asteroidmanager->addAsteroidFrequently();
		//	checkCollisions();
		//}

		gameControlSystem_->update();

		fighterSystem_->update();
		bulletSys_->update();
		asteroidSystem_->update();
		collisionSystem_->update();

		sdlutils().clearRenderer();
		//mngr_->render();
		rendersys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}