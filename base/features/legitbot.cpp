#include "legitbot.h"

// used: cheat variables
#include "../core/variables.h"
// used: main window open state
#include "../core/menu.h"
// used: key state
#include "../utilities/inputsystem.h"
// used: globals, cliententitylist interfaces
#include "../core/interfaces.h"
// used: backtracking
#include "lagcompensation.h"
// used: globals
#include "../global.h"
#include "../utilities/math.h"

/*
	if (!Settings::Aimbot::RCS::enabled) // credits @ aimtux
		return;

	if (!(cmd->buttons & IN_ATTACK))
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	QAngle CurrentPunch = *localplayer->GetAimPunchAngle();
	bool isSilent = Settings::Aimbot::silent;
	bool hasTarget = Settings::Aimbot::AutoAim::enabled && player && shouldAim;

	if (!Settings::Aimbot::RCS::always_on && !hasTarget)
		return;

	if (isSilent || hasTarget)
	{
		angle.x -= CurrentPunch.x * Settings::Aimbot::RCS::valueX;
		angle.y -= CurrentPunch.y * Settings::Aimbot::RCS::valueY;
	}
	else if (localplayer->GetShotsFired() > 1)
	{
		QAngle NewPunch = { CurrentPunch.x - RCSLastPunch.x, CurrentPunch.y - RCSLastPunch.y, 0 };

		angle.x -= NewPunch.x * Settings::Aimbot::RCS::valueX;
		angle.y -= NewPunch.y * Settings::Aimbot::RCS::valueY;
	}

	RCSLastPunch = CurrentPunch;
*/

void CLegitBot::Run(CUserCmd* pCmd, CBaseEntity* pLocal, bool& bSendPacket)
{
	if (!pLocal->IsAlive())
		return;

	CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();

	if (pWeapon == nullptr)
		return;

	// disable when in-menu for more legit (lol)
	if (W::bMainOpened)
		return;

	static QAngle prev_punch = { 0.0f, 0.0f, 0.0f };

	int32_t iWeaponGrp = G::iGetWeaponGroup(pLocal->GetWeapon());
	if (iWeaponGrp > 0 && !C::Get<bool>(Vars.aLegitSettings[iWeaponGrp].bOverrideDefault))
		iWeaponGrp = 0;
	G::flRecoilScale = I::ConVar->FindVar(XorStr("weapon_recoil_scale"));

	if (C::Get<bool>(Vars.aLegitSettings[iWeaponGrp].bEnableRcs) && (pCmd->iButtons & IN_ATTACK))
	{
		float flRecoilAmount = G::flRecoilScale->GetFloat();
		int iRcsAmt = C::Get<int>(Vars.aLegitSettings[iWeaponGrp].iRecoilScale);
		if (C::Get<int>(Vars.aLegitSettings[iWeaponGrp].iRcsFlags) == 1)
		{
			if (pLocal->GetShotsFired() >= C::Get<int>(Vars.aLegitSettings[iWeaponGrp].iRcsShots))
			{
				pCmd->angViewPoint -= (pLocal->GetPunch() * flRecoilAmount);
			}
		}
		else // since we dont have any sort of actual aimbot yet, this'll do.
		{
			pCmd->angViewPoint -= (pLocal->GetPunch() * flRecoilAmount);
		}
	}

	for (int i = 1; i <= I::Globals->nMaxClients; i++)
	{
		CBaseEntity* pEntity = I::ClientEntityList->Get<CBaseEntity>(i);

		if (pEntity == nullptr || !pEntity->IsPlayer() || pEntity->IsDormant() || !pEntity->IsAlive() || pEntity->HasImmunity())
			continue;
	}
}
