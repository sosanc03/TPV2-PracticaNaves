#include "AsteroidsSystem.h"
#include "FighterSystem.h"

void AsteroidsSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _MSG_COL_AST_PLAYER: // perder ronda
		onRoundOver();
		break;
	case _MSG_COL_AST_BULLET: // romper un asteroide
		onCollision_AsteroidBullet(m.hitBulAst.asteroid_);
		break;
	case _MSG_START: // inicio partida
		initSystem();
		break;
	case _MSG_GAMEOVER: // volver de ronda perdida
		onRoundStart();
		break;
	case _MSG_RESUME: // resume
		active_ = true;
		break;
	case _MSG_PAUSE:
		active_ = false;
		break;
	default:
		break;
	}
}

void AsteroidsSystem::initSystem() {
	
	sCenter_ = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2); // centro pantalla
	fSys_ = mngr_->getSystem<FighterSystem>(_SYS_FIGHTER); // ref a fighter
	active_ = false;
	astWidth_ = 510;
	astHeight_ = 500;
	nF_ = 6;
	nC_ = 5;
	maxAsteroids_ = 30;
	numOfAsteroids_ = 0;
	createAsteroids(10, 3);
	cont_ = 5000;

}

void AsteroidsSystem::update() {
	if (active_) {
		addAsteroidFrequently();
		for (auto a : mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS)) {
			showAtOppositeSideUpdate(a);
			followUpdate(a);
			a->getComponent<Transform>(TRANSFORM_H)->move();
		}
	}
}

void AsteroidsSystem::onCollision_AsteroidBullet(Entity* a) {
	sdlutils().soundEffects().at("explosion").play();// sonido de explosión
	numOfAsteroids_--;// resta asteroide

	int g = a->getComponent<Generations>(GENERATIONS_H)->gen_;

	if (g != 1) {
		Transform* tr_ = a->getComponent<Transform>(TRANSFORM_H);
		if (g == 2)createAsteroids(2, 1, tr_->pos_); //Genera los dos nuevos asteroirdes de generación 1
		else createAsteroids(2, 2, tr_->pos_); //Genera los dos nuevos asteroides de generación 2
	}

	// Desactiva la entidad tras generar los nuevos
	a->setAlive(false);

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

		Entity* ast_ = mngr_->addEntity(_grp_ASTEROIDS);// crea el asteroide

		ast_->addComponent<Transform>(TRANSFORM_H, pos_, vel_, size_, size_);// añade componente transform

		Texture* t_;// textura

		if (numOfAsteroids_ < maxAsteroids_) {
			if (sdlutils().rand().nextInt(0, 10) < 3) //tipo b
			{
				t_ = &(SDLUtils::instance()->images().at("goldAsteroid"));
				ast_->addComponent<Follow>(FOLLOW_H);// componente follow
			}
			else t_ = &(SDLUtils::instance()->images().at("asteroid")); //tipo A
		}

		ast_->addComponent<Image>(IMAGE_H, t_, astWidth_, astHeight_, nF_, nC_, size_);// componente de renderizado
		ast_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
		ast_->addComponent<Generations>(GENERATIONS_H, g);// número de generación

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
	for (auto a : mngr_->getEntitiesByGroup(_grp_ASTEROIDS)) {
		a->setAlive(false);
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

void AsteroidsSystem::followUpdate(Entity* a)
{
	if (a->hasComponent(FOLLOW_H)) {
		Transform* playerTr_ = fSys_->fighter_->getComponent<Transform>(TRANSFORM_H);
		Transform* tr_ = a->getComponent<Transform>(TRANSFORM_H);
		Vector2D dir_ = Vector2D(playerTr_->pos_.getX() - tr_->pos_.getX(),
			playerTr_->pos_.getY() - tr_->pos_.getY());// setea la dirección

		dir_ = dir_.normalize();// normaliza la dirección
		tr_->speed_ = dir_;// setea la dirección 
	}
}

void AsteroidsSystem::showAtOppositeSideUpdate(Entity* a)
{
	Transform* tr_ = a->getComponent<Transform>(TRANSFORM_H);
	ShowAtOppositeSide* op_ = a->getComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);

	float wWidth_ = sdlutils().width();// ancho de ventana
	float wHeight_ = sdlutils().height();// alto de ventana
	
	// X
	if (tr_->pos_.getX() > wWidth_ + op_->margin_) tr_->pos_ = Vector2D((0 - op_->margin_), tr_->pos_.getY());
	else if (tr_->pos_.getX() < 0 - op_->margin_) tr_->pos_ = Vector2D((wWidth_ + op_->margin_), tr_->pos_.getY());
	
	// Y
	if (tr_->pos_.getY() > wHeight_ + op_->margin_) tr_->pos_ = Vector2D(tr_->pos_.getX(), (0 - op_->margin_));
	else if (tr_->pos_.getY() < 0 - op_->margin_) tr_->pos_ = Vector2D(tr_->pos_.getX(), (wHeight_ + op_->margin_));
}