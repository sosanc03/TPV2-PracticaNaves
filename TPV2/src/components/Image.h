#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"


using namespace ecs;


class Image : public Component {
private:
	Transform* tr_ = nullptr;// transform
	bool matrix_;// mariz 
	float w_, h_, size_;// ancho, alto y tamaño
	int nframesF_, nframesC_, i, cont_, fila_;// info de los sprites

public:
	Texture* t_ = nullptr;// textura
	Image(Texture* t);// constructora
	Image(Texture* t, float w, float h, int nFil, int nCol, float s);// constructora de matriz
	void initComponent();// init

	void render();// render
};
