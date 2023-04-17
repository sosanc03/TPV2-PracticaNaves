#include "RenderSystem.h"

void RenderSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _MSG_NO_ASTEROIDS: // ganar
		onGameOver();
		break;
	case _MSG_START: // iniciar partida
		onGameStart();
		break;
	case _MSG_GAMEOVER: // volver de ronda perdida
		onRoundStart();
		break;
	case _MSG_COL_AST_PLAYER: // perder ronda
		onRoundOver();
		break;
	case _MSG_RESUME: // resume
		state_ = 1;
		break;
	case _MSG_PAUSE: // pausa
		state_ = 0;
		break;
	default:
		break;
	}
}

void RenderSystem::initSystem() {
	fSys_ = mngr_->getSystem<FighterSystem>(_SYS_FIGHTER);
}

void RenderSystem::update() {
	if (state_ == 1) {// running
		renderFighter();
		renderHealth();
		renderAsteroids();
		renderBullet();
	}
	else renderText();
}

void RenderSystem::renderText()
{
	auto& t = sdlutils().msgs().at("space"); // espacio para continuar
	t.render((sdlutils().width() - t.width()) / 2,
		sdlutils().height() / 2 + t.height() * 2);

	if (winner_ == 1) { // texto al perder
		auto& t = sdlutils().msgs().at("defeat");
		t.render((sdlutils().width() - t.width()) / 2,
			sdlutils().height() / 4 + t.height() * 2);
	}
	else if (winner_ == 2) { // texto al ganar
		auto& t = sdlutils().msgs().at("win");
		t.render((sdlutils().width() - t.width()) / 2,
			sdlutils().height() / 4 + t.height() * 2);
	}
}

void RenderSystem::renderFighter()
{
	fSys_->fighter_->getComponent<Image>(IMAGE_H)->render();
}

void RenderSystem::renderHealth()
{
	Transform* tr_ = fSys_->fighter_->getComponent<Transform>(TRANSFORM_H);
	Health* health_ = fSys_->fighter_->getComponent<Health>(HEALTH_H);

	//Dibuja las vidas
	auto t_ = &(SDLUtils::instance()->images().at("heart"));// textura
	int tSize_ = 50;// tamaño
	Vector2D renderPos = Vector2D(0, 0);// posición de renderizado

	for (int i = 0; i < health_->lifes; ++i) {// dibuja tantos corazones como vidas 
		SDL_Rect dest = { renderPos.getX(), renderPos.getY(), tSize_, tSize_ };
		t_->render(dest);
		renderPos.setX(renderPos.getX() + tSize_);
	}
	renderPos = Vector2D(0, 0);
}

void RenderSystem::renderAsteroids()
{
	for (auto as : mngr_->getEntitiesByGroup(ecs::_grp_ASTEROIDS)) as->getComponent<Image>(IMAGE_H)->render();
}

void RenderSystem::renderBullet()
{
	for(auto b : mngr_->getEntitiesByGroup(ecs::_grp_BULLETS)) b->getComponent<Image>(IMAGE_H)->render();
}

void RenderSystem::onRoundStart(){
	winner_ = 0; // nada
	state_ = 1; // run
}
void RenderSystem::onRoundOver(){
	winner_ = 1; // derrota
	state_ = 0; // pausa
}
void RenderSystem::onGameStart(){
	winner_ = 0; // nada
	state_ = 1; // run
}
void RenderSystem::onGameOver(){
	winner_ = mngr_->getSystem<GameCtrlSystem>(_SYS_GAMECTRL)->winner_; // victoria o derrota
	state_ = 0; // pausa
}
