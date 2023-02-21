#include "Health.h"

Health::Health(int vidas) : Component() {
	life = vidas;
	maxLife = vidas;
}

int Health::getLifes() {
	return life;
}

void Health::lessLife() {
	life--;
}

void Health::resetLifes() {
	life = maxLife;
}