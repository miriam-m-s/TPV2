#include "CollisionSystem.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/messages.h"

#include "../components/Transform.h"
#include "../components/Health.h"

#include "../sdlutils/SDLUtils.h"

#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

#include "../Systems/AsteroidsSystem.h"

void CollisionSystem::recieve(const Message& m)
{
	switch (m.id)
	{

		case _m_ROUND_START:
			onRoundStart();
			break;
		case _m_ROUND_OVER:
			onRoundOver();
			break;
		default:
			break;
	}
}

void CollisionSystem::onRoundOver()
{
	active_ = false;
}

void CollisionSystem::onRoundStart()
{
	active_ = true;
}

void CollisionSystem::initSystem()
{
	astSys_ = mngr_->getSystem<AsteroidsSystem>();
	active_ = false;
}

void CollisionSystem::update()
{

	if (!active_) return;

	auto fighter = mngr_->getHandler(ecs::_hdlr_FIGHTER);
	auto bullets = mngr_->getEntities(ecs::_grp_BULLETS);
	auto asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

	AstFighterCollision(asteroids, fighter);
	AstBulletCollision(asteroids, bullets, fighter);
}

void CollisionSystem::AstFighterCollision(std::vector<ecs::Entity*> asteroids, ecs::Entity* fighter)
{

	auto n = asteroids.size();

	auto fightertr_ = mngr_->getComponent<Transform>(fighter);
	auto fighterhp_ = mngr_->getComponent<Health>(fighter);

	for (auto i = 0u; i < n; i++) {

		auto asteroid = asteroids[i];

		if (mngr_->isAlive(asteroid)) {

			auto asteroidtr_ = mngr_->getComponent<Transform>(asteroid);

			if (Collisions::collides(fightertr_->pos_, fightertr_->width_,
				fightertr_->height_, //
				asteroidtr_->pos_, asteroidtr_->width_, asteroidtr_->height_)) {

				Message m;

				m.id = _m_COLLISION_FIGHTER;

				if (fighterhp_->vidas_ > 1) {
					fightertr_->init(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2), 
						Vector2D(0, 0), fightertr_->width_, fightertr_->height_, 0.0);
					fighterhp_->vidas_ -= 1;
					m.fighter_collision.gameOver = false;
					
				}

				else {
					fightertr_->init(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2),
						Vector2D(0, 0), fightertr_->width_, fightertr_->height_, 0.0);
					m.fighter_collision.gameOver = true;
					fighterhp_->vidas_ -= 1;
				}

				mngr_->send(m);

				sdlutils().soundEffects().at("explosion").play(0, 1);
			}
		}
	}
}

void CollisionSystem::AstBulletCollision(std::vector<ecs::Entity*> asteroids, std::vector<ecs::Entity*> bullets, ecs::Entity* fighter)
{

	auto n = asteroids.size();
	auto b = bullets.size();

	auto fightertr_ = mngr_->getComponent<Transform>(fighter);

	for (auto j = 0u; j < n; j++) {

		auto asteroid = asteroids[j];

		if (mngr_->isAlive(asteroid)) { 

			auto asteroidtr_ = mngr_->getComponent<Transform>(asteroid);

			for (auto i = 0u; i < b; i++) {

				auto bullet = bullets[i];

				if (mngr_->isAlive(bullet)) {

					auto bullettr_ = mngr_->getComponent<Transform>(bullet);

					// check if PacMan collides with the Star (i.e., eat it)
					if (Collisions::collides(asteroidtr_->pos_, asteroidtr_->width_,
						asteroidtr_->height_, //
						bullettr_->pos_, bullettr_->width_, bullettr_->height_)) {

							Message m;

							m.id = _m_COLLISION_BULLET;
							m.bullet_collision.ast = asteroid;
							m.bullet_collision.bul = bullet;

							mngr_->send(m);

							if (astSys_->getNumActualAst() == 0) {
								fightertr_->init(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2),
									Vector2D(0, 0), fightertr_->width_, fightertr_->height_, 0.0);
								
								Message s;
								s.id = _m_FIGHTER_WIN;
								mngr_->send(s);
								//gManager->setState(States::GAMEOVER);
							}

							sdlutils().soundEffects().at("explosion").play(0, 1);
					}
				}
			}
		}
	}
}
