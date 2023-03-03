#pragma once

#include"../ecs/Entity.h"
#include"../ecs/Component.h"
#include"../sdlutils/SDLUtils.h"
#include "Transform.h"

class DisableOnExit :public Component {
private:
	Transform* tr_ = nullptr;// transform
	int w_, h_;// ancho y alto
	int wWidth_, wHeight_;// ancho y alto de ventana

public:

	void initComponent() {
		tr_ = ent_->getComponent<Transform>(TRANSFORM_H);// componente transform
		w_ = tr_->getW();// anchura de la entidad
		h_ = tr_->getH();// altura de la entidad
		wWidth_ = sdlutils().width();// anchura de la ventana
		wHeight_ = sdlutils().height();// altura de la ventana
	}

	void update() {
		int x = tr_->getPos().getX();
		int y = tr_->getPos().getY();
		// si se sale de los límites de la ventana elimina las balas
		if ((x < 0 - w_) || (x + w_ > wWidth_) || (y < 0 - h_) || (y + h_ > wHeight_)) {
			ent_->removeComponent(_grp_BULLETS);
			ent_->setAlive(false);
		}
	}
};