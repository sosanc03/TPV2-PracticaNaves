#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Health.h"

class GameCtrlSystem : public ecs::System {
public:
	int state_; // El estado actual del juego (en lugar del componente State)
	// 0 - PAUSE, 1 - RUNNING
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;
	// Si el juego no est� parado y el jugador pulsa SDLK_SPACE cambia el estado
	// como en la pr�ctica 1, etc. Tiene que enviar mensajes correspondientes cuando
	// empieza una ronda o cuando empieza una nueva partida.
	void update() override;
private:
	// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay m�s vidas avisar que ha acabado el juego (y quien
	// es el ganador).
	void onCollision_FighterAsteroid();
	// Para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
	// ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();
	//int winner_; // 0 - None, 1 - Asteroids, 2- Fighter

};

