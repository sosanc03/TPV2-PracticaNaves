#pragma once
#include "GameState.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../components/DeAcceleration.h"
#include "../components/Health.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/Gun.h"

class Game;

class PlayState : public GameState {
private:
	Entity* fighter;
	FighterCtrl* fiCtrl;

public:
	virtual string getStateID() { return "PlayState"; }; // stringID
	PlayState();
	~PlayState();

	void update();
	void handleEvents();
	void createShip();
};

