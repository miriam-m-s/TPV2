
#pragma once
#include "AsteroidsManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "../utils/Vector2D.h"

AsteroidsManager::AsteroidsManager(ecs::Manager* mgr_) : lastTime(sdlutils().currRealTime()), mngr(mgr_)
{
}

void AsteroidsManager::createAsteroids(int n)
{
    if (numAster + n <= maxAster) {
        for (int i = 0; i < n; i++) {

            auto e = mngr->addEntity(ecs::_ASTEROID_GRP );

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

            auto tr = e->addComponet<Transform>();
            auto s = 10.0f + 5.0f * g;

            tr->init(p, v, s, s, 0.0f);

            e->addComponet < FramedImage >(&sdlutils().images().at("asteroid"),5, 6);
            e->addComponet<ShowAtOpposideSide>();
            e->addComponet<Generations>(g);

            if (sdlutils().rand().nextInt(0, 10) < 3) {
                e->addComponet<Follow>(mngr->getHandler(ecs::_hdlr_CAZA));
                e->addComponet < FramedImage >(&sdlutils().images().at("asteroidgold"), 5, 6);
            }
        }
        numAster += n;
    }
}

void AsteroidsManager::createSonAsteroid(int n, int g, Vector2D transf, Vector2D vel)
{
    if (numAster + n <= maxAster) {
        for (int i = 0; i < n; i++) {

            auto e = mngr->addEntity(ecs::_ASTEROID_GRP);

            auto tr = e->addComponet<Transform>();
            auto s = 10.0f + 5.0f * g;

            tr->init(transf, vel, s, s, 0.0f);

            e->addComponet < FramedImage >(&sdlutils().images().at("asteroid"), 5, 6);
            e->addComponet<ShowAtOpposideSide>();
            e->addComponet<Generations>(g);

            if (sdlutils().rand().nextInt(0, 10) < 3) {
                e->addComponet<Follow>(mngr->getHandler(ecs::_hdlr_CAZA));
                e->addComponet < FramedImage >(&sdlutils().images().at("asteroidgold"), 5, 6);
            }


        }
    }
}

void AsteroidsManager::addAsteroidFrequently()
{
    if (sdlutils().currRealTime() - lastTime >= spawnTime) {

        createAsteroids(1);

        lastTime = sdlutils().currRealTime();
    }
}

void AsteroidsManager::destroyAllAsteroids()
{
    auto asteroids = mngr->getEntities(ecs::_ASTEROID_GRP);

    for (auto i : asteroids) {
        i->setAlive(false);
    }

    numAster = 0;
}

void AsteroidsManager::onCollision(ecs::Entity* a)
{
    auto asteroid = a->getComponent<Generations>();

   int g = asteroid->getnumgenerations() - 1;
    numAster--;
    auto num = 0;
    if (2 + numAster <= maxAster)num = 2;
    else num = 1;
    if (g > 0 && g + numAster <= maxAster) {
        for (int i = 0; i < num; i++) {

            auto tr = a->getComponent<Transform>();

            auto r = sdlutils().rand().nextInt(0, 360);
            auto pos = tr->getPos() + tr->getVel().rotate(r) * 2 * std::max(tr->getWidth(), tr->getHeight());
            auto vel = tr->getVel().rotate(r) * 1.1f;

            createSonAsteroid(1, g, pos, vel);
        }
        numAster += g;
    }
    a->setAlive(false);


}

int AsteroidsManager::getNumActualAst()
{
    return numAster;
}