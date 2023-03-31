// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {

	_MSG_START = 0,
	_MSG_PAUSE = 1,
	_MSG_RESUME = 2,
	_MSG_NO_ASTEROIDS = 3,
	_MSG_SHOT = 4,
	_MSG_COL_AST_PLAYER = 5,
	_MSG_COL_AST_BULLET = 6,
	_LAST_MSG_ID
};


struct Message {
	msgId_type id;

	union {

		struct {
			ecs::Entity* bullet_;
			ecs::Entity* asteroid_;
		} hitBulAst;

		struct {
			float posX, posY, velX, velY, width, height, rotation;
		} fighterStruct;
	};
};
