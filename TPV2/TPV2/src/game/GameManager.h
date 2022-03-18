// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <array>



class GameManager  {
public:

	enum Side {
		LEFT = 0, //
		RIGHT
	};

	enum GameState {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameManager();
	virtual ~GameManager();

	inline GameState getState() {
		return state_;
	}

	inline void setState(GameState state) {
		state_ = state;
	}
	void onBallExit(Side side);
	void resetBall();
	void moveBall();

private:
	
	GameState state_;

	
};

