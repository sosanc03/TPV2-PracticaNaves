//#include "Health.h"
//
//Health::Health(int lifes) : Component() {
//	t_ = &(SDLUtils::instance()->images().at("heart"));// textura
//	lifes_ = lifes;// n�mero de vidas
//	maxHP_ = lifes;// vidas m�ximas
//	tSize_ = 50;// tama�o
//	renderPos = Vector2D(0, 0);// posici�n de renderizado
//}
//
//int Health::getLifes() {// devuelve las vidas
//	return lifes_;
//}
//
//void Health::subLife() {// resta una vida
//	lifes_--;
//}
//
//void Health::render() {
//	for (int i = 0; i < lifes_; ++i) {// dibuja tantos corazones como vidas 
//		SDL_Rect dest = { renderPos.getX(), renderPos.getY(), tSize_, tSize_ };
//		t_->render(dest);
//		renderPos.setX(renderPos.getX() + tSize_);
//	}
//	renderPos = Vector2D(0, 0);
//}