#include "Stdafx.h"
#include "ClientUnknownWrapper.h"


using namespace SourceSDK::Core::Interfaces::Shared;

CClientUnknownWrapper::CClientUnknownWrapper(M_IClientUnknown^ clientUnknown)
{
	m_ClientClass = clientUnknown;

	m_pCollideable = nullptr;
	m_pClientNetworkable = nullptr;
	m_pClientRenderable = nullptr;
	m_pClientEntity = nullptr;
	m_pBaseEntity = nullptr;
	m_pClientThinkable = nullptr;
}

CClientUnknownWrapper::~CClientUnknownWrapper()
{
	//delete m_pCollideable;
	//delete m_pClientNetworkable;
	//delete m_pClientRenderable;
	//delete m_pClientEntity;
	//delete m_pBaseEntity;
	//delete m_pClientThinkable;
}

ICollideable* CClientUnknownWrapper::GetCollideable()
{
	Assert(false);
	return nullptr;
	//if (m_pCollideable)
	//	return m_pCollideable;

	//auto object = m_ClientClass->Collideable;

	//if (!object)
	//	return nullptr;

	//m_pCollideable = new CClientUnknownWrapper(object);
	//return m_pCollideable;
}

IClientNetworkable* CClientUnknownWrapper::GetClientNetworkable()
{
	Assert(false);
	return nullptr;
}

IClientRenderable* CClientUnknownWrapper::GetClientRenderable()
{
	Assert(false);
	return nullptr;
}

IClientEntity* CClientUnknownWrapper::GetIClientEntity()
{
	Assert(false);
	return nullptr;
}

C_BaseEntity* CClientUnknownWrapper::GetBaseEntity()
{
	Assert(false);
	return nullptr;
}

IClientThinkable* CClientUnknownWrapper::GetClientThinkable()
{
	Assert(false);
	return nullptr;
}

void CClientUnknownWrapper::SetRefEHandle(const CBaseHandle &handle)
{
	m_ClientClass->BaseHandle = gcnew BaseHandle(handle.ToInt());
	m_BaseHandle = handle;
}

const CBaseHandle& CClientUnknownWrapper::GetRefEHandle() const
{
	return m_BaseHandle;
}