#include "AsteroidsManager.h"


AsteroidsManager::AsteroidsManager(Manager* manager) {
	mngr_ = manager;
	astWidth_ = 510;
	astHeight_ = 500;
	nF_ = 6;
	nC_ = 5;
	maxAsteroids_ = 30;
	sCenter_ = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2);
	cont_ = 5000;
}

void AsteroidsManager::createAsteroids(int n) {
	int i = 0;
	while (nAsteroids_ < maxAsteroids_ && i < n) {

		Entity* ast_ = Manager::instance()->addEntity();
		Texture* t_;

		if (nAsteroids_ < maxAsteroids_) {
			if (sdlutils().rand().nextInt(0, 10) < 3) //tipo b
			{
				t_ = &(SDLUtils::instance()->images().at("goldAsteroid"));
				ast_->addComponent<Follow>(FOLLOW_H);
			}
			else t_ = &(SDLUtils::instance()->images().at("asteroid")); //tipo A
		}

		Vector2D pos_ = generateAstPos();

		Vector2D c = sCenter_ + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));

		float speed_ = sdlutils().rand().nextInt(1, 10) / 10.0f;
		Vector2D vel_ = (c - pos_).normalize() * speed_;

		float size_ = 25.0f + 8.0f * n;

		ast_->addComponent<Transform>(TRANSFORM_H, pos_, vel_, astWidth_, astHeight_);
		ast_->addComponent<Image>(IMAGE_H, t_, astWidth_, astHeight_, nF_, nC_, size_);
		ast_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);
		ast_->addToGroup(_grp_ASTEROIDS);
		nAsteroids_++;
		i++;
	}
}

void AsteroidsManager::addAsteroidFrequently() {
	if (sdlutils().currRealTime() >= cont_) {
		int rnd = sdlutils().rand().nextInt(1, 4);
		createAsteroids(rnd);
		cont_ = sdlutils().currRealTime() + 5000; // 5 secs
	}
}
void AsteroidsManager::destroyAllAsteroids() {
	// setAlive(false) a todos los asteroides de la lista de grupo correspondiente del Manager
}
void AsteroidsManager::onCollision(Entity* a) {
	//genera 2 asteroides (si su numero de generaciones lo permite, si hay 29 asteroides solo genera 1, si hay 30 no genera)
	// TENER EN CUENTA QUE HAY nAsteroides-1 YA QUE EL ASTEROIDE DESTRUIDO SE ELIMINA DESPUES
	createAsteroids(2); //Generar los dos nuevos. 
	// Desactiva la entidad tras generar los nuevos
	a->setAlive(false);
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