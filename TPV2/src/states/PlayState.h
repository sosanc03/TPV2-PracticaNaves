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
#include "../game/AsteroidsManager.h"


class Game;

class PlayState : public GameState {
private:
	Entity* fighter_ = nullptr;
	AsteroidsManager* astM_ = nullptr;
	Health* plHealth_;
	Transform* playerTr_;

	Vector2D plCentralPos_;

	bool sublife;
public:
	virtual string getStateID() { return "PlayState"; }; // stringID
	PlayState();
	~PlayState();
	void update();
	void createShip();
	void playerCollides();
	void setEndGame();
	void handlePause();
	void subLife();
};

