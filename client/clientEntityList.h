#pragma once


#include "icliententitylist.h"
#include "basehandle.h"

class CSourceSDKClientEntityList : public IClientEntityList
{
public:
	IClientNetworkable*	GetClientNetworkable(int entnum) override;
	IClientNetworkable*	GetClientNetworkableFromHandle(CBaseHandle hEnt) override;
	IClientUnknown*	GetClientUnknownFromHandle(CBaseHandle hEnt) override;
	IClientEntity* GetClientEntity(int entnum) override;
	IClientEntity* GetClientEntityFromHandle(CBaseHandle hEnt) override;

	int	NumberOfEntities(bool bIncludeNonNetworkable) override;
	int	GetHighestEntityIndex() override;
	void SetMaxEntities(int maxents) override;
	int GetMaxEntities() override;
};