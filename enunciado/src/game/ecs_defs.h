// This file is part of the course TPV2@UCM - Samir Genaim


#pragma once

// Components list - must have at least one element
//
#define _CMPS_LIST_ \
	_TRANSFORM, \
	_IMAGE, \
	_RECTANGLEVIEWER, \
	_GAMESTATE, \
	_GAMEINFOMSGS,\
	_FIGHTERCTRL,\
	_DEACCELERATION,\
	_HEALTH,\
	_GENERATIONS,\
	_FOLLOW,\
	_FRAMEDIMAGE,\
	_DISABLEONEXIT

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	_grp_ASTEROIDS,\
	_grp_BULLETS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
	_hdlr_PLAYER

// Systems list - must have at least one element
//
#define _SYS_LIST_ \
	_sys_RENDER, \
	_sys_GAMECTRL, \
	_sys_COLLISIONS,\
	_sys_FIGHTER,\
	_sys_ASTEROIDS,\
	_sys_GUN,\
	_sys_BULLET

