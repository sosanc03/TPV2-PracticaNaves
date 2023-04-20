#include "Image.h"
#include "../game/Game.h"

Image::Image(Texture* t, float w, float h, int nFil, int nCol, float s) {
	t_ = t;// textura
	matrix_ = true;// matriz
	w_ = w;// ancho
	h_ = h;// altura
	nframesF_ = nFil;// número de filas
	nframesC_ = nCol;// número de columnas
	i = 0;// primer frame
	cont_ = 0;// contador
	fila_ = 0;// fila
	size_ = s;// tamaño
}


Image::Image(Texture* t) {
	t_ = t;// textura
	matrix_ = false;// matriz
}

void Image::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);// transform
}

void Image::render() {
	SDL_Rect dest_ = { tr_->pos_.getX(), tr_->pos_.getY(), tr_->w_, tr_->h_ };// rectángulo destino
	if (!matrix_) t_->render(dest_, tr_->rot_);
	else
	{
		dest_.h = size_;
		dest_.w = size_;

		SDL_Rect src_;
		src_.x = i * (w_ / nframesF_);
		src_.y = 0;
		src_.h = h_ / nframesC_;
		src_.w = w_ / nframesF_;
		t_->render(src_, dest_, 0, nullptr, SDL_FLIP_NONE);
		if (cont_ >= ANIMATION_SPEED) {
			if (i < nframesC_)i++;
			else i = 0;
			cont_ = 0;
		}
		cont_++;
	}
}