// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include <SDL_rect.h>
#include "../components/Image.h"
#include "../components/RectangleViewer.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/FramedImage.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"

RenderSystem::RenderSystem() {
}

RenderSystem::~RenderSystem() {
}
void RenderSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_NO_ASTEROIDS:
		win = true;
		break;
	case _m_GAME_START:
		win = false;
		break;
	default:
		break;
	}
}
void RenderSystem::initSystem() {
	initime = sdlutils().currRealTime();
}

void RenderSystem::update() {
	drawMsgs();
	auto state = mngr_->getSystem<GameCtrlSystem>()->getState();
	// message when game is not running
	if (state == GameCtrlSystem::RUNNING) {
		drawFighter();
		drawHealth();
		drawAsteroids();
		drawBullet();
	}
}

void RenderSystem::drawFighter()
{

	auto plyr = mngr_->getHandler(ecs::_hdlr_PLAYER);

	auto tr_ = mngr_->getComponent<Transform>(plyr);
	SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_, tr_->height_);

	auto img = mngr_->getComponent<Image>(plyr)->tex_;
	assert(img != nullptr);
	img->render(dest, tr_->rot_);
}

void RenderSystem::drawHealth()
{
	auto plyr = mngr_->getHandler(ecs::_hdlr_PLAYER);
	auto health_ = mngr_->getComponent<Health>(plyr);
	//Dibuja las vidas del jugador
	auto s = &sdlutils().images().at("heart");
	SDL_Rect dest = build_sdlrect( //
		10.0f, //
		10.0f, //
		40, //
		40);
	for (int i = 0; i < health_->h_; i++) {
		s->render(dest);
		dest.x += dest.w + 10;
	}
}

void RenderSystem::drawAsteroids()
{
	for (auto a : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {
		auto tr_ = mngr_->getComponent<Transform>(a);
		mngr_->getComponent<FramedImage>(a)->render(tr_);
	}
}

void RenderSystem::drawBullet()
{
	for (auto a : mngr_->getEntities(ecs::_grp_BULLETS)) {
		if (mngr_->isAlive(a)) {
			auto tr_ = mngr_->getComponent<Transform>(a);
			auto img = mngr_->getComponent<Image>(a);
			SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_,
				tr_->height_);
			assert(img->tex_ != nullptr);

			img->tex_->render(dest, tr_->rot_);
		}
	}
}

void RenderSystem::drawMsgs() {
	auto state = mngr_->getSystem<GameCtrlSystem>()->getState();

	// message when game is not running
	if (state != GameCtrlSystem::RUNNING) {

		// game over message
		if (state == GameCtrlSystem::PAUSED) {
			auto health = mngr_->getComponent<Health>(mngr_->getHandler(ecs::_hdlr_PLAYER))->h_;
			if (health == 0) {
				auto& t = sdlutils().msgs().at("gameover");
				t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
			}
			else if(!win){
				auto& t = sdlutils().msgs().at("continue");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
			}
			else {
				auto& t = sdlutils().msgs().at("win");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
			}
		}
		else if (state == GameCtrlSystem::PAUSED) {
		}
		// new game message
		else if (state == GameCtrlSystem::NEWGAME) {
			auto& t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
				sdlutils().height() / 2 + t.height() * 2);
		}

	}
}

