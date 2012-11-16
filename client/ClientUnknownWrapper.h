#pragma once

#include "iclientunknown.h"
#include "basehandle.h"
#include <gcroot.h>


using namespace SourceSDK::Core::Interfaces::Client;

class CCollideableWrapper;
class CClientNetworkableWrapper;
class CClientRenderableWrapper;
class CClientEntityWrapper;
class C_BaseEntityWrapper;
class CClientThinkableWrapper;

class CClientUnknownWrapper : public IClientUnknown
{
public:
	CClientUnknownWrapper(M_IClientUnknown^ clientUnknown);
	~CClientUnknownWrapper();

	ICollideable* GetCollideable() override;
	IClientNetworkable* GetClientNetworkable() override;
	IClientRenderable* GetClientRenderable() override;
	IClientEntity* GetIClientEntity() override;
	C_BaseEntity* GetBaseEntity() override;
	IClientThinkable* GetClientThinkable() override;

	void SetRefEHandle(const CBaseHandle &handle) override;
	const CBaseHandle& GetRefEHandle() const override;

private:
	CCollideableWrapper *m_pCollideable;
	CClientNetworkableWrapper *m_pClientNetworkable;
	CClientRenderableWrapper *m_pClientRenderable;
	CClientEntityWrapper *m_pClientEntity;
	C_BaseEntityWrapper *m_pBaseEntity;
	CClientThinkableWrapper *m_pClientThinkable;

	CBaseHandle m_BaseHandle;
	gcroot<M_IClientUnknown^> m_ClientClass;
};