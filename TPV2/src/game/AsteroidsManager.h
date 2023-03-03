#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Follow.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/Generations.h"

class PlayState;

class AsteroidsManager{
private:
	Manager* mngr_ = nullptr;
	Entity* player_;
	PlayState* pSt_;// referencia a play state

	float astWidth_, astHeight_;
	int nF_, nC_;
	int nAsteroids_;
	int maxAsteroids_;

	Vector2D sCenter_;

	int cont_;

public:
	AsteroidsManager(Manager* Manager, Entity* player, PlayState* pSt);
	void createAsteroids(int n, int g = 3, Vector2D pos_ = Vector2D(-1, -1));
	void addAsteroidFrequently();

	
	void destroyAllAsteroids();
	void onCollision(Entity* a);
	
	Vector2D generateAstPos();
};

