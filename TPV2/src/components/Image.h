#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"


using namespace ecs;


class Image : public Component {
private:
	Texture* t_ = nullptr;
	Transform* tr_ = nullptr;
	bool matrix_;
	float w_, h_, size_;
	int nframesF_, nframesC_, i, cont_, fila_;

public:
	Image(Texture* t, float w, float h, int nFil, int nCol, float s);
	Image(Texture* t);
	void initComponent();

	void render();
};
