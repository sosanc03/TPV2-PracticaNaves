// This file is part of the course TPV2@UCM - Samir Genaim
#include "AsteroidsManager.h"
#include "../components/GameCtrl.h"
#include "../components/Image.h"
#include "../components/ShowAtOpposieSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

AsteroidsManager::AsteroidsManager(ecs::Manager* m_) : mngr_(m_), numAsteroids(0)
{
	asteroidTime = sdlutils().currRealTime() / 1000;
}

AsteroidsManager::~AsteroidsManager()
{
}

void AsteroidsManager::createAsteroids(int n)
{
	if (numAsteroids + n <= 30) {
		//Asteroides de tipo A y b aleatoriamente
		for (auto i = 0u; i < n; i++) {
			// Always use the random number generator provided by SDLUtils
			//
			auto& rand = sdlutils().rand();

			// add and entity to the manager
			//
			auto a = mngr_->addEntity();
			a->addToGroup(ecs::_grp_ASTEROIDS);
			auto gen = a->addComponet<Generations>();
			auto g = gen->getGenerations();
			// add a Transform component, and initialise it with random
			// size and position
			//
			auto s = 10.0f + 5.0f * g;

			auto r = rand.nextInt(0, 4);
			auto x = 0;
			auto y = 0;
			//depende de que valor salga, se representa el asteroide en un lateral de la ventana en una pos aleatoria
			switch (r)
			{
			case 0:
				x = rand.nextInt(0, sdlutils().width() - s);
				y = sdlutils().height() - s;
				break;
			case 1:
				x = rand.nextInt(0, sdlutils().width() - s);
				y = s;
				break;
			case 2:
				x = s;
				y = rand.nextInt(0, sdlutils().height() - s);
				break;
			case 3:
				x = sdlutils().width() - s;
				y = rand.nextInt(0, sdlutils().height() - s);
				break;
			default:
				break;
			}
			float speed = rand.nextInt(1, 10) / 10.0f;
			auto rx = rand.nextInt(-100, 100);
			auto ry = rand.nextInt(-100, 100);
			//Centro de la ppantalla
			Vector2D c = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2) + Vector2D(rx, ry);
			//Posicion inicial
			Vector2D p = Vector2D(x, y);
			Vector2D v = (c - p).normalize() * speed;
			auto tr = a->addComponet<Transform>(p, v, s, s, 0.0f);
			//se elige aleatoriamente el tipo de asteroide
			auto tipo = sdlutils().rand().nextInt(0, 100) < 30;

			a->addComponet<FramedImage>(&sdlutils().images().at(tipo ? "asteroid_b" : "asteroid_a"), 5, 6, 20, 30);
			a->addComponet<ShowAtOpposieSide>();


			//si el asteroide es B le añade el componente de seguir al jugador
			if (tipo)a->addComponet<Follow>();
		}
		numAsteroids += n;
	}
}

void AsteroidsManager::AddAsteroidFrecuently()
{
	float time = sdlutils().currRealTime() / 1000;
	if (time - asteroidTime >= 5) {
		createAsteroids(1);
		asteroidTime = sdlutils().currRealTime() / 1000;
	}
}

void AsteroidsManager::destroyAllAsteroids()
{
	auto& asteroids = mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS);
	for (auto n : asteroids) {
		n->setAlive(false);
	}
	numAsteroids = 0;
}

void AsteroidsManager::onCollision(ecs::Entity* c)
{
	int g = c->getComponent<Generations>()->getGenerations();
	g--;
	auto tr = c->getComponent<Transform>();
	if (g > 0 && numAsteroids + 2 <= 30) {
		//Asteroides de tipo A y b aleatoriamentes
		for (auto i = 0u; i < 2; i++) {
			auto r = sdlutils().rand().nextInt(0, 360);
			auto pos = tr->getPos() + tr->getVel().rotate(r) * 2 * std::max(tr->getWidth(), tr->getHeight());
			auto vel_ = tr->getVel().rotate(r) * 1.1f;
			// Always use the random number generator provided by SDLUtils
			//
			auto& rand = sdlutils().rand();

			// add and entity to the manager
			//
			auto a = mngr_->addEntity();
			a->addToGroup(ecs::_grp_ASTEROIDS);
			auto gen = a->addComponet<Generations>();
			gen->setGenerations(g);

			auto tr = a->addComponet<Transform>();
			auto s = 10.0f + 5.0f * g;


			auto rx = rand.nextInt(-100, 100);
			auto ry = rand.nextInt(-100, 100);
			//Centro de la ppantalla
			Vector2D c = new Vector2D(sdlutils().width() / 2, sdlutils().height() / 2) + (rx, ry);
			//Posicion inicial

			tr->init(pos, vel_, s, s, 0.0f);
			//se elige aleatoriamente el tipo de asteroide
			auto tipo = sdlutils().rand().nextInt(0, 100) < 30;

			if (tipo)a->addComponet<Follow>();
			a->addComponet<FramedImage>(&sdlutils().images().at(tipo ? "asteroid_b" : "asteroid_a"), 5, 6, 20, 30);
			a->addComponet<ShowAtOpposieSide>();


			//si el asteroide es B le añade el componente de seguir al jugador
			numAsteroids++;
		}
	}
	numAsteroids--;
	c->setAlive(false);
}

