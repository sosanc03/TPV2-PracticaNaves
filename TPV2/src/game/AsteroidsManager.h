#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

class AsteroidsManager{
private:
	Manager* mngr = nullptr;
	int nAsteroids;

public:
	AsteroidsManager(Manager* Manager);

	void createAsteroids(int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(Entity* a);
};

