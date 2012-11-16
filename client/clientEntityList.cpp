#include "Stdafx.h"
#include "clientEntityList.h"


IClientNetworkable*	CSourceSDKClientEntityList::GetClientNetworkable(int entnum)
{
	return nullptr;
}

IClientNetworkable*	CSourceSDKClientEntityList::GetClientNetworkableFromHandle(CBaseHandle hEnt)
{
	return nullptr;
}

IClientUnknown*	CSourceSDKClientEntityList::GetClientUnknownFromHandle(CBaseHandle hEnt)
{
	return nullptr;
}

IClientEntity* CSourceSDKClientEntityList::GetClientEntity(int entnum)
{
	return nullptr;
}

IClientEntity* CSourceSDKClientEntityList::GetClientEntityFromHandle(CBaseHandle hEnt)
{
	return nullptr;
}

int	CSourceSDKClientEntityList::NumberOfEntities(bool bIncludeNonNetworkable)
{
	return 0;
}

int	CSourceSDKClientEntityList::GetHighestEntityIndex()
{
	return 0;
}

void CSourceSDKClientEntityList::SetMaxEntities(int maxents)
{
}

int CSourceSDKClientEntityList::GetMaxEntities()
{
	return 255;
}
