#include "Image.h"

Image::Image(Texture* Texture) : Component() {
	texture = Texture;
}

void Image::initComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM);
}

void Image::render() {
	SDL_Rect desR = {tr->getPos().getX(), tr->getPos().getY(), tr->getW(), tr->getH()};
	texture->render(desR, tr->getR());
}