#pragma once

class Entity;

namespace ecs {
	using cmpId_type = unsigned __int8;
	enum cmpId : cmpId_type {
		TRANSFORM_H = 0,
		IMAGE_H = 1,
		FIGHTERCTRL_H = 2,
		HEALTH_H = 3,
		DEACCELERATION_H = 4,
		GUN_H = 5,
		OPPOSITESIDE_H = 6,
		FOLLOW_H = 7,
		DISABLEONEXIT_H = 8,
		GENERATIONS_H = 9,
		// do not remove this
		_LAST_CMP_ID
	};
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

	using grpId_type = unsigned __int8;
	enum grpId : grpId_type {
		_grp_GENERAL = 0,
		_grp_ASTEROIDS = 1,
		_grp_BULLETS = 2,
		
		_LAST_GRP_ID
	};
	constexpr grpId_type maxGroupId = _LAST_GRP_ID;

	using sysId_type = unsigned __int8;
	enum sysId : sysId_type {
		_SYS_ASTEROIDS = 0,
		_SYS_BULLET = 1,
		_SYS_COLLISIONS = 2,
		_SYS_FIGHTER = 3,
		_SYS_GAMECTRL = 4,
		_SYS_RENDER = 5,
		// do not remove this
		_LAST_SYS_ID
	};

	using msgId_type = unsigned __int8;
	enum msgId : msgId_type {

		_MSG_START = 0,
		_MSG_PAUSE = 1,
		_MSG_RESUME = 2,
		_MSG_NO_ASTEROIDS = 3,
		_MSG_SHOT = 4,
		_MSG_COL_AST_PLAYER = 5,
		_MSG_COL_AST_BULLET = 6,
		_MSG_GAMEOVER = 7,
		_LAST_MSG_ID
	};

	constexpr msgId_type maxMessageId = _LAST_MSG_ID;
	constexpr sysId_type maxSystemId = _LAST_SYS_ID;

	struct Message {
		msgId_type id;

		union {
			struct hitBulAst {
				Entity* bullet_;
				Entity* asteroid_;
			};
			hitBulAst hitBulAst;

			struct fighterStruct {
				float posX, posY, velX, velY, width, height, rotation;
			};
			fighterStruct fighterStruct;
		};
	};


}
