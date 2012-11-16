#pragma once

#include "iclientnetworkable.h"

class CClientClassWrapper;

using namespace SourceSDK::Core::Interfaces::Client;
using namespace SourceSDK::Core::Interfaces::Shared;

class CBaseEntity : public IClientNetworkable
{
public:
	CBaseEntity(CClientClassWrapper* pClientClass);
	CBaseEntity(CClientClassWrapper* pClientClass, int entnum, int serialNum);
	~CBaseEntity();

	IClientUnknown*	GetIClientUnknown() override;

	void Release() override;

	ClientClass* GetClientClass() override;

	void NotifyShouldTransmit(ShouldTransmitState_t state) override;

	void OnPreDataChanged(DataUpdateType_t updateType) override;
	void OnDataChanged(DataUpdateType_t updateType) override;
	void PreDataUpdate(DataUpdateType_t updateType) override;
	void PostDataUpdate(DataUpdateType_t updateType) override;

	bool IsDormant() override;

	int entindex() const override;

	void ReceiveMessage(int classID, bf_read &msg) override;

	void* GetDataTableBasePtr() override;

	virtual void SetDestroyedOnRecreateEntities() override;

	BaseEntityClient^ Get()
	{
		return m_pEntity;
	}

private:
	int m_nEntIndex;
	IClientUnknown *m_pClientUnknown;
	CClientClassWrapper *m_pClientClass;

	gcroot<BaseEntityClient^> m_pEntity;
};