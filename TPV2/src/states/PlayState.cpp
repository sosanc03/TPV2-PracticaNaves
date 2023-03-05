#include "PlayState.h"
#include "../game/Game.h"

PlayState::PlayState() {
	//posición central
	plCentralPos_ = Vector2D(sdlutils().width() / 2 - FIGHTER_SIZE / 2, sdlutils().height() / 2 - FIGHTER_SIZE / 2);
	createShip();// crea la nave
	
	astM_ = new AsteroidsManager(Manager::instance(), fighter_, this);// instancia de AsteroidsManager
	astM_->createAsteroids(10, 3);// crea 10 asteroides de generación 3

	sublife = false;// perder vida a false
}

PlayState::~PlayState(){
	for (auto& b : Manager::instance()->getEntities()) {//destruye todas las balas
		if (b->hasGroup(_grp_BULLETS)) {
			b->removeFromGroup(_grp_BULLETS);
			b->setAlive(false);
		}
	}
	astM_->destroyAllAsteroids();// destruye todos los asteroides
	fighter_->setAlive(false); // destruye el player
	// llamará a game o hará un cambio de estado para que salga el mensaje de pulsar el espacio
	Manager::instance()->refresh();
	delete(astM_);
}

void PlayState::update() {
	handlePause();
	GameState::update();// update del GameState

	if (generate) {// genera situación incial
		astM_->createAsteroids(10, 3);
		generate = false;
	}

	astM_->addAsteroidFrequently();// genera asteroides cada 5 segundos
	checkCollision();// comprueba colisión
	if (sublife) subLife();// lógica de perder vida
}


void PlayState::createShip() {
	fighter_ = Manager::instance()->addEntity();// nave
	Vector2D vel_ = Vector2D(0, 0);// velocidad incial
	int rot_ = 0;// rotación inicial
	// transform del payer
	playerTr_ = fighter_->addComponent<Transform>(TRANSFORM_H, plCentralPos_, vel_ , FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	fighter_->addComponent<FighterCtrl>(FIGHTERCTRL_H);// componente fighter
	Texture* text = &(SDLUtils::instance()->images().at("fighter"));// textura
	fighter_->addComponent<Image>(IMAGE_H, text);// componente imagen
	fighter_->addComponent<DeAcceleration>(DEACCELERATION_H);// componente de deaceleración
	int lifes = 3;// número de vidas
	plHealth_ = fighter_->addComponent<Health>(HEALTH_H, lifes);// componente de salud
	fighter_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
	fighter_->addComponent<Gun>(GUN_H);// componente bala

}

void PlayState::playerCollides() {
	sdlutils().soundEffects().at("explosion").play();// sonido de expresión
	playerTr_->setPos(plCentralPos_);// coloca al player en el centro
	playerTr_->setVel(Vector2D(0, 0));// velocidad a 0
	playerTr_->setR(-playerTr_->getR());// rotación a 0
	for (auto& b : Manager::instance()->getEntities()) {//destruye todas las balas
		if (b->hasGroup(_grp_BULLETS)) {
			b->removeFromGroup(_grp_BULLETS);
			b->setAlive(false);
		}
	}

	astM_->destroyAllAsteroids();// destruye todos los asteroides


	plHealth_->subLife();// quita vida
	sublife = true;// restar vida
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
	for (auto& as : Manager::instance()->getEntities()) {// recorre las entidades
		if (as->hasGroup(_grp_ASTEROIDS)) {// comprueba que sea un asteroide
			Transform* asTr_ = as->getComponent<Transform>(TRANSFORM_H);
			if (collides(plTr_, asTr_)) playerCollides();// colision entre asteroide y player
			else {
				for (auto& b : Manager::instance()->getEntities()) {// recorre las entidades
					if (b->hasGroup(_grp_BULLETS)) {// comprueba que sea una bala
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
}

void PlayState::GameOver() {
	GameStateMachine::instance()->changeState(new GameOverState());// game Over
}

void PlayState::subLife() {
	sublife = false;
	Manager::instance()->refresh();// limpia el manager de entidades no vidas
	if (plHealth_->getLifes() == 0) {// Game Over
		GameOver();
	}
	else {
		GameStateMachine::instance()->pushState(new PauseState());
		generate = true;// en el próximo update generará 10 nuevos asteroides
	}
}
