// This file is part of the course TPV2@UCM - Samir Genaim


#pragma once

// Components list - must have at least one element
//
#define _CMPS_LIST_ \
	_TRANSFORM, \
	_IMAGE, \
	_FIGHTERCTRL, \
	_STARMOTION, \
	_GAMECTRL, \
	_STOPONBORDER,\
    _DEACCELERATION,\
   _SHOWATOPPOSIDESIDE,\
	_GUNCTRL,\
	_HEALTHCTRL,\
_FRAMEDIMAGE,\
_GENERATIONS,\
_FOLLOW,\
_DISABLEGUN,\
_STATE


// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	_grp_STARS,\
	_grp_BALAS,\
_ASTEROID_GRP

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    _hdlr_FIGHTER, \
	_hdlr_GAMEINFO

#define _SYSLIST \
    _sys_FIGHTER, \
    _sys_PADDLES, \
    _sys_RENDER, \
    _sys_GAMECTRL, \
    _sys_COLLISIONS


