// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>
#include <cstdint>
#include "../CheckML.h"
#include "../ecs/System.h"

struct GameState;

class GameCtrlSystem : public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_GAMECTRL)


		enum Side : uint8_t {
		LEFT = 0, //
		RIGHT
	};

	enum State {
		NEWGAME, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
	};

	GameCtrlSystem();
	virtual ~GameCtrlSystem();

	inline State getState() {
		return state_;
	}

	void update() override;
	void recieve(const Message&) override;

	bool hasWin();

private:

	void startRound();
	void roundOver();
	void newGame();

	State state_;

	bool win = false;

};

