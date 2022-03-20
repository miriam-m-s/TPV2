// #include "State.h"
// #include "../sdlutils/SDLUtils.h"


// State::State():state(State::NEWGAME)
// {
// }

// State::~State()
// {
// }

// void State::render()
// {
	
// 	// message when game is not running
// 	if (state != RUNNING) {

// 		// game over message
// 		if (state == GAMEOVER) {
// 			auto& t = sdlutils().msgs().at("gameover");
// 			t.render((sdlutils().width() - t.width()) / 2,
// 				(sdlutils().height() - t.height()) / 2);
// 		}

// 		// new game message
// 		if (state == NEWGAME) {
// 			auto& t = sdlutils().msgs().at("start");
// 			t.render((sdlutils().width() - t.width()) / 2,
// 				sdlutils().height() / 2 + t.height() * 2);
// 		}
// 		else {
// 			auto& t = sdlutils().msgs().at("continue");
// 			t.render((sdlutils().width() - t.width()) / 2,
// 				sdlutils().height() / 2 + t.height() * 2);
// 		}
// 	}
// }



