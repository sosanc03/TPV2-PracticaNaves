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
	Manager* mngr_ = nullptr;// manager
	Entity* player_;// jugador
	PlayState* pSt_;// referencia a play state

	
	// sprites
	float astWidth_, astHeight_;
	int nF_, nC_;
	int nAsteroids_;

	int maxAsteroids_;// máximo número de asteroides

	Vector2D sCenter_;// vector central

	int cont_;// contador

public:
	AsteroidsManager(Manager* Manager, Entity* player, PlayState* pSt);// constructora
	void createAsteroids(int n, int g = 3, Vector2D pos_ = Vector2D(-1, -1));// generador de asteroides
	void addAsteroidFrequently();// añade asteroides cada 5 segundos

	
	void destroyAllAsteroids();// destruye todos los asteroides
	void onCollision(Entity* a);// colisión entre bala y asteroide
	
	Vector2D generateAstPos();// genera una posición aleatoria en los bordes de la ventana
};

