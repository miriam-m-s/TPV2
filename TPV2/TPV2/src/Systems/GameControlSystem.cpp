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
             onCollision_FighterAsteroid(m.fighter_collision.gameOver);
            
            break;

        case  _m_FIGHTER_WIN:
            onAsteroidsExtinction();
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

void GameControlSystem::onCollision_FighterAsteroid(bool h)
{
    auto state_ = mngr_->getComponent<State>(gamemanager);
    if (!h) state_->state = State::PAUSED;
    else {
        state_->state = State::GAMEOVER;
    }
    Message s;
    s.id = _m_ROUND_OVER;
    mngr_->send(s);
  
}

void GameControlSystem::onAsteroidsExtinction()
{
    auto state_ = mngr_->getComponent<State>(gamemanager);
    state_->state = State::GAMEOVER;
}
