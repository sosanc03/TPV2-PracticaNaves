#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Health : public Component {
private:
	Texture* t_ = nullptr;// textura
	Vector2D renderPos;// posición
	int lifes_;// vidas
	int maxHP_;// vida máxima
	int tSize_;// tamaño
public:
	Health(int vidas);// constructora
	int getLifes();// devulve el númerod de vidas
	void subLife();// resta vida
	void render();// render
};
