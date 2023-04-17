#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrlSystem.h"

class RenderSystem : public System
{
public:
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
		// - Dibujar las vidas (siempre).
		// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
		// la práctica 1)
	void update() override;

	void renderText();
	void renderFighter();
	void renderHealth();
	void renderBullet();
	void renderAsteroids();
private:
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_.
	void onRoundStart();
	void onRoundOver();
	void onGameStart();
	void onGameOver();
	int winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	int state_; // El estado actual de juego (como en GameCtrlSystem)
	// 0 - START, 1 - PAUSE, 2 - RUNNING
	FighterSystem* fSys_;
	//GameCtrlSystem* gSys_;
};

