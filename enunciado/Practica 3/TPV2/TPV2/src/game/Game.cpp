// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/BulletsSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/FightersSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/NetworkSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using ecs::Entity;
using ecs::Manager;

Game::Game() :
	mngr_(nullptr), //
	fightersSys_(nullptr), //
	bulletsSys_(nullptr), //
	gameCtrlSys_(nullptr), //
	collisionSys_(nullptr), //
	renderSys_(nullptr) {

}

Game::~Game() {
	delete mngr_;
}

bool Game::init() {

	// Create the manager
	mngr_ = new Manager();
	netSys_ = mngr_->addSystem<NetworkSystem>();
	netSys_->putName();
	if (!netSys_->connect()) {
		return false;
	}
	// initialise the SDLUtils singleton
	SDLUtils::init("Fighters", 800, 600,
		"resources/config/fighters.resources.json");

	
	// add the systems
	gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
	fightersSys_ = mngr_->addSystem<FightersSystem>();
	bulletsSys_ = mngr_->addSystem<BulletsSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
	collisionSys_ = mngr_->addSystem<CollisionsSystem>();
	return true;
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto& ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			netSys_->disconnect();
			exit = true;
			continue;
		}

		fightersSys_->update();
		bulletsSys_->update();
		gameCtrlSys_->update();
		collisionSys_->update();
		netSys_->update();


		sdlutils().clearRenderer();
		renderSys_->update();
		sdlutils().presentRenderer();

		// remove dead entities
		mngr_->refresh();

		// send pending messages
		mngr_->flushMessagesWithSwap();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

