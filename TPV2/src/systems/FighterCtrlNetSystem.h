#pragma once
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
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
	FighterCtrlNetSystem();
	virtual ~FighterCtrlNetSystem() {};

	void receive(const Message&) override;
	void initSystem() override;
	void update() override;
	void changeFighterPos(Uint16 side, float x, float y, float rot);

	Entity* fighter0_;
	Entity* fighter1_;
private:
	void createShip0();
	void createShip1();


	void GameStart(const Message&);
	void GameOver(const Message&);
	void collision(const Message&);

	void fighterCtrlUpdate(Transform* tr_, FighterCtrl* fi_);
	void deAccelerationUpdate(Transform* tr_, DeAcceleration* de_);
	void showAtOppositeSideUpdate(Transform* tr_, ShowAtOppositeSide* op_);
	
	NetworkSystem* netSys;
	
	Transform* tr0_;
	Transform* tr1_;
	bool running_;
};

