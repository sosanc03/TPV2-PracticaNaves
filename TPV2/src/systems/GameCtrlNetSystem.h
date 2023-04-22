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
		RUNNING, PAUSED
	};

	GameCtrlNetSystem();
	virtual ~GameCtrlNetSystem();

	void receive(const Message& m) override;
	void update() override;

	void GameStart();
	void requestToStartGame();

private:

	void GameOver(const Message&);

	uint8_t state_;
};
