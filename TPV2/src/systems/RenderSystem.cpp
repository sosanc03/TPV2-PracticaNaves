#include "RenderSystem.h"

void RenderSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _MSG_NO_ASTEROIDS:
		winner_ = 2;
		break;
	case _MSG_START:
		winner_ = 0;
		break;
	default:
		break;
	}
}

void RenderSystem::initSystem() {

}

void RenderSystem::update() {
	state_ = mngr_->getSystem<GameCtrlSystem>()->state_;

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
	auto& t = sdlutils().msgs().at("space");
	t.render((sdlutils().width() - t.width()) / 2,
		sdlutils().height() / 2 + t.height() * 2);
}

void RenderSystem::renderFighter()
{
	mngr_->getComponent<Image>(mngr_->getHandler(ecs::_HDLR_PLAYER))->render();
}

void RenderSystem::renderHealth()
{
	Transform* tr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_HDLR_PLAYER));
	Health* health_ = mngr_->getComponent<Health>(mngr_->getHandler(ecs::_HDLR_PLAYER));

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
	for (auto as : mngr_->getEntities(ecs::_grp_ASTEROIDS)) mngr_->getComponent<Image>(as)->render();

}

void RenderSystem::renderBullet()
{
	for(auto b : mngr_->getEntities(ecs::_grp_BULLETS))mngr_->getComponent<Image>(b)->render();
}

void RenderSystem::onRoundStart(){}
void RenderSystem::onRoundOver(){}
void RenderSystem::onGameStart(){}
void RenderSystem::onGameOver(){}
