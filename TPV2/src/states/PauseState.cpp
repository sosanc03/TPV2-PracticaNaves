#include "PauseState.h"
#include "../game/Game.h"

PauseState::PauseState()// constructora
{
	auto& sdl = *SDLUtils::instance();// SDLUtils
	auto& space = sdl.msgs().at("space");// textura del texto
	text_ = Manager::instance()->addEntity();

	float w_ = 400;// anchura
	float h_ = 50;// altura
	Vector2D pos_ = Vector2D(sdl.width() / 2 - w_ / 2, sdl.height() / 2 - h_ / 2);// posición central
	Vector2D vel_ = Vector2D(0, 0);// velocidad inicial a 0
	text_->addComponent<Transform>(TRANSFORM_H, pos_, vel_, w_, h_);// transform
	t_ = &space;
	text_->addComponent<Image>(IMAGE_H, t_);// componente image
}

PauseState::~PauseState() {
	text_->setAlive(false);// desactiva el texto
}

void PauseState::update() {
	InputHandler::instance()->refresh();// actualiza el input
	if (InputHandler::instance()->keyDownEvent()) {
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
 			GameStateMachine::instance()->popState();// vuelve al juego
		}
	}
}