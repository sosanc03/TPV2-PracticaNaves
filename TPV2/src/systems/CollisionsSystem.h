#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../utils/Collisions.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

class CollisionsSystem : public ecs::System
{
public:
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// Si el juego est� parado no hacer nada, en otro caso comprobar colisiones como
		// en la pr�ctica 1 y enviar mensajes correspondientes.
	void update() override;

	void checkCollision();
	bool collides(Transform* obj1_, Transform* obj2_);
private:
	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
		// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
		// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
		// onRoundStart, y en update no hacer nada si no est� activo)
		bool active_;

};

