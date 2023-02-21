#include "FighterCtrl.h"


FighterCtrl::FighterCtrl() : Component() {
	velocity = 0;
	maxVelocity = 0;
	rotation = 0;
}

FighterCtrl::FighterCtrl(float Velocity, float MaxVelocity, float Rotation) :Component() {
	velocity = Velocity;
	maxVelocity = MaxVelocity;
	rotation = Rotation;
}

void FighterCtrl::initComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM);
}

void FighterCtrl::update() {
	
}	

void FighterCtrl::handleEvents(SDL_Event event)
{

	InputHandler::instance()->update(event);

	if (InputHandler::instance()->keyDownEvent())
	{

		//Rotación
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
			tr->setR(-5.0f);
		}
		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
			tr->setR(5.0f);
		}
		//Movimiento
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP)) {
			tr->setVel(tr->getVel() + (tr->getDir() * 0.1f));

		}
		/*if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_A)) {
			cout << "SOFIA CUANTO POR MEARME EN LA CARA?";
		}*/



	}
}