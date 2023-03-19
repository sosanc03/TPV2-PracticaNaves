// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/AsteroidsSystem.h"
#include "../systems/BulletsSystem.h"
#include "../systems/FighterGunSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using ecs::Manager;

Game::Game() :
	mngr_(nullptr), //
	gameCtrlSys_(nullptr), //
	collisionsSys_(nullptr), //
	renderSys_(nullptr),
	fightSys_(nullptr),
	AstSys_(nullptr),
	GunSys_(nullptr),
	BullSys_(nullptr){
}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// Initialize the SDLUtils singleton
	SDLUtils::init("Ping Pong", 800, 600,
		"resources/config/asteroid.resources.json");

	sdlutils().hideCursor();

	// Create the manager
	mngr_ = new Manager();

	//We add the systems that we are going to use
	gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
	collisionsSys_ = mngr_->addSystem<CollisionsSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
	fightSys_ = mngr_->addSystem<FighterSystem>();
	AstSys_ = mngr_->addSystem<AsteroidsSystem>();
	GunSys_ = mngr_->addSystem<FighterGunSystem>();
	BullSys_ = mngr_->addSystem<BulletsSystem>();
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
			exit = true;
			continue;
		}

		mngr_->refresh();


		gameCtrlSys_->update();
		collisionsSys_->update();
		fightSys_->update();
		AstSys_->update();
		BullSys_->update();
		GunSys_->update();
		fightSys_->update();
		sdlutils().clearRenderer();
		renderSys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}
