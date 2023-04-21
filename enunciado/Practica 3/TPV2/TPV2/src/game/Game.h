// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/ecs.h"
class FightersSystem;
class BulletsSystem;
class GameCtrlSystem;
class CollisionsSystem;
class NetworkSystem;
class RenderSystem;
class Game {
public:
	Game();
	virtual ~Game();
	bool init();
	void start();
private:
	ecs::Manager* mngr_;
	FightersSystem* fightersSys_;
	BulletsSystem* bulletsSys_;
	GameCtrlSystem* gameCtrlSys_;
	CollisionsSystem* collisionSys_;
	RenderSystem* renderSys_;
	NetworkSystem* netSys_;
};

