#include "AsteroidsSystem.h"

void AsteroidsSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _MSG_COL_AST_PLAYER:
		destroyAllAsteroids();
		break;
	case _MSG_COL_AST_BULLET:
		onCollision_AsteroidBullet(m.hitBulAst.asteroid_);
		break;
	case _MSG_START:
		initSystem();
		break;
	case _MSG_RESUME:
		onRoundStart();
	default:
		break;
	}
}

void AsteroidsSystem::initSystem() {
	active_ = true;
	createAsteroids(10, 3);
	cont_ = 5000;
}

void AsteroidsSystem::update() {
	if (active_) {
		addAsteroidFrequently();
		for (auto a : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {
			showAtOppositeSideUpdate(a);
			followUpdate(a);
			mngr_->getComponent<Transform>(a)->move();
		}
	}
}

void AsteroidsSystem::onCollision_AsteroidBullet(ecs::Entity* a) {
	sdlutils().soundEffects().at("explosion").play();// sonido de explosión
	numOfAsteroids_--;// resta asteroide

	int g = mngr_->getComponent<Generations>(a)->gen_;

	if (g != 1) {
		Transform* tr_ = mngr_->getComponent<Transform>(a);
		if (g == 2)createAsteroids(2, 1, tr_->pos_); //Genera los dos nuevos asteroirdes de generación 1
		else createAsteroids(2, 2, tr_->pos_); //Genera los dos nuevos asteroides de generación 2
	}

	// Desactiva la entidad tras generar los nuevos
	mngr_->setAlive(a, false);

	//Comprobar aqui que queden asteroides
	if (numOfAsteroids_ == 0) {
		Message m;
		m.id = _MSG_NO_ASTEROIDS;
		mngr_->send(m);
	}
}

void AsteroidsSystem::onRoundOver() {
	destroyAllAsteroids();
	active_ = false;
}

void AsteroidsSystem::onRoundStart() {
	active_ = true;
	createAsteroids(10, 3);
}


void AsteroidsSystem::createAsteroids(int n, int g, Vector2D pos) {
	int i = 0;
	while (numOfAsteroids_ < maxAsteroids_ && i < n) {// los asteroides no superan el máximo
		Vector2D pos_;
		if (pos == Vector2D(-1, -1))pos_ = generateAstPos();// posición aleatoria de aparición
		else pos_ = pos;// posición no aleatoria


		// vector central pero con un random entre -100 y 100 para que los asteroides vayan a la zona central en un rango
		Vector2D c = sCenter_ + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));

		float speed_ = sdlutils().rand().nextInt(1, 10) / 10.0f;// factor velocidad
		Vector2D vel_ = (c - pos_).normalize() * speed_;// vector velocidad

		float size_ = 25.0f + 8.0f * g;// tamaño

		ecs::Entity* ast_ = mngr_->addEntity(_grp_ASTEROIDS);// crea el asteroide

		mngr_->addComponent<Transform>(ast_, pos_, vel_, size_, size_);// añade componente transform

		Texture* t_;// textura

		if (numOfAsteroids_ < maxAsteroids_) {
			if (sdlutils().rand().nextInt(0, 10) < 3) //tipo b
			{
				t_ = &(SDLUtils::instance()->images().at("goldAsteroid"));
				mngr_->addComponent<Follow>(ast_);// componente follow
			}
			else t_ = &(SDLUtils::instance()->images().at("asteroid")); //tipo A
		}



		mngr_->addComponent<Image>(ast_, t_, astWidth_, astHeight_, nF_, nC_, size_);// componente de renderizado
		mngr_->addComponent<ShowAtOppositeSide>(ast_);// componente toroidal
		mngr_->addComponent<Generations>(ast_, g);// número de generación

		numOfAsteroids_++;// aumenta el número de asteroiodes
		i++;
	}
}

void AsteroidsSystem::addAsteroidFrequently() {
	if (sdlutils().currRealTime() >= cont_) {
		int rnd = sdlutils().rand().nextInt(1, 4);// generación entre [0, 4)
		createAsteroids(1, rnd);
		cont_ = sdlutils().currRealTime() + 5000; // 5 secs
	}
}

void AsteroidsSystem::destroyAllAsteroids() {
	numOfAsteroids_ = 0;// número de asteroides a 0
	for (auto a : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {
		mngr_->setAlive(a, false);
	}
}

Vector2D AsteroidsSystem::generateAstPos() {
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

void AsteroidsSystem::followUpdate(ecs::Entity* a)
{
	if (mngr_->hasComponent<Follow>(a)) {
		Transform* playerTr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_HDLR_PLAYER));
		Transform* tr_ = mngr_->getComponent<Transform>(a);
		Vector2D dir_ = Vector2D(playerTr_->pos_.getX() - tr_->pos_.getX(),
			playerTr_->pos_.getY() - tr_->pos_.getY());// setea la dirección

		dir_ = dir_.normalize();// normaliza la dirección
		tr_->speed_ = dir_;// setea la dirección 
	}
}

void AsteroidsSystem::showAtOppositeSideUpdate(ecs::Entity* a)
{
	Transform* tr_ = mngr_->getComponent<Transform>(a);
	ShowAtOppositeSide* op_ = mngr_->getComponent<ShowAtOppositeSide>(a);

	float wWidth_ = sdlutils().width();// ancho de ventana
	float wHeight_ = sdlutils().height();// alto de ventana
	
	// X
	if (tr_->pos_.getX() > wWidth_ + op_->margin_) tr_->pos_ = Vector2D((0 - op_->margin_), tr_->pos_.getY());
	else if (tr_->pos_.getX() < 0 - op_->margin_) tr_->pos_ = Vector2D((wWidth_ + op_->margin_), tr_->pos_.getY());
	
	// Y
	if (tr_->pos_.getY() > wHeight_ + op_->margin_) tr_->pos_ = Vector2D(tr_->pos_.getX(), (0 - op_->margin_));
	else if (tr_->pos_.getY() < 0 - op_->margin_) tr_->pos_ = Vector2D(tr_->pos_.getX(), (wHeight_ + op_->margin_));
}