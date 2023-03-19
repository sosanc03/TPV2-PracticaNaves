// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

namespace ecs {
	class Manager;
}


class GameCtrlSystem;
class CollisionsSystem;
class RenderSystem;
class FighterSystem;
class AsteroidsSystem;
class FighterGunSystem;
class BulletsSystem;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	ecs::Manager* mngr_;


	GameCtrlSystem* gameCtrlSys_;
	CollisionsSystem* collisionsSys_;
	RenderSystem* renderSys_;
	FighterSystem* fightSys_;
	AsteroidsSystem* AstSys_;
	FighterGunSystem* GunSys_;
	BulletsSystem* BullSys_;
};

