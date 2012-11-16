#pragma once

#include "eiface.h"

using namespace System;
using namespace SourceSDK::Core::Interfaces::Server;
using namespace SourceSDK::Core::Interfaces::Shared;

ref class VEngineServerWrapper : public NI_VEngineServer
{
public:
	VEngineServerWrapper(IVEngineServer* pEngine);

	virtual bool LoadGameState(String^ mapName, bool createPlayers);

	virtual void LoadAdjacentEnts(String^ oldLevel, String^ landmarkName);

	virtual void CreateEdict(IEntity^ entity, int index);
		
	virtual void RemoveEdict(IEdict^ edict);

	virtual int IndexOfEdict(IEdict^ edict);

	IVEngineServer* Get()
	{
		return m_pEngine;
	}

private:
	IVEngineServer* m_pEngine;
};