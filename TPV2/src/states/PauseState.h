#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameStateMachine.h"

class PauseState :public GameState
{
private: 
	Entity* text_;
	Texture* t_;
public:
	virtual string getStateID() { return "PauseState"; }; // stringID
	PauseState();
	~PauseState();
	void update();
};

