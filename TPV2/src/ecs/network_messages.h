#pragma once

#include "../sdlutils/SDLNetUtils.h"

namespace net {

	enum MsgId : Uint8 {
		_CONNECTION_REQUEST = 0, //
		_REQUEST_ACCEPTED = 1, //
		_START_GAME = 2, //
		_START_GAME_REQUEST = 3, //
		_FIGHTER_POS = 4, //
		_BULLET_POS = 5, //
		_BULLET_SHOT = 6,

		_LASTMSG
	};

	struct Message {
		Uint8 id;

		//
		_IMPL_SERIALIAZION_(id)
	};
	struct NameMessage :Message {
		char nameSend[11]; // nombre del player, 10 caracteres maximo

		_IMPL_SERIALIAZION_WITH_BASE_(Message, nameSend)
	};

	struct ReqAccMsg : Message {

		Uint8 side;
		char nameSend[11]; // nombre del player, 10 caracteres maximo
		_IMPL_SERIALIAZION_WITH_BASE_(Message, side, nameSend)
		//
	};


	struct FighterPosMsg : Message {

		Uint8 side;
		float x;
		float y;
		float rot;

		//
		_IMPL_SERIALIAZION_WITH_BASE_(Message, side, x, y, rot)
	};


	struct BulletPosMsg : Message {

		Uint8 side;

		float x;
		float y;
		float rot;
		//
		_IMPL_SERIALIAZION_WITH_BASE_(Message, side, x, y, rot)
	};
	struct BulletShotMsg : Message {

		Uint8 side;
		float posX;
		float posY;
		float velX;
		float velY;
		//
		_IMPL_SERIALIAZION_WITH_BASE_(Message, side, posX, posY, velX, velY)
	};



	struct StartRequestMsg : Message {

		Uint8 side;

		//
		_IMPL_SERIALIAZION_WITH_BASE_(Message, side)
	};


}
