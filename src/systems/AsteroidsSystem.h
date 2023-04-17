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

class FighterSystem;

class AsteroidsSystem :public System
{
public:
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;
		// Inicializar el sistema, etc.
	void initSystem() override;
		// Si el juego est� parado no hacer nada, en otro caso mover los asteroides como
		// en la pr�ctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
		// de los 10 al principio de cada ronda).
	void update() override;

	void createAsteroids(int n, int g = 3, Vector2D pos_ = Vector2D(-1, -1));// generador de asteroides
	void addAsteroidFrequently();// a�ade asteroides cada 5 segundos


	void destroyAllAsteroids();// destruye todos los asteroides
	Vector2D generateAstPos();// genera una posici�n aleatoria en los bordes de la ventana

	void followUpdate(Entity* a);
	void showAtOppositeSideUpdate(Entity* a);
private:
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide �a� y crear 2 asteroides como en la pr�ctica 1,
	// y si no hay m�s asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(Entity* a);
		// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
		// asteroides, y desactivar el sistema.
	void onRoundOver();
		// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
		// a�adir los asteroides iniciales (como en la pr�ctica 1).
	void onRoundStart();
		// El n�mero actual de asteroides en el juego (recuerda que no puede superar un
		// l�mite)
		int numOfAsteroids_ = 0;
	// Indica si el sistema est� activo o no (modificar el valor en onRoundOver y
	// onRoundStart, y en update no hacer nada si no est� activo)
	bool active_;

	// sprites
	float astWidth_, astHeight_;
	int nF_, nC_;

	int maxAsteroids_;// m�ximo n�mero de asteroides

	Vector2D sCenter_;// vector central
	FighterSystem* fSys_;
	int cont_;// contador
};

