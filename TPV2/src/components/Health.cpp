#include "Health.h"

Health::Health(int vidas) : Component() {
	lifes = vidas;
	maxLife = vidas;
}

int Health::getLifes() {
	return lifes;
}

void Health::subLife() {
	lifes--;
}

void Health::resetLifes() {
	lifes = maxLife;
}