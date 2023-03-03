#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameStateMachine.h"


class GameOverState :
    public GameState
{
private:
	Entity* text_;// texto
	Texture* t_;// textura
public:
	virtual string getStateID() { return "PauseState"; }; // stringID
	GameOverState();// constructora
	~GameOverState();// destructora
	void update();// update
};

