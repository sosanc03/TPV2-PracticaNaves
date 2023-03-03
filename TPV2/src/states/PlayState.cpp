#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() {
	plCentralPos_ = Vector2D(sdlutils().width() / 2 - FIGHTER_SIZE / 2, sdlutils().height() / 2 - FIGHTER_SIZE / 2);
	createShip();
	
	// 10 primeros asteroides
	astM_ = new AsteroidsManager(Manager::instance(), fighter_, this);
	astM_->createAsteroids(10, 3);

	sublife = false;
}

PlayState::~PlayState(){
	delete(fighter_);
	delete(astM_);
	//delete(playerTr_);
	//delete(plHealth_);
}

void PlayState::update() {
	GameState::update();
	handlePause();
	astM_->addAsteroidFrequently();
	astM_->checkCollision();
	if (sublife) {
		astM_->createAsteroids(10, 3);
		sublife = false;
	}
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
	playerTr_->setVel(Vector2D(0, 0));
	playerTr_->setR(-playerTr_->getR());
	for (auto& b : Manager::instance()->getEntities()) {//destruye todas las balas
		if (b->hasGroup(_grp_BULLETS)) {
			b->removeFromGroup(_grp_BULLETS);
			b->setAlive(false);
		}
	}

	astM_->destroyAllAsteroids();// destruye todos los asteroides

	//Manager::instance()->refresh();

	plHealth_->subLife();// quita vida
	if (plHealth_->getLifes() == 0) setEndGame();
	else subLife();
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

void PlayState::handlePause() {
	if (InputHandler::instance()->keyDownEvent()) {
		//Pausa SDL_SCANCODE_SPACE
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
			InputHandler::instance()->refresh();
			GameStateMachine::instance()->pushState(new PauseState());
		}
	}

}

void PlayState::subLife() {
	sublife = true;
	//GameStateMachine::instance()->pushState(new PauseState());
	//astM_->createAsteroids(10, 3);
}

