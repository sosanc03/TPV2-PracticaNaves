#include "Gun.h"

Gun::Gun(float DelayTime) : Component() {
	delayTime = DelayTime;
}

void Gun::initComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM);
}

void Gun::update() {
	/*if (timer->currTime() >= delayTime) {
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
			cout << "dispara";
			timer->reset();
		}
	}
	*/
}