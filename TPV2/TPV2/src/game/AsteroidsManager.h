#pragma once

#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"

class AsteroidsManager
{

    double lastTime;
    double spawnTime = 5000;
    int numAster = 0, maxAster = 30;
    ecs::Manager* mngr;

public:

    AsteroidsManager(ecs::Manager* mgr_);
    ~AsteroidsManager() {};

    void createAsteroids(int n);
    void createSonAsteroid(int n, int g, Vector2D transf, Vector2D vel);
    void addAsteroidFrequently();
    void destroyAllAsteroids();
    void onCollision(ecs::Entity* a);
    int getNumActualAst();

};