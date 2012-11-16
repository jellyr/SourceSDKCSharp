#include "Stdafx.h"
#include "BaseEntity.h"


#include "ClientClassWrapper.h"
#include "ClientUnknown.h"

CBaseEntity::CBaseEntity(CClientClassWrapper* pClientClass)
{
	m_pClientClass = pClientClass;
	m_nEntIndex = -1;
	m_pEntity = pClientClass->Get()->Create();

	m_pClientUnknown = nullptr;
}

CBaseEntity::CBaseEntity(CClientClassWrapper* pClientClass, int entnum, int serialNum)
{
	m_pClientClass = pClientClass;
	m_nEntIndex = entnum;
	m_pEntity = pClientClass->Get()->Create();

	m_pClientUnknown = new CClientUnknown(m_pEntity, entnum, serialNum);
}

CBaseEntity::~CBaseEntity()
{
	delete m_pClientUnknown;
}

IClientUnknown*	CBaseEntity::GetIClientUnknown()
{
	return m_pClientUnknown;
}

void CBaseEntity::Release()
{
	m_pEntity->Release();
	m_pEntity->Handle = nullptr;

	delete this;
}

ClientClass* CBaseEntity::GetClientClass()
{
	return m_pClientClass;
}

void CBaseEntity::NotifyShouldTransmit(ShouldTransmitState_t state)
{
}

void CBaseEntity::OnPreDataChanged(DataUpdateType_t updateType)
{
}

void CBaseEntity::OnDataChanged(DataUpdateType_t updateType)
{
}

void CBaseEntity::PreDataUpdate(DataUpdateType_t updateType)
{
}

void CBaseEntity::PostDataUpdate(DataUpdateType_t updateType)
{
}

bool CBaseEntity::IsDormant()
{
	return false;
}

int CBaseEntity::entindex() const
{
	return m_nEntIndex;
}

void CBaseEntity::ReceiveMessage(int classID, bf_read &msg)
{
}

// Get the base pointer to the networked data that GetClientClass->m_pRecvTable starts at.
// (This is usually just the "this" pointer).
void* CBaseEntity::GetDataTableBasePtr()
{
	Assert(false); //check
	return m_pClientClass;
}

void CBaseEntity::SetDestroyedOnRecreateEntities()
{
}

