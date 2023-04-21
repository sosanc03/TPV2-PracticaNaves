#include "RenderNetSystem.h"
#include <SDL_render.h>

#include "../components/FighterInfo.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "GameCtrlSystem.h"
#include "NetworkSystem.h"

RenderNetSystem::RenderNetSystem() :
	running_(false), over_(false), killedId_() {
}

RenderNetSystem::~RenderNetSystem() {
}

void RenderNetSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_START:
		handleGameStart(m);
		break;
	case _MSG_GAMEOVER:
		handleGameOver(m);
		break;
	default:
		break;
	}
}

void RenderNetSystem::handleGameStart(const Message&) {
	running_ = true;
	over_ = false;
}

void RenderNetSystem::handleGameOver(const Message& m) {
	running_ = false;
	over_ = true;
	killedId_ = m.killed.playerId;
}

void RenderNetSystem::initSystem() {
}

void RenderNetSystem::update() {


	if (mngr_->getSystem<NetworkSystem>(_SYS_NETWORK)->isReday()) {
		drawMsgs();
		drawFighters();
		drawBullets();
	}
	else {
		drawWaitingMsg();
	}
}




void RenderNetSystem::drawMsgs() {
	if (!running_) {

		auto& startMsg = sdlutils().msgs().at("start");
		startMsg.render((sdlutils().width() - startMsg.width()) / 2,
			sdlutils().height() / 2 + startMsg.height() * 2);

		if (over_) {
			auto netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);
			auto& gameOverMsg = sdlutils().msgs().at("gameover");
			gameOverMsg.render((sdlutils().width() - gameOverMsg.width()) / 2,
				20);

			Texture winnerMsg(sdlutils().renderer(), //
				netSys->getName(killedId_) + " has been shot!", //
				sdlutils().fonts().at("ARIAL24"), //
				build_sdlcolor(0xffAA44ff));

			winnerMsg.render((sdlutils().width() - winnerMsg.width()) / 2,
				gameOverMsg.height() + 50);
		}

	}

}

void RenderNetSystem::drawFighters() {
	auto netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);
	auto side = netSys->getSide();
	for (auto& g : mngr_->getEntitiesByGroup(_grp_FIGHTERS)) {
		if (g == mngr_->getEntitiesByGroup(_grp_FIGHTERS).at(side))
			drawBox(g);
		drawFigh(g);
	}
}

void RenderNetSystem::drawFigh(Entity* e)
{
	draw(e);
	drawId(e);
}

void RenderNetSystem::drawBullets() {
	for (Entity* e : mngr_->getEntitiesByGroup(ecs::_grp_BULLETS)) {
		draw(e);
	}
}

void RenderNetSystem::draw(Entity* e) {
	auto tr = e->getComponent<Transform>(TRANSFORM_H);
	auto img = e->getComponent<Image>(TRANSFORM_H);

	SDL_Rect dest = build_sdlrect(tr->pos_, tr->w_, tr->h_);
	img->render();
}

void RenderNetSystem::drawId(Entity* e) {
	auto id = e->getComponent<FighterInfo>(FIGHTERINFO_H)->id_;
	auto tr = e->getComponent<Transform>(TRANSFORM_H);
	auto netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);

	std::string tag = netSys->getName(id);

	Texture playeTag(sdlutils().renderer(), //
		tag, //
		sdlutils().fonts().at("ARIAL12"), //
		build_sdlcolor(0xff0000ff));

	Vector2D p =
		Vector2D(0.0f, (tr->h_ / 2.0f) + playeTag.height() / 2.0f).rotate(
			tr->rot_) + tr->pos_
		+ Vector2D(tr->w_ / 2.0f, tr->h_ / 2.0f);

	SDL_Rect dest = build_sdlrect(p.getX() - playeTag.width() / 2.0f,
		p.getY() - playeTag.height() / 2.0, playeTag.width(),
		playeTag.height());

	playeTag.render(dest, tr->rot_);

	//	SDL_RenderDrawLine(sdlutils().renderer(), , lb.getY() + y, lu.getX() + x,
	//			lu.getY() + y);

}

void RenderNetSystem::drawBox(Entity* e) {
	SDL_Renderer* renderer = sdlutils().renderer();
	auto tr = e->getComponent<Transform>(TRANSFORM_H);

	// the rotation angle of the entity
	float angle = tr->rot_;

	// Assuming the (0,0) point is the middle of the entity, the following are
	// vectors to the corners of its bounding rectangle
	Vector2D lu = Vector2D(-tr->w_ / 2.0f, -tr->h_ / 2.0f);
	Vector2D ru = Vector2D(tr->w_ / 2.0f, -tr->h_ / 2.0f);
	Vector2D rb = Vector2D(tr->w_ / 2.0f, tr->h_ / 2.0f);
	Vector2D lb = Vector2D(-tr->w_ / 2.0f, tr->h_ / 2.0f);

	// rotate the corners, so we get a rotated rectangle
	lu = lu.rotate(angle);
	ru = ru.rotate(angle);
	rb = rb.rotate(angle);
	lb = lb.rotate(angle);

	// the center of the entity
	float x = tr->pos_.getX() + tr->w_ / 2.0f;
	float y = tr->pos_.getY() + tr->h_ / 2.0f;

	// draw lines between the corners, after shifting them by (x,y)
	SDL_SetRenderDrawColor(renderer, COLOREXP(build_sdlcolor(0x0000ff00)));
	SDL_RenderDrawLine(renderer, lu.getX() + x, lu.getY() + y, ru.getX() + x,
		ru.getY() + y);
	SDL_RenderDrawLine(renderer, ru.getX() + x, ru.getY() + y, rb.getX() + x,
		rb.getY() + y);
	SDL_RenderDrawLine(renderer, rb.getX() + x, rb.getY() + y, lb.getX() + x,
		lb.getY() + y);
	SDL_RenderDrawLine(renderer, lb.getX() + x, lb.getY() + y, lu.getX() + x,
		lu.getY() + y);

	/*
	 // draw center point
	 SDL_SetRenderDrawColor(renderer, COLOREXP(build_sdlcolor(0xff000000)));
	 SDL_Rect dest = build_sdlrect(x - 1, y - 1, 3, 3);
	 SDL_RenderFillRect(renderer, &dest);

	 // draw velocity vector
	 SDL_SetRenderDrawColor(renderer, COLOREXP(build_sdlcolor(0x00ff0011)));

	 auto vel = tr->vel_;
	 float wh = std::min(tr->height_, tr->width_) / 2.0f; // minimum of width an height
	 vel = vel * wh / 2.0f;
	 SDL_RenderDrawLine(renderer, x, y, vel.getX() + x, vel.getY() + y);
	 */
}

void RenderNetSystem::drawWaitingMsg()
{
	auto port = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK)->getPort();

	Texture waiting(
		sdlutils().renderer(), //
		"Waiting for the other player to connect ...",
		sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xccddaaaff));
	waiting.render((sdlutils().width() - waiting.width()) / 2, 10);

	Texture portmsg(
		sdlutils().renderer(), //
		"Your are connected at port " + std::to_string(port),
		sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0x1155aaff));
	portmsg.render((sdlutils().width() - portmsg.width()) / 2,
		waiting.height() + 30);
}
