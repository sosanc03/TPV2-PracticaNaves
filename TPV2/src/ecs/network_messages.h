// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../sdlutils/SDLNetUtils.h"

namespace net {

	enum MsgId : Uint8 {
		_CONNECTION_REQUEST, //
		_REQUEST_ACCEPTED, //
		_REQUEST_REFUSED, //
		_FIGHTER_POS, //
		_BULLET_POS, //
		_BULLET_SHOT,
		_START_GAME_REQUEST, //
		_START_THE_GAME, //
		_GAME_OVER, //
		_DISCONNECTING
	};

	struct Message {
		Uint8 id;

		//
		_IMPL_SERIALIAZION_(id)
	};
	struct NameMessage :Message {
		char nameSend[11];

		_IMPL_SERIALIAZION_WITH_BASE_(Message, nameSend)
	};

	struct ReqAccMsg : Message {

		Uint8 side;
		char nameSend[11];
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
