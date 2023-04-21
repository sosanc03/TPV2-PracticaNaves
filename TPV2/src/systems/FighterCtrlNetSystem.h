#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/Health.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "../sdlutils/InputHandler.h"
#include "../components/ShowAtOpposideSide.h"
#include "NetworkSystem.h"
#include "../components/FighterInfo.h"

class FighterCtrlNetSystem :
    public System
{
public:

	Entity* fighter0_;
	Entity* fighter1_;

	FighterCtrlNetSystem();
	virtual ~FighterCtrlNetSystem() {};

	void receive(const Message&) override;
	void initSystem() override;
	void update() override;
	void changeFighterPos(Uint16 side, float x, float y, float rot);
private:
	void createShip0();
	void createShip1();
	void handleGameStart(const Message&);
	void handleGameOver(const Message&);
	void handleBulletHitFighter(const Message&);
	void showAtOppositeSide(Transform* tr);
	void reduceVelocity(Transform* tr);
	void moveFighter(Entity* fighter);
	
	Transform* tr0_;
	Transform* tr1_;
	std::string myName;
	std::string enemyName;
	bool running_;
};

