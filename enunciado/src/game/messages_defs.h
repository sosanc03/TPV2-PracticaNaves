// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {

	_m_GAME_START,
	_m_GAME_PAUSED,
	_m_GAME_RESUME,
	_m_NO_ASTEROIDS,
	_m_GUN_SHOT,
	_m_COL_AST_PLAYER,
	_m_COL_BULLET_AST
};


struct Message {
	msgId_type id;

	union {

		struct {
			ecs::Entity* bull;
			ecs::Entity* ast;
		} bullet_hit_asteroid;

		struct {
			float posX, posY, vX, vY, width, height, rotation;
		} FighterCoords;
	};
};
