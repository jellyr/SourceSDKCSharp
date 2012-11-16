#include "Stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "ClientClassWrapper.h"
#include "ClientUnknownWrapper.h"
#include "dt_recv.h"


using namespace msclr::interop;
using namespace System;

typedef void (RecvVarProxyFnNoPtr)( const CRecvProxyData *pData, void *pStruct, void *pOut );
typedef IClientNetworkable*	(*CreateClientClassFnNoPtr)( int entnum, int serialNum );
typedef IClientNetworkable*	(*CreateEventFnNoPtr)();


class CClientNetworkable : public IClientNetworkable
{
public:
	CClientNetworkable(CClientClassWrapper* pClientClass)
	{
		m_pClientUnknown = nullptr;
		m_pClientClass = pClientClass;
		m_nEntIndex = -1;

		m_Networkable = pClientClass->Get()->Create();
	}

	CClientNetworkable(int entnum, int serialNum, CClientClassWrapper* pClientClass)
	{
		m_pClientUnknown = nullptr;
		m_pClientClass = pClientClass;
		m_nEntIndex = entnum;

		m_Networkable = pClientClass->Get()->Create(entnum, serialNum);
	}

	~CClientNetworkable()
	{
		delete m_pClientUnknown;
	}

	IClientUnknown*	GetIClientUnknown() override
	{
		if (m_pClientUnknown)
			return m_pClientUnknown;

		auto unknown = m_Networkable->ClientUnknown;

		if (!unknown)
			return nullptr;

		m_pClientUnknown = new CClientUnknownWrapper(unknown);
		return m_pClientUnknown;
	}

	void Release() override
	{
		m_Networkable->Release();
		delete this;
	}

	ClientClass* GetClientClass() override
	{
		return m_pClientClass;
	}

	void NotifyShouldTransmit(ShouldTransmitState_t state) override
	{
	}

	void OnPreDataChanged(DataUpdateType_t updateType) override
	{
	}

	void OnDataChanged(DataUpdateType_t updateType) override
	{
	}

	void PreDataUpdate(DataUpdateType_t updateType) override
	{
	}

	void PostDataUpdate(DataUpdateType_t updateType) override
	{
	}

	bool IsDormant() override
	{
		return false;
	}

	int entindex() const override
	{
		return m_nEntIndex;
	}

	void ReceiveMessage(int classID, bf_read &msg) override
	{
	}

	// Get the base pointer to the networked data that GetClientClass->m_pRecvTable starts at.
	// (This is usually just the "this" pointer).
	void* GetDataTableBasePtr() override
	{
		Assert(false); //check
		return m_pClientClass;
	}

	virtual void SetDestroyedOnRecreateEntities()
	{
	}

	M_IClientNetworkable^ Get()
	{
		return m_Networkable;
	}

private:
	int m_nEntIndex;
	CClientUnknownWrapper *m_pClientUnknown;
	CClientClassWrapper *m_pClientClass;
	gcroot<M_IClientNetworkable^> m_Networkable;
};

class CRecvPropWrapper
{
public:
	CRecvPropWrapper(M_RecvProp^ recvProp)
	{
		m_RecvProp = recvProp;
	}

	M_RecvProp^ Get()
	{
		return m_RecvProp;
	}

	gcroot<M_RecvProp^> m_RecvProp;
};

RecvTable* CreateRecvTable(IClientClass^ clientClass, std::vector<std::string> &propNames, std::vector<std::function<void (const CRecvProxyData *, void*, void*)>> &vFunctions);

CClientClassWrapper::CClientClassWrapper(IClientClass^ clientClass) 
	: ClientClass(nullptr, nullptr, nullptr, nullptr)
{
	m_ClientClass = clientClass;

	m_pRecvTable = CreateRecvTable(clientClass, m_vPropNames, m_vFunctions);
	m_szNetworkName = marshal_as<std::string>(clientClass->Name);
	m_pNetworkName = (char*)m_szNetworkName.c_str();

	if (clientClass->IsEvent)
	{
		m_CreateEvent = [&]() -> IClientNetworkable*
		{
			return new CClientNetworkable(this);
		};

		m_pCreateEventFn = (CreateEventFn)m_CreateEvent.target<CreateEventFnNoPtr>();
	}
	else
	{
		m_CreateEntity = [&](int entnum, int serialNum) -> IClientNetworkable*
		{
			return new CClientNetworkable(entnum, serialNum, this);
		};

		m_pCreateFn = (CreateClientClassFn)m_CreateEntity.target<CreateClientClassFnNoPtr>();
	}
}

static void DoAssert()
{
	Assert(false);
}

static RecvTable* CreateRecvTable(IClientClass^ clientClass, std::vector<std::string> &propNames, std::vector<std::function<void (const CRecvProxyData *, void*, void*)>> &vFunctions)
{
	auto pRt = new RecvTable();
	pRt->m_nProps = clientClass->RecvProps->Length;

	if (pRt->m_nProps == 0)
		return pRt;

	auto props = new RecvProp[pRt->m_nProps];

	int x=0;

	for each (auto i in clientClass->RecvProps)
	{
		auto pw = CRecvPropWrapper(i);
		std::string szName = marshal_as<std::string>(i->Name);
		propNames.push_back(szName);

		switch (i->Type)
		{
		case DPT_Int:
			{
				auto funct = [&pw](const CRecvProxyData *pData, void *pStruct, void *pOut){
					auto o = static_cast<CClientNetworkable*>(pOut)->Get();
					pw.Get()->SetValue(o, pData->m_Value.m_Int);
				};

				vFunctions.push_back(funct);
				props[x] = RecvPropInt((char*)propNames[x].c_str(), 0, SIZEOF_IGNORE, i->Flags, vFunctions[x].target<RecvVarProxyFnNoPtr>());
			}
			break;

		case DPT_Float:
			{
				auto funct = [&pw](const CRecvProxyData *pData, void *pStruct, void *pOut){
					auto o = static_cast<CClientNetworkable*>(pOut)->Get();
					pw.Get()->SetValue(o, pData->m_Value.m_Float);
				};

				vFunctions.push_back(funct);
				props[x] = RecvPropFloat((char*)propNames[x].c_str(), 0, SIZEOF_IGNORE, i->Flags, vFunctions[x].target<RecvVarProxyFnNoPtr>());
			}
			break;

		case DPT_String:
			{
				auto funct = [&pw](const CRecvProxyData *pData, void *pStruct, void *pOut){
					auto o = static_cast<CClientNetworkable*>(pOut)->Get();
					pw.Get()->SetValue(o, gcnew String(pData->m_Value.m_pString));
				};

				vFunctions.push_back(funct);
				props[x] = RecvPropString((char*)propNames[x].c_str(), 0, SIZEOF_IGNORE, i->Flags, vFunctions[x].target<RecvVarProxyFnNoPtr>());
			}
			break;

		default:
			DoAssert(); //todo
		}

		x++;
	}

	pRt->m_pProps = props;
	return pRt;
}