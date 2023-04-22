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
		FIGHTERINFO_H = 10,
		BULLETINFO_H = 11,
		// do not remove this
		_LAST_CMP_ID
	};
	constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

	using grpId_type = unsigned __int8;
	enum grpId : grpId_type {
		_grp_GENERAL = 0,
		_grp_ASTEROIDS = 1,
		_grp_BULLETS = 2,
		_grp_FIGHTERS = 3,
		
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
		_SYS_NETWORK = 6,
		_SYS_FIGHTERNET = 7,
		_SYS_BULLETNET = 8,
		_SYS_GAMECTRLNET = 9,
		_SYS_RENDERNET = 10,
		_SYS_COLLISIONSNET = 11,
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
		_MSG_COL_BULLET_PLAYER = 8,
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

			struct shoot {
				struct {
					float x;
					float y;
				} pos;
				struct {
					float x;
					float y;
				} vel;

				int id;
			};
			shoot shoot;

			struct killed {
				int playerId; // player id
			};
			killed killed;

			struct bullet_fighter {
				Entity* bullet_;
				Entity* fighter_;
			};
			bullet_fighter bullet_fighter;
		};
	};


}
