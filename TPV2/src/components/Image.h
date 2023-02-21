#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

using namespace ecs;

class Image : public Component {
private:
	Texture* texture = nullptr;
	Transform* tr = nullptr;
public:
	Image(Texture* Texture);
	void initComponent();

	void render();
};
