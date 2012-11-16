#include "Stdafx.h"
#include "ClientUnknown.h"

#include "HandleWrapper.h"

using namespace SourceSDK::Core::Interfaces::Shared;

CClientUnknown::CClientUnknown(BaseEntityClient^ entity, int entnum, int serialNum)
{
	m_pEntity = entity;
	m_Handle.Init(entnum, serialNum);
	m_pEntity->Handle = gcnew HandleWrapper(m_Handle);

	m_pCollideable = nullptr;
	m_pClientNetworkable = nullptr;
	m_pClientRenderable = nullptr;
	m_pClientEntity = nullptr;
	m_pBaseEntity = nullptr;
	m_pClientThinkable = nullptr;
}

CClientUnknown::~CClientUnknown()
{
	//delete m_pCollideable;
	//delete m_pClientNetworkable;
	//delete m_pClientRenderable;
	//delete m_pClientEntity;
	//delete m_pBaseEntity;
	//delete m_pClientThinkable;
}

ICollideable* CClientUnknown::GetCollideable()
{
	Assert(false);
	return nullptr;
	//if (m_pCollideable)
	//	return m_pCollideable;

	//auto object = m_ClientClass->Collideable;

	//if (!object)
	//	return nullptr;

	//m_pCollideable = new CClientUnknown(object);
	//return m_pCollideable;
}

IClientNetworkable* CClientUnknown::GetClientNetworkable()
{
	Assert(false);
	return nullptr;
}

IClientRenderable* CClientUnknown::GetClientRenderable()
{
	Assert(false);
	return nullptr;
}

IClientEntity* CClientUnknown::GetIClientEntity()
{
	Assert(false);
	return nullptr;
}

C_BaseEntity* CClientUnknown::GetBaseEntity()
{
	Assert(false);
	return nullptr;
}

IClientThinkable* CClientUnknown::GetClientThinkable()
{
	Assert(false);
	return nullptr;
}

void CClientUnknown::SetRefEHandle(const CBaseHandle &handle)
{
	m_Handle = handle;
}

const CBaseHandle& CClientUnknown::GetRefEHandle() const
{
	return m_Handle;
}