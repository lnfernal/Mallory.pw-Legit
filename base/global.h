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
// used: weaponsystem
#include "core/interfaces.h"

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
	// cur wep group
	__forceinline int iGetWeaponGroup(CBaseCombatWeapon* pWeapon)
	{
		CCSWeaponData* pWeaponData = I::WeaponSystem->GetWeaponData(pWeapon->GetItemDefinitionIndex());
		if (pWeaponData->nWeaponType == WEAPONTYPE_KNIFE)
			return 0; // default

		static int32_t iWepGroup = 0;

		if (pWeapon->GetItemDefinitionIndex() == WEAPON_DEAGLE || pWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
		{
			iWepGroup = 2;
		}
		else
		{
			switch (pWeaponData->nWeaponType)
			{
			case WEAPONTYPE_PISTOL:
				iWepGroup = 1;
				break;
			case WEAPONTYPE_MACHINEGUN:
			case WEAPONTYPE_SHOTGUN:
				iWepGroup = 4;
				break;
			case WEAPONTYPE_RIFLE:
				iWepGroup = 5;
				break;
			case WEAPONTYPE_SNIPER:
				iWepGroup = 6;
				break;
			case WEAPONTYPE_SUBMACHINEGUN:
				iWepGroup = 3;
				break;
			}
		}
		return iWepGroup;
	}
}
