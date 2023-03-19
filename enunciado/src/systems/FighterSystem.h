#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../CheckML.h"
class FighterSystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::_sys_FIGHTER)
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void recieve(const Message& m) override;
	FighterSystem();
	virtual ~FighterSystem();
		// Crear la entidad del caza, a�adir sus componentes, asociarla con un handler
		// correspondiente, etc.
	void initSystem() override;
		// Si el juego est� parado no hacer nada, en otro caso actualizar la velocidad
		// del caza y moverlo como en la pr�ctica 1 (acelerar, desacelerar, etc).
	void update() override;
private:
	// Para reaccionar al mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Poner el caza en el centro con velocidad (0,0) y rotaci�n 0. No
	// hace falta desactivar la entidad (no dibujarla si el juego est� parado).
	void onCollision_FighterAsteroid();

	//M�todos para hacer update de los componentes
	void FighterCtrlUpdate();//update del fighter
	void DecelerateUpdate();//deceleraci�n autom�tica
	void ShowAtOppositeSideUpdate();//cambio de lado de la nave

	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();

	void onGameStart();

	void resetPosition();
	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_;
	ecs::Entity* player;

};

