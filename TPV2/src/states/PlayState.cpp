#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() {
	createShip();
}

PlayState::~PlayState(){

}

void PlayState::update() {
	GameState::update();
	handleEvents();
	/*cout << fighter->getComponent<Transform>(_TRANSFORM)->getPos().getX()
		<< fighter->getComponent<Transform>(_TRANSFORM)->getPos().getY()
		<< endl;*/
}

void PlayState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) fiCtrl->handleEvents(event);
}

void PlayState::createShip() {
	fighter = Manager::instance()->addEntity();
	Vector2D v = Vector2D(0, 0);
	int rotation = 0;
	fighter->addComponent<Transform>(_TRANSFORM, v, v, FIGHTER_SIZE, FIGHTER_SIZE, rotation);
	fiCtrl = fighter->addComponent<FighterCtrl>(_CTRL);
	Texture* text = &(SDLUtils::instance()->images().at("fighter"));
	fighter->addComponent<Image>(_IMAGE, text);

	fighter->addComponent<DeAcceleration>(_DEACCELERATION);
	int lifes = 3;
	fighter->addComponent<Health>(_HEALTH, lifes);
	fighter->addComponent<ShowAtOppositeSide>(_OPPOSITESIDE);

	fighter->addComponent<Gun>(_GUN);

}