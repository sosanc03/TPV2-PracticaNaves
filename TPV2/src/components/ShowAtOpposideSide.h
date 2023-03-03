#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

const float WIDTH = SDLUtils::instance()->width();// ancho de pantalla
const float HEIGHT = SDLUtils::instance()->height();// alto de pantalla
class ShowAtOppositeSide : public Component {
private: 
	Transform* tr_ = nullptr;// transform
	float wWidth_;// ancho de pantalla
	float wHeight_;// alto de pantalla
	float w_;// ancho
	float h_;// alto
	float margin_;// margen

public:
	void initComponent();// inti

	void update();// update
};
