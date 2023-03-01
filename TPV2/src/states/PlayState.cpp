#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() {
	createShip();
	
	// 10 primeros asteroides
	astM_ = new AsteroidsManager(Manager::instance());
	for (int i = 0; i < 5; i++) {
		astM_->createAsteroids(2);
	}
}

PlayState::~PlayState(){

}

void PlayState::update() {
	GameState::update();
	astM_->addAsteroidFrequently();
}


void PlayState::createShip() {
	fighter_ = Manager::instance()->addEntity();
	Vector2D vel_ = Vector2D(0, 0);
	int rot_ = 0;
	Vector2D centralPos_ = Vector2D(sdlutils().width() / 2 - FIGHTER_SIZE / 2, sdlutils().height() / 2 - FIGHTER_SIZE / 2);
	fighter_->addComponent<Transform>(TRANSFORM_H, centralPos_, vel_ , FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	fighter_->addComponent<FighterCtrl>(FIGHTERCTRL_H);
	Texture* text = &(SDLUtils::instance()->images().at("fighter"));
	fighter_->addComponent<Image>(IMAGE_H, text);
	fighter_->addComponent<DeAcceleration>(DEACCELERATION_H);
	int lifes = 3;
	fighter_->addComponent<Health>(HEALTH_H, lifes);
	fighter_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);
	fighter_->addComponent<Gun>(GUN_H);

}