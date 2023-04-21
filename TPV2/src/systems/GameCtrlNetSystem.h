#pragma once
#include "../ecs/System.h"
#include "../components/FighterInfo.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/NetworkSystem.h"

class GameCtrlNetSystem :
    public System
{
public:

	enum GameState : uint8_t {
		_RUNNING, _STOPPED
	};

	GameCtrlNetSystem();
	virtual ~GameCtrlNetSystem();


	void initSystem() override;
	void update() override;
	void receive(const Message& m) override;

	void requestToStartGame();

	void startGame();

	void gameOver();

private:

	void handleBulletHitFighter(const Message&);

	uint8_t state_;
};
