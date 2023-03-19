#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../CheckML.h"
class AsteroidsSystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::_sys_ASTEROIDS)
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void recieve(const Message& m) override;
	// Inicializar el sistema, etc.
	void initSystem() override;

	AsteroidsSystem();
	virtual ~AsteroidsSystem();
	// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
	// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	void update() override;
private:
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1,
	// y si no hay más asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(ecs::Entity* a);
	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
	// asteroides, y desactivar el sistema.
	void onRoundOver();

	void onGameStart();
	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
	// añadir los asteroides iniciales (como en la práctica 1).
	void onRoundStart();
	void createAsteroids(int n);

	void AddAsteroidFrecuently();

	//Seguimiento del jugador
	//Solo para los asteroides con componente follow
	void followUpdate(ecs::Entity* a);

	void showAtOppositeSideUpdate(ecs::Entity* a);

	void deleteAllAsteroids();

	int numAsteroids = 0;
	float asteroidTime = 0;
	// Indica si el sistema está activo o no 
	bool active_;
};

