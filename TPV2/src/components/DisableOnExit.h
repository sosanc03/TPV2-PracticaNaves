#pragma once

#include"../ecs/Entity.h"
#include"../ecs/Component.h"
#include"../sdlutils/SDLUtils.h"
#include "Transform.h"

class DisableOnExit :public Component {
private:
	Transform* tr_ = nullptr;
	int w_, h_;
	int wWidth_, wHeight_;

public:

	void initComponent() {
		tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
		w_ = tr_->getW();
		h_ = tr_->getH();
		wWidth_ = sdlutils().width();
		wHeight_ = sdlutils().height();
	}

	void update() {
		int x = tr_->getPos().getX();
		int y = tr_->getPos().getY();
		if ((x < 0 - w_) || (x + w_ > wWidth_) || (y < 0 - h_) || (y + h_ > wHeight_)) {
			ent_->setAlive(false);
		}
	}
};