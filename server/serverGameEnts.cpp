#include "Stdafx.h"
#include "serverGameEnts.h"

#include "EdictWrapper.h"

void CSourceSDKServerGameEnts::SetDebugEdictBase(edict_t *base)
{
	m_pServerGameEnts->SetDebugEdictBase(gcnew EdictWrapper(base));
}

void CSourceSDKServerGameEnts::MarkEntitiesAsTouching(edict_t *e1, edict_t *e2)
{
	m_pServerGameEnts->MarkEntitiesAsTouching(gcnew EdictWrapper(e1), gcnew EdictWrapper(e2));
}

void CSourceSDKServerGameEnts::FreeContainingEntity(edict_t *edict)
{
	m_pServerGameEnts->FreeContainingEntity(gcnew EdictWrapper(edict));
}

edict_t* CSourceSDKServerGameEnts::BaseEntityToEdict(CBaseEntity *pEnt)
{
	if (pEnt == nullptr)
		return nullptr;

	return pEnt->GetNetworkable()->GetEdict();
}

CBaseEntity* CSourceSDKServerGameEnts::EdictToBaseEntity(edict_t *pEdict)
{
	return pEdict->GetUnknown()->GetBaseEntity();
}

void CSourceSDKServerGameEnts::CheckTransmit(CCheckTransmitInfo *pInfo, const unsigned short *pEdictIndices, int nEdicts)
{
	Assert(false);
	//m_pServerGameEnts->CheckTransmit()
}