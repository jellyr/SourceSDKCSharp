#include "Stdafx.h"

#include "VEngineServerWrapper.h"
#include "EdictWrapper.h"

#include "ServerClassWrapper.h"

using namespace SourceSDK::Core::Interfaces::Server;


class CServerNetworkable : public IServerNetworkable
{
public:
	CServerNetworkable(IEntity^ entity, edict_t* pEdict, CBaseEntity* pBaseEntity, IHandleEntity* pHandleEntity)
	{
		m_pEntity = entity;
		m_pEdict = pEdict;
		m_pBaseEntity = pBaseEntity;
		m_pHandleEntity = pHandleEntity;
		m_szClassName = marshal_as<std::string>(m_pEntity->ClassName);
	}

	virtual IHandleEntity *GetEntityHandle() override
	{
		return m_pHandleEntity;
	}

	// Tell the engine which class this object is.
	virtual ServerClass* GetServerClass() override
	{
		ServerClass *pTemp = g_pServerClassHead;

		while (pTemp)
		{
			auto scw = static_cast<CServerClassWrapper*>(pTemp);

			if (scw && scw->GetNameAsString() == m_szClassName)
				return scw;

			pTemp = pTemp->m_pNext;
		}

		return nullptr;
	}

	virtual CBaseEntity* GetBaseEntity() override
	{
		return m_pBaseEntity;
	}

	virtual edict_t *GetEdict() const  override
	{
		return m_pEdict;
	}

	virtual const char* GetClassName() const  override
	{
		return m_szClassName.c_str();
	}

	virtual void Release() override
	{
		m_pEntity->Release();
	}

	virtual int AreaNum() const override
	{
		return m_pEntity->AreaNum;
	}

	// In place of a generic QueryInterface.
	virtual CBaseNetworkable* GetBaseNetworkable() override
	{
		return nullptr;
	}

	virtual PVSInfo_t* GetPVSInfo() override
	{
		return nullptr;
	}

private:
	std::string m_szClassName;

	edict_t *m_pEdict;
	IHandleEntity* m_pHandleEntity;
	CBaseEntity* m_pBaseEntity;

	gcroot<IEntity^> m_pEntity;
};

class CHandleEntity : public IHandleEntity
{
public:
	virtual void SetRefEHandle(const CBaseHandle &handle) override
	{
		m_Handle = handle;
	}

	virtual const CBaseHandle& GetRefEHandle() const
	{
		return m_Handle;
	}

	CBaseHandle m_Handle;
};

class CBaseEntity : public IServerEntity
{
public:
	CBaseEntity(IEntity^ entity, edict_t* pEdict)
		: m_ServerNetworkable(entity, pEdict, this, &m_HandleEntity)
	{
		m_pEntity = entity;
	}

	virtual int GetModelIndex() const override
	{
		return m_pEntity->ModelIndex;
	}

	virtual void SetModelIndex(int index) override
	{
		m_pEntity->ModelIndex = index;
	}

	virtual string_t GetModelName() const override
	{
		m_szModelName = marshal_as<std::string>(m_pEntity->ModelName);
		return MAKE_STRING(m_szModelName.c_str());
	}

	virtual ICollideable* GetCollideable() override
	{
		return nullptr;
	}

	virtual IServerNetworkable*	GetNetworkable() override
	{
		return &m_ServerNetworkable;
	}

	virtual CBaseEntity* GetBaseEntity() override
	{
		return this;
	}

	virtual void SetRefEHandle(const CBaseHandle &handle) override
	{
		m_HandleEntity.SetRefEHandle(handle);
	}

	virtual const CBaseHandle& GetRefEHandle() const
	{
		return m_HandleEntity.GetRefEHandle();
	}

private:
	CHandleEntity m_HandleEntity;
	CServerNetworkable m_ServerNetworkable;

	mutable std::string m_szModelName;
	gcroot<IEntity^> m_pEntity;
};


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