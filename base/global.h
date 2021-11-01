#pragma once
// used: winapi includes
#include "common.h"
// used: vector
#include "sdk/datatypes/vector.h"
// used: qangle
#include "sdk/datatypes/qangle.h"
// used: usercmd
#include "sdk/datatypes/usercmd.h"
// used: baseentity
#include "sdk/entity.h"
// used: cconvar
#include "sdk/convar.h"

/*
 * GLOBALS
 * globally defined values
 * may used in any source/header file what includes in
 */
namespace G
{
	// current module
	inline HMODULE			hDll = nullptr;
	// last localplayer pointer
	inline CBaseEntity*		pLocal = nullptr;
	// last cmd pointer
	inline CUserCmd*		pCmd = nullptr;
	// last sendpacket state
	inline bool				bSendPacket = true;
	// last viewangles with allowed sendpacket
	inline QAngle			angRealView = { };
	// last aimstep restriction
	inline QAngle			angStep = { };
	// camera origin
	inline Vector			vecCamera = { };
	// recoil scale
	inline CConVar*         flRecoilScale = nullptr;
	// current weapon group (for legitbot)
	inline int32_t          iWeaponGroup = 0; // default
}
