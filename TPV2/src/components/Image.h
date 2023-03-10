#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"


using namespace ecs;


class Image : public Component {
private:
	Texture* t_ = nullptr;// textura
	Transform* tr_ = nullptr;// transform
	bool matrix_;// mariz 
	float w_, h_, size_;// ancho, alto y tama?o
	int nframesF_, nframesC_, i, cont_, fila_;// info de los sprites

public:
	Image(Texture* t, float w, float h, int nFil, int nCol, float s);// constructora de matriz
	Image(Texture* t);// contructora
	void initComponent();// init

	void render();// render
};
