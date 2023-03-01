#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Follow.h"
#include "../components/ShowAtOpposideSide.h"


class AsteroidsManager{
private:
	float astWidth_, astHeight_;
	int nF_, nC_;
	Manager* mngr_ = nullptr;
	int nAsteroids_;
	int maxAsteroids_;
	Vector2D sCenter_;

	int cont_;

public:
	AsteroidsManager(Manager* Manager);
	void createAsteroids(int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);
	Vector2D generateAstPos();
};

