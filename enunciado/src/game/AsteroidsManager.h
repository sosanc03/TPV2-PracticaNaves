// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include "../ecs/Entity.h"
namespace ecs {
class Manager;
}
class AsteroidsManager {
public:
	AsteroidsManager(ecs::Manager* m_);
	virtual ~AsteroidsManager();
	void init();
	void start();
	void createAsteroids(int n);
	void AddAsteroidFrecuently();
	void destroyAllAsteroids();
	int getnumAsteroids() {
		return numAsteroids;
	}
	void onCollision(ecs::Entity *c);

private:
	void checkCollisions();
	ecs::Manager* mngr_;
	int numAsteroids;
	float asteroidTime = 0.0f;
};

