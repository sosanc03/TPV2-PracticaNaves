#include "Health.h"

Health::Health(int lifes) : Component() {
	t_ = &(SDLUtils::instance()->images().at("heart"));
	lifes_ = lifes;
	maxHP_ = lifes;
	tSize_ = 50;
}

int Health::getLifes() {
	return lifes_;
}

void Health::subLife() {
	lifes_--;
}

void Health::resetLifes() {
	lifes_ = maxHP_;
}

void Health::render() {
	for (int i = 0; i < lifes_; ++i) {
		SDL_Rect dest = { renderPos.getX(), renderPos.getY(), tSize_, tSize_ };
		t_->render(dest);
		renderPos.setX(renderPos.getX() + tSize_);
	}
	renderPos = Vector2D(0, 0);
}