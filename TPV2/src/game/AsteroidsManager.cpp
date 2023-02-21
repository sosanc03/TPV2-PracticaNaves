#include "AsteroidsManager.h"

void AsteroidsManager::createAsteroids(int n) {
	//if (sdlutils().rand().nextInt(0, 10) < 3){} 30%
	//else{} 70%
}
void AsteroidsManager::addAsteroidFrequently() {
	// Cada cinco segundos:
	//createAsteroids(1);
}
void AsteroidsManager::destroyAllAsteroids() {
	// setAlive(false) a todos los asteroides de la lista de grupo correspondiente del Manager
}
void AsteroidsManager::onCollision(Entity* a) {
	//genera 2 asteroides (si su numero de generaciones lo permite, si hay 29 asteroides solo genera 1, si hay 30 no genera)
	// TENER EN CUENTA QUE HAY nAsteroides-1 YA QUE EL ASTEROIDE DESTRUIDO SE ELIMINA DESPUES

	// Desactiva la entidad tras generar los nuevos
	a->setAlive(false);
}