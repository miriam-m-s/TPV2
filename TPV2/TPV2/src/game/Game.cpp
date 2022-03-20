// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../Systems/FighterSystem.h"
#include "../Systems/RenderSystem.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "AsteroidsManager.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Health.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"


using ecs::Manager;

Game::Game() :
		mngr_(nullptr), asteroidmanager(nullptr),fighterSystem_(nullptr),rendersys_(nullptr){
}

Game::~Game() {
	delete mngr_;
	delete asteroidmanager;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/asteroid.resources.json");

	mngr_ = new Manager();
	//CAZA COMPONENTS
	
	fighterSystem_ = mngr_->addSystem<FighterSystem>();
    rendersys_=mngr_->addSystem<RenderSystem>();
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

		fighterSystem_->update();
		
		sdlutils().clearRenderer();
		//mngr_->render();
		rendersys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

//void Game::checkCollisions() {
//
//
//	//caza tranform and health
//	auto pTR = mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Transform>();
//	auto cazavida = mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Health>();
//	//asteroid group
//	auto &asteroids = mngr_->getEntities(ecs::_ASTEROID_GRP);
//	//bullets group
//	auto& bullets = mngr_->getEntities(ecs::_grp_BALAS);
//
//	//------------------COLLISION WITH FIGHTER AND ASTEROIDS------------------
//
//	auto n = asteroids.size();
//	for (auto i = 0u; i < n; i++) {
//		auto e = asteroids[i];
//		if (e->isAlive()) { // if the asteroid is active (it might have died in this frame)
//			//cacheamos el tranform del asteroide
//			auto eTR = e->getComponent<Transform>();
//			//Collision with the fighter and the asteroid
//			if (Collisions::collidesWithRotation(pTR->getPos(), pTR->getWidth(),
//				pTR->getHeight(), pTR->getRot(),
//				eTR->getPos(), eTR->getWidth(), eTR->getHeight(), eTR->getRot())) {
//				//destroy all asteroids
//				asteroidmanager->destroyAllAsteroids();
//				//restar vida al caza
//				cazavida->RestaVidas();
//
//				//poner caza centro de la pantalla
//				auto x = (sdlutils().width() - pTR->getWidth()) / 2.0f;
//				auto y = (sdlutils().height() - pTR->getHeight()) / 2.0f;
//				pTR->init(Vector2D(x, y), Vector2D(), pTR->getWidth(), pTR->getHeight(), 0.0f);
//				//Change of state
//				auto gmanager = mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>();
//				if (cazavida->cuantasvidas() > 0) 				
//					gmanager->setState(State::PAUSED);
//				else gmanager->setState(State::GAMEOVER);
//				//sound
//				sdlutils().soundEffects().at("explosion").play(0, 1);
//			}
//		}
//	}
//	//------------------COLLISION WITH BULLETS AND ASTEROIDS------------------
//	auto num = bullets.size();
//	for (auto j = 0u; j < num; j++) {
//		auto b = bullets[j];
//		if (b->isAlive()) {
//			for (auto i = 0u; i < n; i++) {
//				auto e = asteroids[i];
//				if (e->isAlive()) { // if the asteroid is active (it might have died in this frame)
//					//asteroid tranform
//					auto eTR = e->getComponent<Transform>();
//					//bullet tranform
//					auto bTR = b->getComponent<Transform>();
//
//					//Collision with bullet and asteroids
//					if (Collisions::collidesWithRotation(eTR->getPos(), eTR->getWidth(),
//						eTR->getHeight(), eTR->getRot(),//
//						bTR->getPos(), bTR->getWidth(), bTR->getHeight(), bTR->getRot())) {
//						b->setAlive(false);
//						asteroidmanager->onCollision(e);
//						//if there are no asteroids the fighter wins
//						if (asteroidmanager->getNumActualAst() == 0) {
//							auto gmanager = mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>();
//							//poner caza centro de la pantalla
//							auto x = (sdlutils().width() - pTR->getWidth()) / 2.0f;
//							auto y = (sdlutils().height() - pTR->getHeight()) / 2.0f;
//							pTR->init(Vector2D(x, y), Vector2D(), pTR->getWidth(), pTR->getHeight(), 0.0f);
//							gmanager->setState(State::GAMEOVER);
//						}
//						//sound
//						sdlutils().soundEffects().at("explosion").play(0, 1);
//						
//					}
//				}
//			}
//		}
//		
//	}
//	
//}
