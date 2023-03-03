#include "AsteroidsManager.h"
#include "../states/PlayState.h"


AsteroidsManager::AsteroidsManager(Manager* manager, Entity* player, PlayState* plSt) {
	mngr_ = manager;
	player_ = player;
	pSt_ = plSt;
	astWidth_ = 510;
	astHeight_ = 500;
	nF_ = 6;
	nC_ = 5;
	maxAsteroids_ = 30;
	sCenter_ = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2);
	cont_ = 5000;
}

void AsteroidsManager::createAsteroids(int n, int g, Vector2D pos) {
	int i = 0;
	while (nAsteroids_ < maxAsteroids_ && i < n) {
		Vector2D pos_;
		if (pos == Vector2D(-1, -1))pos_ = generateAstPos();// posición aleatoria de aparición
		else pos_ = pos;

		Vector2D c = sCenter_ + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));

		float speed_ = sdlutils().rand().nextInt(1, 10) / 10.0f;// factor velocidad
		Vector2D vel_ = (c - pos_).normalize() * speed_;// vector velocidad

		float size_ = 25.0f + 8.0f * g;

		Entity* ast_ = Manager::instance()->addEntity();// crea el asteroide
		ast_->addComponent<Transform>(TRANSFORM_H, pos_, vel_, size_, size_);// añade componente transform

		Texture* t_;// textura

		if (nAsteroids_ < maxAsteroids_) {
			if (sdlutils().rand().nextInt(0, 10) < 3) //tipo b
			{
				t_ = &(SDLUtils::instance()->images().at("goldAsteroid"));
				ast_->addComponent<Follow>(FOLLOW_H, player_);// componente follow
			}
			else t_ = &(SDLUtils::instance()->images().at("asteroid")); //tipo A
		}

		

		ast_->addComponent<Image>(IMAGE_H, t_, astWidth_, astHeight_, nF_, nC_, size_);// componente de renderizado
		ast_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
		ast_->addComponent<Generations>(GENERATIONS_H, g);

		ast_->addToGroup(_grp_ASTEROIDS);// añadir al grupo de asteroides

		nAsteroids_++;// aumenta el número de asteroiodes
		i++;
	}
}

void AsteroidsManager::addAsteroidFrequently() {
	if (sdlutils().currRealTime() >= cont_) {
		int rnd = sdlutils().rand().nextInt(1, 4);
		createAsteroids(1, rnd);
		cont_ = sdlutils().currRealTime() + 5000; // 5 secs
	}
}

void  AsteroidsManager::checkCollision()
{
	Transform* plTr_ = player_->getComponent<Transform>(TRANSFORM_H);
	for (auto& as : Manager::instance()->getEntities()) {
		if (as->hasGroup(_grp_ASTEROIDS)) {
			Transform* asTr_ = as->getComponent<Transform>(TRANSFORM_H);
			if (collides(plTr_, asTr_)) pSt_->playerCollides();// colision entre asteroide y player
			else {
				for (auto& b : Manager::instance()->getEntities()) {
					if (b->hasGroup(_grp_BULLETS)) {
						Transform* bTr_ = b->getComponent<Transform>(TRANSFORM_H);
						if (collides(bTr_, asTr_)) // colisión entre bala y asteroide
						{
							onCollision(as);
							b->removeFromGroup(_grp_BULLETS);
							b->setAlive(false);
						}
					}
				}
			}
		}
	}
}

bool AsteroidsManager::collides(Transform* obj1_, Transform* obj2_) {
	return (Collisions::collides(obj1_->getPos(), obj1_->getW(),
		obj1_->getH(), obj2_->getPos(), obj2_->getW(),
		obj2_->getH()));
}

void AsteroidsManager::destroyAllAsteroids() {
	for (auto& as : Manager::instance()->getEntities()) {
		if (as->hasGroup(_grp_ASTEROIDS)) {
			as->removeFromGroup(_grp_ASTEROIDS);
			as->setAlive(false);
		}
	}
}

void AsteroidsManager::onCollision(Entity* a) {
	nAsteroids_--;

	Generations* gen_ = a->getComponent<Generations>(GENERATIONS_H);
	int g = gen_->getGen();// generación del actual

	if (g != 1) {
		Transform* tr_ = a->getComponent<Transform>(TRANSFORM_H);
		if(g == 2)createAsteroids(2, 1, tr_->getPos()); //Genera los dos nuevos de generación 1
		else createAsteroids(2, 2, tr_->getPos()); //Genera los dos nuevos de generación 2
	} 

	// Desactiva la entidad tras generar los nuevos
	a->setAlive(false);
	a->removeFromGroup(_grp_ASTEROIDS);
	if (nAsteroids_ == 0) pSt_->setEndGame();
}

Vector2D AsteroidsManager::generateAstPos() {
	Vector2D pos_;
	int rnd = sdlutils().rand().nextInt(0, 4);
	switch (rnd) {
	case 0: //dr
		rnd = sdlutils().rand().nextInt(0, sdlutils().height());
		pos_ = Vector2D(sdlutils().width(), rnd);
		break;
	case 1: //izq
		rnd = sdlutils().rand().nextInt(0, sdlutils().height());
		pos_ = Vector2D(0, rnd);
		break;
	case 2: //abj
		rnd = sdlutils().rand().nextInt(0, sdlutils().width());
		pos_ = Vector2D(rnd, sdlutils().height());
		break;
	case 3: //arr
		rnd = sdlutils().rand().nextInt(0, sdlutils().width());
		pos_ = Vector2D(rnd, 0);
		break;
	}
	return pos_;
}