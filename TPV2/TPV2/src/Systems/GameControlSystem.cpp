#include "GameControlSystem.h"

#include "../ecs/Manager.h"
#include "../ecs/messages.h"

#include "../sdlutils/InputHandler.h"

#include "../components/State.h"

void GameControlSystem::recieve(const Message& m)
{

    switch (m.id)
    {

        case _m_COLLISION_FIGHTER:

            auto state_ = mngr_->getComponent<State>(gamemanager);

            if (m.fighter_collision.gameOver) state_->state = State::GAMEOVER;
            else {
                state_->state = State::PAUSED;
            }

            break;
    }

}

void GameControlSystem::initSystem()
{
	gamemanager = mngr_->addEntity();

    mngr_->setHandler(ecs::_hdlr_GAMEINFO, gamemanager);

	mngr_->addComponent<State>(gamemanager);
}

void GameControlSystem::update()
{
    auto& ihldr = ih();
    auto state_ = mngr_->getComponent<State>(gamemanager);

    if (state_->state != State::RUNNING) {

        if (ihldr.keyDownEvent()) {

            auto& inhdlr = ih();

            if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {

                Message m;

                switch (state_->state) {

                case  State::NEWGAME:

                    m.id = _m_ROUND_START;
                    state_->state = State::RUNNING;
                    break;

                case  State::PAUSED:

                    state_->state = State::RUNNING;
                    m.id = _m_ROUND_START;
                    break;

                case  State::GAMEOVER:

                    m.id = _m_ROUND_OVER;
                    state_->state = State::NEWGAME;
                    break;
                default:
                    break;
                }

                mngr_->send(m);
            }
        }
    }

}

void GameControlSystem::onCollision_FighterAsteroid()
{
}

void GameControlSystem::onAsteroidsExtinction()
{
}
