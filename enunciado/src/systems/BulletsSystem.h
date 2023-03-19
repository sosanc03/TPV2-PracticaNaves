#pragma once
#include "../CheckML.h"
#include "../ecs/System.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
class BulletsSystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::_sys_BULLET)
		// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
		void recieve(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override {};
	BulletsSystem();
	virtual ~BulletsSystem();
	// Si el juego está parado no hacer nada, en otro caso mover las balas y
	// desactivar las que salen de la ventana como en la práctica 1.
	void update() override;
private:
	// Para gestionar el mensaje de que el jugador ha disparado. Añadir una bala al
	// juego, como en la práctica 1. Recuerda que la rotación de la bala sería
	// vel.angle(Vector2D(0.0f,-1.0f))
	void shoot(Vector2D pos, Vector2D vel, double width, double height,double rotation);
	// Para gestionar el mensaje de que ha habido un choque entre una bala y un
	// asteroide. Desactivar la bala “b”.

	void DisableOnExitUpdate(ecs::Entity* bullet);

	void onCollision_BulletAsteroid(ecs::Entity* b);
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
	// balas, y desactivar el sistema.
	void onRoundOver();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;
	float bulletTime = 0.0;

};