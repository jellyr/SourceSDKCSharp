#pragma once

#include "eiface.h"


class CSourceSDKServerGameEnts : public IServerGameEnts
{
public:
	void SetDebugEdictBase(edict_t *base) override;
	void MarkEntitiesAsTouching( edict_t *e1, edict_t *e2 ) override;
	void FreeContainingEntity( edict_t * ) override; 

	edict_t* BaseEntityToEdict( CBaseEntity *pEnt ) override;
	CBaseEntity* EdictToBaseEntity( edict_t *pEdict ) override;

	void CheckTransmit( CCheckTransmitInfo *pInfo, const unsigned short *pEdictIndices, int nEdicts ) override;
};