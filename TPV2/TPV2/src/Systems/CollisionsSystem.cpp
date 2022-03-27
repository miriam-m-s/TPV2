#include "CollisionsSystem.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/messages.h"

#include "../components/Transform.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "../components/Generations.h"


void CollisionsSystem::recieve(const Message& m)
{
}

void CollisionsSystem::initSystem()
{
}

void CollisionsSystem::update()
{
	auto fighter = mngr_->getHandler(ecs::_hdlr_FIGHTER);

	auto pTR = mngr_->getComponent<Transform>(fighter);
	//	auto cazavida = mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Health>();
		//asteroid group
	auto& asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	//bullets group
	auto& bullets = mngr_->getEntities(ecs::_grp_BALAS);

	//------------------COLLISION WITH FIGHTER AND ASTEROIDS------------------

	auto n = asteroids.size();
	for (auto i = 0u; i < n; i++) {
		auto e = asteroids[i];
		if (mngr_->isAlive(e)) { // if the asteroid is active (it might have died in this frame)
			//cacheamos el tranform del asteroide
			auto eTR = mngr_->getComponent<Transform>(e);
			//Collision with the fighter and the asteroid
			if (Collisions::collidesWithRotation(pTR->pos_, pTR->width_,
				pTR->height_, pTR->rot_,
				eTR->pos_, eTR->width_, eTR->height_, eTR->rot_)) {
				//destroy all asteroids

				//astesys_->destroyAllAsteroids();
				//restar vida al caza
				//cazavida->RestaVidas();

				//poner caza centro de la pantalla
				auto x = (sdlutils().width() - pTR->height_) / 2.0f;
				auto y = (sdlutils().height() - pTR->height_) / 2.0f;
				pTR->init(Vector2D(x, y), Vector2D(), pTR->width_, pTR->width_, 0.0f);
				//Change of state
			/*	auto gmanager = mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>();
				if (cazavida->cuantasvidas() > 0)
					gmanager->setState(State::PAUSED);
				else gmanager->setState(State::GAMEOVER);*/
				//sound
				sdlutils().soundEffects().at("explosion").play(0, 1);
				Message m;
				m.id = _m_COLLISIOM_FIGHTERASTEROID;
				mngr_->send(m);
			}
		}
	}
	//------------------COLLISION WITH BULLETS AND ASTEROIDS------------------
	auto num = bullets.size();
	for (auto j = 0u; j < num; j++) {
		auto b = bullets[j];
		if (mngr_->isAlive(b)) {
			for (auto i = 0u; i < n; i++) {
				auto e = asteroids[i];
				if (mngr_->isAlive(e)) { // if the asteroid is active (it might have died in this frame)
					//asteroid tranform
					auto bTR = mngr_->getComponent<Transform>(b);
					//bullet tranform
					auto eTR = mngr_->getComponent<Transform>(e);

					//Collision with bullet and asteroids
					if (Collisions::collidesWithRotation(eTR->pos_, eTR->width_,
						eTR->height_, eTR->rot_,//
						bTR->pos_, bTR->width_, bTR->height_, bTR->rot_)) {
						mngr_->setAlive(b, false);
						//asteroidmanager->onCollision(e);
						//if there are no asteroids the fighter wins
						//if (asteroidmanager->getNumActualAst() == 0) {
						//	auto gmanager = mngr_->getHandler(ecs::_hdlr_GAMEINFO)->getComponent<State>();
						//	//poner caza centro de la pantalla
						//	auto x = (sdlutils().width() - pTR->getWidth()) / 2.0f;
						//	auto y = (sdlutils().height() - pTR->getHeight()) / 2.0f;
						//	pTR->init(Vector2D(x, y), Vector2D(), pTR->getWidth(), pTR->getHeight(), 0.0f);
						//	gmanager->setState(State::GAMEOVER);
						//}
						//sound
						sdlutils().soundEffects().at("explosion").play(0, 1);
						Message m;
						m.id = _m_COLLISION_BULLETASTEROID;
						m.divide_asteroid.ent=e;
				
						mngr_->send(m);

					}
				}
			}
		}

	}
}

void CollisionsSystem::onRoundOver()
{
}

void CollisionsSystem::onRoundStart()
{
}

