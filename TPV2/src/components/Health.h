#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Health : public Component {
private:
	Texture* t_ = nullptr;// textura
	Vector2D renderPos;// posici�n
	int lifes_;// vidas
	int maxHP_;// vida m�xima
	int tSize_;// tama�o
public:
	Health(int vidas);// constructora
	int getLifes();// devulve el n�merod de vidas
	void subLife();// resta vida
	void render();// render
};
