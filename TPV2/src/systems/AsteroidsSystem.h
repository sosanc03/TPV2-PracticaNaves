#pragma once
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Follow.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/Generations.h"
#include "../components/Image.h"

class AsteroidsSystem :public ecs::System
{
public:
	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
		// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
		// de los 10 al principio de cada ronda).
	void update() override;

	void createAsteroids(int n, int g = 3, Vector2D pos_ = Vector2D(-1, -1));// generador de asteroides
	void addAsteroidFrequently();// añade asteroides cada 5 segundos


	void destroyAllAsteroids();// destruye todos los asteroides
	Vector2D generateAstPos();// genera una posición aleatoria en los bordes de la ventana

	void followUpdate(ecs::Entity* a);
	void showAtOppositeSideUpdate(ecs::Entity* a);
private:
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1,
	// y si no hay más asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(ecs::Entity* a);
		// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
		// asteroides, y desactivar el sistema.
	void onRoundOver();
		// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
		// añadir los asteroides iniciales (como en la práctica 1).
	void onRoundStart();
		// El número actual de asteroides en el juego (recuerda que no puede superar un
		// límite)
		int numOfAsteroids_ = 0;
	// Indica si el sistema está activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no está activo)
	bool active_;

	// sprites
	float astWidth_, astHeight_;
	int nF_, nC_;

	int maxAsteroids_;// máximo número de asteroides

	Vector2D sCenter_;// vector central

	int cont_;// contador
};

