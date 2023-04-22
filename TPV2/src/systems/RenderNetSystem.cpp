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

RenderNetSystem::RenderNetSystem()  {
	active_ = false;
	gameOver_ = false;
}

RenderNetSystem::~RenderNetSystem() {
}

void RenderNetSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_START:
		GameStart(m);
		break;
	case _MSG_GAMEOVER:
		GameOver(m);
		break;
	default:
		break;
	}
}

void RenderNetSystem::GameStart(const Message&) {
	active_ = true;
	gameOver_ = false;
}

void RenderNetSystem::GameOver(const Message& m) {
	active_ = false;
	gameOver_ = true;
	killedId_ = m.killed.playerId;
}

void RenderNetSystem::update() {

	if (mngr_->getSystem<NetworkSystem>(_SYS_NETWORK)->isReady()) {
		renderText(); // dibuja textos
		renderFighters();// dibuja players
		renderBullets();// dibuja balas
	}
	else renderWaitingText();// texto de espera mientras no se haya conectado el segundo player

}

void RenderNetSystem::renderText() {// dibuja los textos del juego
	if (!active_) {

		auto& t = sdlutils().msgs().at("space"); // espacio para continuar
		t.render((sdlutils().width() - t.width()) / 2,
			sdlutils().height() / 2 + t.height() * 2);

		if (gameOver_) {// game Over
			NetworkSystem* netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);
			auto& gameOver = sdlutils().msgs().at("gameOver");
			gameOver.render((sdlutils().width() - gameOver.width()) / 2, 20);// texto de GameOver

			
			Texture t(sdlutils().renderer(), 
				netSys->getName(killedId_) + " has been shot!", 
				sdlutils().fonts().at("ARIAL24"), 
				build_sdlcolor(0xff0000ff));
			t.render((sdlutils().width() - t.width()) / 2,
				gameOver.height() + 50);// texto de jugador que ha sido disparado
		}
	}
}

void RenderNetSystem::renderFighters() {// dibuja los players
	for (auto& e : mngr_->getEntitiesByGroup(_grp_FIGHTERS)) {
		renderFighter(e);
	}
}

void RenderNetSystem::renderFighter(Entity* e)
{
	renderEntity(e);// dibuja el player
	renderName(e);// dibuja el nombre
}

void RenderNetSystem::renderBullets() {// dibuja las balas
	for (Entity* e : mngr_->getEntitiesByGroup(ecs::_grp_BULLETS)) {
		renderEntity(e);
	}
}

void RenderNetSystem::renderEntity(Entity* e) {// dibuja entidades
	Image* img = e->getComponent<Image>(IMAGE_H);
	img->render();
}

void RenderNetSystem::renderName(Entity* e) {// dibuja el nombre de los players

	int id = e->getComponent<FighterInfo>(FIGHTERINFO_H)->id_;// guarda el id del fighter
	Transform* tr = e->getComponent<Transform>(TRANSFORM_H);
	NetworkSystem* netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);

	string name = netSys->getName(id);// nombre

	Texture playeName(sdlutils().renderer(), 
		name, sdlutils().fonts().at("ARIAL16"),
		build_sdlcolor(0xffffffff));// textura

	Vector2D pos =
		Vector2D(0.0f, (tr->h_ / 2.0f) + playeName.height() / 2.0f)
		.rotate(tr->rot_) + tr->pos_
		+ Vector2D(tr->w_ / 2.0f, tr->h_ / 2.0f);

	SDL_Rect dest = build_sdlrect(pos.getX() - playeName.width() / 2.0f,
		pos.getY() - playeName.height() / 2.0, playeName.width(),
		playeName.height());

	playeName.render(dest, tr->rot_);// dibuja nombre
}

void RenderNetSystem::renderWaitingText()// texto de espera
{
	int port = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK)->getPort();

	Texture waiting(
		sdlutils().renderer(), 
		"Waiting for the other player to connect ...",
		sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xccddaaaff));
	waiting.render((sdlutils().width() - waiting.width()) / 2, 10); // texto de espera

	Texture portmsg(
		sdlutils().renderer(), 
		"Your are connected at port " + std::to_string(port),
		sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0x1155aaff));
	portmsg.render((sdlutils().width() - portmsg.width()) / 2,
		waiting.height() + 30);// texto de puerto actual
}
