#include "PauseState.h"
#include "../game/Game.h"

PauseState::PauseState()
{
	auto& sdl = *SDLUtils::instance();
	auto& space = sdl.msgs().at("space");
	text_ = Manager::instance()->addEntity();

	float w_ = 400;
	float h_ = 50;
	Vector2D pos_ = Vector2D(sdl.width() / 2 - w_/2, sdl.height() / 2 - h_/2);
	Vector2D vel_ = Vector2D(0, 0);
	text_->addComponent<Transform>(TRANSFORM_H, pos_, vel_, w_, h_);
	t_ = &space;
	text_->addComponent<Image>(IMAGE_H, t_);
}

PauseState::~PauseState() {
	text_->setAlive(false);
	//delete(text_);
	//delete(t_);
}

void PauseState::update() {
	InputHandler::instance()->refresh();
	if (InputHandler::instance()->keyDownEvent()) {
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
 			GameStateMachine::instance()->popState();
		}
	}
}