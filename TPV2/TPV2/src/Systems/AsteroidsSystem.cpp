#include "AsteroidsSystem.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/messages.h"

#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Follow.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void AsteroidsSystem::initSystem()
{
	active_ = true;
    numOfAsteroids_ = 0;
    createAsteroids(10);
}

void AsteroidsSystem::update()
{
	if (!active_) return;

    for(auto i : mngr_->getEntities(ecs::_grp_ASTEROIDS)){

        auto asteroidstr_ = mngr_->getComponent<Transform>(i);

        if(mngr_->getComponent<Follow>(i) != nullptr){
            follow(asteroidstr_);
        }

        asteroidstr_->move();
        showAtOpposideside(i);
    }
	
}

void AsteroidsSystem::recieve(const Message& m) {
    
}

void AsteroidsSystem::showAtOpposideside(ecs::Entity* s) {

    auto aster_ = mngr_->getComponent<Transform>(s);
    auto& pos = aster_->pos_;
    auto& vel = aster_->vel_;

    if (pos.getX() < -aster_->width_) {
        pos.set(sdlutils().width(), pos.getY());
    }
    else if (pos.getY() <= -aster_->height_) {
        pos.set(pos.getX(), sdlutils().height());
    }
    else if (pos.getX() > sdlutils().width()) {
        pos.set(-aster_->width_, pos.getY());
    }
    else if (pos.getY() >= sdlutils().height()) {
        pos.set(pos.getX(), -aster_->height_);
    }
}

void AsteroidsSystem::follow(Transform* asteroidtr_)
{
    auto fighter = mngr_->getHandler(ecs::_hdlr_FIGHTER);

    auto fightertr_ = mngr_->getComponent<Transform>(fighter);
    
    auto& v = asteroidtr_->vel_;
    auto p = asteroidtr_->pos_;
    auto q = fightertr_->pos_;

    v = v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f);
}

void AsteroidsSystem::createAsteroids(int n)
{
	    if (numOfAsteroids_ + n <= maxAster) {
        for (int i = 0; i < n; i++) {

            auto e = mngr_->addEntity(ecs::_grp_ASTEROIDS);

            auto x = sdlutils().rand().nextInt(0, 2);
            auto y = sdlutils().rand().nextInt(0, 2);

            if (x == 0 && y == 0) {
                x = sdlutils().rand().nextInt(0, sdlutils().width());
            }

            else if (x == 0 && y == 1) {
                y = sdlutils().rand().nextInt(0, sdlutils().width());
            }

            else if (x == 1 && y == 0) {
                y = sdlutils().rand().nextInt(0, sdlutils().height());
                x = sdlutils().width();
            }


            else if (x == 1 && y == 1) {
                x = sdlutils().rand().nextInt(0, sdlutils().width());
                y = sdlutils().height();
            }

            Vector2D p = Vector2D(x, y);

            auto cx = sdlutils().width() / 2.0f;
            auto cy = sdlutils().height() / 2.0f;

            auto c = Vector2D(cx, cy) +
                Vector2D(sdlutils().rand().nextInt(-100, 101), sdlutils().rand().nextInt(-100, 101));

            float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;

            Vector2D v = (c - p).normalize() * speed;

            int g = sdlutils().rand().nextInt(1, 4);

            auto tr = mngr_->addComponent<Transform>(e);
            auto s = 10.0f + 5.0f * g;

            tr->init(p, v, s, s, 0.0f);

            mngr_->addComponent<FramedImage>(e, &sdlutils().images().at("asteroid"), 5, 6);
            mngr_->addComponent<Generations>(e, g);

            if (sdlutils().rand().nextInt(0, 10) < 3) {
                mngr_->addComponent<Follow>(e);
                mngr_->addComponent <FramedImage>(e, &sdlutils().images().at("asteroidgold"),5,6);
            }
        }
        numOfAsteroids_ += n;
    }
}

void AsteroidsSystem::createSonAsteroid(int n, int g, Vector2D transf, Vector2D vel)
{
    if (numOfAsteroids_ + n <= maxAster) {
                for (int i = 0; i < n; i++) {
        
                    auto e = mngr_->addEntity(ecs::_grp_ASTEROIDS);
        
                    auto tr = mngr_->addComponent<Transform>(e);
                    auto s = 10.0f + 5.0f * g;
        
                    tr->init(transf, vel, s, s, 0.0f);
        
                   mngr_->addComponent <FramedImage>(e,&sdlutils().images().at("asteroid"),5,6);
                   // e->addComponet<ShowAtOpposideSide>();
                   mngr_->addComponent<Generations>(e, g);
        
                    if (sdlutils().rand().nextInt(0, 10) < 3) {
                       mngr_->addComponent<Follow>(e);
                       mngr_->addComponent <FramedImage>(e,&sdlutils().images().at("asteroidgold"),5,6);
                    }
        
        
                }
            }
}

void AsteroidsSystem::addAsteroidFrequently()
{
    if (sdlutils().currRealTime() - lastTime >= spawnTime) {

        createAsteroids(1);

        lastTime = sdlutils().currRealTime();
    }
}

void AsteroidsSystem::destroyAllAsteroids()
{
    auto asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

    for (auto i : asteroids) {
        //i->setAlive(false);
    }

    numOfAsteroids_ = 0;
}

void AsteroidsSystem::onCollision(ecs::Entity* a)
{
}

int AsteroidsSystem::getNumActualAst()
{
	return 0;
}
