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
	/*delete(fighter_);
	delete(astM_);
	delete(playerTr_);
	delete(plHealth_);*/
}

void PlayState::update() {
	handlePause();
	GameState::update();

	if (generate) {
		astM_->createAsteroids(10, 3);
		generate = false;
	}

	astM_->addAsteroidFrequently();
	checkCollision();
	if (sublife) {
		sublife = false;
		Manager::instance()->refresh();
		GameStateMachine::instance()->pushState(new PauseState());
		generate = true;
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


	plHealth_->subLife();// quita vida
	if (plHealth_->getLifes() == 0) setEndGame();
	else sublife = true;
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
	InputHandler::instance()->refresh();
	if (InputHandler::instance()->keyDownEvent()) {
		//Pausa SDL_SCANCODE_SPACE
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
			GameStateMachine::instance()->pushState(new PauseState());
		}
	}

}

void  PlayState::checkCollision()
{
	Transform* plTr_ = fighter_->getComponent<Transform>(TRANSFORM_H);
	for (auto& as : Manager::instance()->getEntities()) {
		if (as->hasGroup(_grp_ASTEROIDS)) {
			Transform* asTr_ = as->getComponent<Transform>(TRANSFORM_H);
			if (collides(plTr_, asTr_)) playerCollides();// colision entre asteroide y player
			else {
				for (auto& b : Manager::instance()->getEntities()) {
					if (b->hasGroup(_grp_BULLETS)) {
						Transform* bTr_ = b->getComponent<Transform>(TRANSFORM_H);
						if (collides(bTr_, asTr_)) // colisión entre bala y asteroide
						{
							astM_->onCollision(as);
							b->removeFromGroup(_grp_BULLETS);
							b->setAlive(false);
						}
					}
				}
			}
		}
	}
}

bool PlayState::collides(Transform* obj1_, Transform* obj2_) {
	return (Collisions::collidesWithRotation(obj1_->getPos(), obj1_->getW(),
		obj1_->getH(), obj1_->getR(), obj2_->getPos(), obj2_->getW(),
		obj2_->getH(), obj2_->getR()));
	//return false;
}

