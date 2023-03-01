#include "Image.h"
#include "../game/Game.h"

Image::Image(Texture* t, float w, float h, int nFil, int nCol, float s) {
	t_ = t;
	matrix_ = true;
	w_ = w;
	h_ = h;
	nframesF_ = nFil;
	nframesC_ = nCol;
	i = 0;
	cont_ = 0;
	fila_ = 0;
	size_ = s;
}


Image::Image(Texture* t) : Component() {
	t_ = t;
	matrix_ = false;
}

void Image::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
}

void Image::render() {
	SDL_Rect dest_ = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH() };
	if (!matrix_) t_->render(dest_, tr_->getR());
	else
	{
		dest_.h = size_;
		dest_.w = size_;

		SDL_Rect src_;
		src_.x = i * (tr_->getW() / nframesF_);
		src_.y = 0;
		src_.h = tr_->getH() / nframesC_;
		src_.w = tr_->getW() / nframesF_;
		t_->render(src_, dest_, 0, nullptr, SDL_FLIP_NONE);
		if (cont_ >= ANIMATION_SPEED) {
			if (i < nframesC_)i++;
			else i = 0;
			cont_ = 0;
		}
		cont_++;
	}
}