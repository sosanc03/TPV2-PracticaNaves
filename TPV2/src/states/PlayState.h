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
#include "../utils/Collisions.h"
#include "GameOverState.h"
#include "PauseState.h"



class PlayState : public GameState {
private:
	Entity* fighter_ = nullptr;// nave
	AsteroidsManager* astM_ = nullptr;// asteroid manager
	Health* plHealth_;// vida/salud
	Transform* playerTr_;// transform del player

	Vector2D plCentralPos_;// posición central

	bool sublife, generate;// booleanos de restar vida y generar asteroides
public:
	virtual string getStateID() { return "PlayState"; }; // stringID
	PlayState();// constructora
	~PlayState();// destructora
	void update();// update
	void createShip();// crea una nueva nave
	void playerCollides();// colisión de player y asteroide
	void handlePause();// gestión de pausa

	void checkCollision();// comprueba si hay colisión
	bool collides(Transform* obj1_, Transform* obj2_);// booleano a true si hay colisión entre las entidades
	void GameOver();// fin de juego

	void subLife();// player pierde una vida
};

