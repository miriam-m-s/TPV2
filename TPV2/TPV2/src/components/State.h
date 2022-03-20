
// // This file is part of the course TPV2@UCM - Samir Genaim

// #pragma once
// #include "../ecs/Component.h"

// class Transform;

// class State : public ecs::Component {
// public:

// 	// This line expands to the following (see the defintion of
// 	// __CMPID_DECL__ en ecs.h):
// 	//
// 	//    constexpr static ecs::cmpId_type id = ecs::_PACMANCTRL
// 	//
	
// 	__CMPID_DECL__(ecs::_STATE)
// 	enum GameState {
// 		NEWGAME = 0, // just before starting a new game
// 		PAUSED, // between rounds
// 		RUNNING, // playing
// 		GAMEOVER // game over
// 	};
// 		State();
// 	virtual ~State();
// 	void render()override;
// 	GameState getstate() {
// 		return state;
// 	}
// 	void setState(GameState gm) {
// 		state = gm;
// 	}

// private :
// 	GameState state;
// };

