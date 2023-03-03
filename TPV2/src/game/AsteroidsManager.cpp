#include "AsteroidsManager.h"
#include "../states/PlayState.h"


AsteroidsManager::AsteroidsManager(Manager* manager, Entity* player, PlayState* plSt) {
	mngr_ = manager;// manager
	player_ = player;// figther
	pSt_ = plSt;// play State
	astWidth_ = 510;// ancho de sprite
	astHeight_ = 500;// altura de sprite
	nF_ = 6;// número de filas
	nC_ = 5;// número de columnas
	maxAsteroids_ = 30;// máximo de asteroides 
	sCenter_ = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2);// vector central
	cont_ = 5000;// contador de 5 segundos
}

void AsteroidsManager::createAsteroids(int n, int g, Vector2D pos) {
	int i = 0;
	while (nAsteroids_ < maxAsteroids_ && i < n) {// los asteroides no superan el máximo
		Vector2D pos_;
		if (pos == Vector2D(-1, -1))pos_ = generateAstPos();// posición aleatoria de aparición
		else pos_ = pos;// posición no aleatoria

		
		// vector central pero con un random entre -100 y 100 para que los asteroides vayan a la zona central en un rango
		Vector2D c = sCenter_ + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));

		float speed_ = sdlutils().rand().nextInt(1, 10) / 10.0f;// factor velocidad
		Vector2D vel_ = (c - pos_).normalize() * speed_;// vector velocidad

		float size_ = 25.0f + 8.0f * g;// tamaño

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
		ast_->addComponent<Generations>(GENERATIONS_H, g);// número de generación

		ast_->addToGroup(_grp_ASTEROIDS);// añadir al grupo de asteroides

		nAsteroids_++;// aumenta el número de asteroiodes
		i++;
	}
}

void AsteroidsManager::addAsteroidFrequently() {
	if (sdlutils().currRealTime() >= cont_) {
		int rnd = sdlutils().rand().nextInt(1, 4);// generación entre [0, 4)
		createAsteroids(1, rnd);
		cont_ = sdlutils().currRealTime() + 5000; // 5 secs
	}
}

void AsteroidsManager::destroyAllAsteroids() {
	nAsteroids_ = 0;// número de asteroides a 0
	for (auto& as : Manager::instance()->getEntities()) {
		if (as->hasGroup(_grp_ASTEROIDS)) {
			//desactiva los asteroides y los borra del grupo
			as->removeFromGroup(_grp_ASTEROIDS);
			as->setAlive(false);
		}
	}
}

void AsteroidsManager::onCollision(Entity* a) {
	sdlutils().soundEffects().at("explosion").play();// sonido de explosión
	nAsteroids_--;// resta asteroide

	Generations* gen_ = a->getComponent<Generations>(GENERATIONS_H);
	int g = gen_->getGen();// generación del actual

	if (g != 1) {
		Transform* tr_ = a->getComponent<Transform>(TRANSFORM_H);
		if(g == 2)createAsteroids(2, 1, tr_->getPos()); //Genera los dos nuevos asteroirdes de generación 1
		else createAsteroids(2, 2, tr_->getPos()); //Genera los dos nuevos asteroides de generación 2
	} 

	// Desactiva la entidad tras generar los nuevos
	a->setAlive(false);
	a->removeFromGroup(_grp_ASTEROIDS);
	if (nAsteroids_ == 0) pSt_->GameOver();// victoria
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