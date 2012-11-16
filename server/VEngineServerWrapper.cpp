#include "Stdafx.h"

#include "VEngineServerWrapper.h"
#include "EdictWrapper.h"
#include "BaseEntity.h"

using namespace SourceSDK::Core::Interfaces::Server;



VEngineServerWrapper::VEngineServerWrapper(IVEngineServer* pEngine)
{
	m_pEngine = pEngine;
}

bool VEngineServerWrapper::LoadGameState(String^ mapName, bool createPlayers)
{
	std::string szMapName = marshal_as<std::string>(mapName);
	return m_pEngine->LoadGameState(szMapName.c_str(), createPlayers);
}

void VEngineServerWrapper::LoadAdjacentEnts(String^ oldLevel, String^ landmarkName)
{
	std::string szOldLevel = marshal_as<std::string>(oldLevel);
	std::string szLandmark = marshal_as<std::string>(landmarkName);

	m_pEngine->LoadAdjacentEnts(szOldLevel.c_str(), szLandmark.c_str());
}

void VEngineServerWrapper::CreateEdict(IEntity^ entity, int index)
{
	edict_t* edict = m_pEngine->CreateEdict(index);

	auto pEntity = new CBaseEntity(entity, edict);
	edict->SetEdict(pEntity, true);
	edict->m_pNetworkable = pEntity->GetNetworkable();

	entity->Edict = gcnew EdictWrapper(edict);
}
		
void VEngineServerWrapper::RemoveEdict(IEdict^ edict)
{
	EdictWrapper^ ew = dynamic_cast<EdictWrapper^>(edict);

	if (ew)
		m_pEngine->RemoveEdict(ew->Get());
}

int VEngineServerWrapper::IndexOfEdict(IEdict^ edict)
{
	EdictWrapper^ ew = dynamic_cast<EdictWrapper^>(edict);

	if (!ew)
		return -1;

	return m_pEngine->IndexOfEdict(ew->Get());
}