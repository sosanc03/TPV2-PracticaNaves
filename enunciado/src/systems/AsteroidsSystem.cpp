#include "AsteroidsSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void AsteroidsSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_COL_AST_PLAYER:
		deleteAllAsteroids();
		break;
	case _m_COL_BULLET_AST:
		onCollision_AsteroidBullet(m.bullet_hit_asteroid.ast);
		break;
	case _m_GAME_START:
		onGameStart();
		break;
	case _m_GAME_RESUME:
		onRoundStart();
	default:
		break;
	}
}

void AsteroidsSystem::initSystem()
{
	if (active_) {
		createAsteroids(10);
		asteroidTime = sdlutils().currRealTime() / 1000;
	}
}

AsteroidsSystem::AsteroidsSystem() : active_(false)
{
}

AsteroidsSystem::~AsteroidsSystem()
{
}

void AsteroidsSystem::update()
{
	if (active_) {
		//AddAsteroidFrecuently();
		for (auto a : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {
			showAtOppositeSideUpdate(a);
			followUpdate(a);
			auto* tr_ = mngr_->getComponent<Transform>(a);
			tr_->move();
		}
	}
}

void AsteroidsSystem::onCollision_AsteroidBullet(ecs::Entity* a)
{
	mngr_->getComponent<Generations>(a)->g_--;

	auto tr = mngr_->getComponent<Transform>(a);
	if (mngr_->getComponent<Generations>(a)->g_ > 0 && numAsteroids + 2 <= 30) {

		for (auto i = 0u; i < 2; i++) {
			auto r = sdlutils().rand().nextInt(0, 360);
			auto pos = tr->pos_ + tr->vel_.rotate(r) * 2 * std::max(tr->width_, tr->height_);
			auto vel_ = tr->vel_.rotate(r) * 1.1f;
			// Always use the random number generator provided by SDLUtils
			//
			auto& rand = sdlutils().rand();

			// add and entity to the manager
			//
			auto newAst = mngr_->addEntity(ecs::_grp_ASTEROIDS);
			auto gen = mngr_->addComponent<Generations>(newAst);
			gen->g_ = mngr_->getComponent<Generations>(a)->g_;

			auto tr = mngr_->addComponent<Transform>(newAst);
			auto s = 10.0f + 5.0f * mngr_->getComponent<Generations>(a)->g_;


			auto rx = rand.nextInt(-100, 100);
			auto ry = rand.nextInt(-100, 100);
			//Centro de la ppantalla
			Vector2D c = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2) + Vector2D(rx, ry);
			//Posicion inicial

			tr->init(pos, vel_, s, s, 0.0f);
			//se elige aleatoriamente el tipo de asteroide
			auto tipo = sdlutils().rand().nextInt(0, 100) < 30;

			if (tipo)mngr_->addComponent<Follow>(newAst);
			mngr_->addComponent<FramedImage>(newAst, &sdlutils().images().at(tipo ? "asteroid_b" : "asteroid_a"), 5, 6, 20, 300);

			numAsteroids++;
		}
	}
	numAsteroids--;
	mngr_->setAlive(a, false);

	//Comprobar aqui que queden asteroides
	if (numAsteroids <= 0) {
		Message m;
		m.id = _m_NO_ASTEROIDS;
		mngr_->send(m);
	}
}

void AsteroidsSystem::onRoundOver()
{
	deleteAllAsteroids();
	active_ = false;
}

void AsteroidsSystem::onGameStart()
{
	active_ = true;
	initSystem();
}

void AsteroidsSystem::onRoundStart()
{
	active_ = true;
	createAsteroids(10);
}

void AsteroidsSystem::createAsteroids(int n)
{
	if (numAsteroids + n <= 30) {
		//Asteroides de tipo A y b aleatoriamente
		for (auto i = 0u; i < n; i++) {

			auto& rand = sdlutils().rand();

			auto a = mngr_->addEntity(ecs::_grp_ASTEROIDS);
			auto gen = mngr_->addComponent<Generations>(a);

			gen->g_ = rand.nextInt(1, 4);
			auto s = 10.0f + 5.0f * gen->g_;

			auto r = rand.nextInt(0, 4);
			auto x = 0;
			auto y = 0;
			//depende de que valor salga, se representa el asteroide en un lateral de la ventana en una pos aleatoria
			switch (r)
			{
			case 0:
				x = rand.nextInt(0, sdlutils().width() - s);
				y = sdlutils().height() - s;
				break;
			case 1:
				x = rand.nextInt(0, sdlutils().width() - s);
				y = s;
				break;
			case 2:
				x = s;
				y = rand.nextInt(0, sdlutils().height() - s);
				break;
			case 3:
				x = sdlutils().width() - s;
				y = rand.nextInt(0, sdlutils().height() - s);
				break;
			default:
				break;
			}
			float speed = rand.nextInt(1, 10) / 10.0f;
			auto rx = rand.nextInt(-100, 100);
			auto ry = rand.nextInt(-100, 100);
			//Centro de la ppantalla
			Vector2D c = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2) + Vector2D(rx, ry);
			//Posicion inicial
			Vector2D p = Vector2D(x, y);
			Vector2D v = (c - p).normalize() * speed;
			auto tr = mngr_->addComponent<Transform>(a);
			tr->init(p, v, s, s, 0.0f);
			//se elige aleatoriamente el tipo de asteroide
			auto tipo = sdlutils().rand().nextInt(0, 100) < 30;

			mngr_->addComponent<FramedImage>(a, &sdlutils().images().at(tipo ? "asteroid_b" : "asteroid_a"), 5, 6, 20, 30);
			//si el asteroide es B le añade el componente de seguir al jugador
			if (tipo) mngr_->addComponent<Follow>(a);
		}
		numAsteroids += n;
	}
}

void AsteroidsSystem::AddAsteroidFrecuently()
{
	float time = sdlutils().currRealTime() / 1000;

	if (time - asteroidTime >= 5) {
		createAsteroids(1);
		asteroidTime = sdlutils().currRealTime() / 1000;
	}
}

void AsteroidsSystem::followUpdate(ecs::Entity* a)
{
	if (mngr_->hasComponent<Follow>(a)) {
		auto* tr_ = mngr_->getComponent<Transform>(a);
		auto& vel = tr_->vel_;
		auto& pos = tr_->pos_;
		auto q = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_PLAYER))->pos_;
		vel = vel.rotate(vel.angle(q - pos) > 0 ? 1.0f : -1.0f);
	}
}

void AsteroidsSystem::showAtOppositeSideUpdate(ecs::Entity* a)
{
	auto* tr_ = mngr_->getComponent<Transform>(a);

	// check left/right borders
	if (tr_->pos_.getX() + tr_->width_ < 0) {
		tr_->pos_.setX(sdlutils().width());
	}
	else if (tr_->pos_.getX() > sdlutils().width()) {
		tr_->pos_.setX(-tr_->width_);
	}

	// check upper/lower borders
	if (tr_->pos_.getY() + tr_->height_ < 0) {
		tr_->pos_.setY(sdlutils().height());
	}
	else if (tr_->pos_.getY() > sdlutils().height()) {
		tr_->pos_.setY(-tr_->height_);
	}
}

void AsteroidsSystem::deleteAllAsteroids()
{
	for (auto a : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {
		mngr_->setAlive(a, false);
	}
	numAsteroids = 0;
}
