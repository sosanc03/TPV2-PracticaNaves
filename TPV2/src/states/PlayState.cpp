#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() {
	plCentralPos_ = Vector2D(sdlutils().width() / 2 - FIGHTER_SIZE / 2, sdlutils().height() / 2 - FIGHTER_SIZE / 2);
	createShip();
	
	// 10 primeros asteroides
	astM_ = new AsteroidsManager(Manager::instance(), fighter_, this);
	astM_->createAsteroids(10, 3);
}

PlayState::~PlayState(){

}

void PlayState::update() {
	GameState::update();
	astM_->addAsteroidFrequently();
	//astM_->checkCollision();
}


void PlayState::createShip() {
	fighter_ = Manager::instance()->addEntity();
	Vector2D vel_ = Vector2D(0, 0);
	int rot_ = 0;
	playerTr_ = fighter_->addComponent<Transform>(TRANSFORM_H, plCentralPos_, vel_ , FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	fighter_->addComponent<FighterCtrl>(FIGHTERCTRL_H);
	Texture* text = &(SDLUtils::instance()->images().at("fighter"));
	fighter_->addComponent<Image>(IMAGE_H, text);
	fighter_->addComponent<DeAcceleration>(DEACCELERATION_H);
	int lifes = 3;
	plHealth_ = fighter_->addComponent<Health>(HEALTH_H, lifes);
	fighter_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);
	fighter_->addComponent<Gun>(GUN_H);

}

void PlayState::playerCollides() {
	playerTr_->setPos(plCentralPos_);// coloca al player en el centro
	for (auto& b : Manager::instance()->getEntities()) {//destruye todas las balas
		if (b->hasGroup(_grp_BULLETS)) {
			b->removeFromGroup(_grp_BULLETS);
			b->setAlive(false);
		}
	}

	astM_->destroyAllAsteroids();// destruye todos los asteroides

	plHealth_->subLife();// quita vida
	if (plHealth_->getLifes() == 0) setEndGame();
}

void PlayState::setEndGame() {
	for (auto& b : Manager::instance()->getEntities()) {//destruye todas las balas
		if (b->hasGroup(_grp_BULLETS)) {
			b->removeFromGroup(_grp_BULLETS);
			b->setAlive(false);
		}
	}
	astM_->destroyAllAsteroids();// destruye todos los asteroides
	fighter_->setAlive(false); // destruye el player
	// llamará a game o hará un cambio de estado para que salga el mensaje de pulsar el espacio
}

