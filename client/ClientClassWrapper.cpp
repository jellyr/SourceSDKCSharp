#include "Stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "ClientClassWrapper.h"
#include "dt_recv.h"

#include "BaseEntity.h"


using namespace SourceSDK::Core::Interfaces::Shared;
using namespace msclr::interop;
using namespace System;

typedef void (RecvVarProxyFnNoPtr)( const CRecvProxyData *pData, void *pStruct, void *pOut );
typedef IClientNetworkable*	(*CreateClientClassFnNoPtr)( int entnum, int serialNum );
typedef IClientNetworkable*	(*CreateEventFnNoPtr)();


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

static void DoAssert()
{
	Assert(false);
}


CClientClassWrapper::CClientClassWrapper(IClientClass^ clientClass) 
	: ClientClass(nullptr, nullptr, nullptr, nullptr)
{
	m_ClientClass = clientClass;

	m_pRecvTable = CreateRecvTable();
	m_szNetworkName = marshal_as<std::string>(clientClass->Name);
	m_pNetworkName = (char*)m_szNetworkName.c_str();

	if (clientClass->IsEvent)
	{
		m_CreateEvent = [&]() -> IClientNetworkable*
		{
			return new CBaseEntity(this);
		};

		m_pCreateEventFn = (CreateEventFn)m_CreateEvent.target<CreateEventFnNoPtr>();
	}
	else
	{
		m_CreateEntity = [&](int entnum, int serialNum) -> IClientNetworkable*
		{
			return new CBaseEntity(this, entnum, serialNum);
		};

		m_pCreateFn = (CreateClientClassFn)m_CreateEntity.target<CreateClientClassFnNoPtr>();
	}
}

RecvTable* CClientClassWrapper::CreateRecvTable()
{
	m_szNetTableName = marshal_as<std::string>(m_ClientClass->RecvNetTableName);

	auto pRt = new RecvTable();
	pRt->m_nProps = m_ClientClass->RecvProps->Length;
	pRt->m_pNetTableName = (char*)m_szNetTableName.c_str();

	if (pRt->m_nProps == 0)
	{
		pRt->m_nProps = 1;
		pRt->m_pProps = new RecvProp[1];
		pRt->m_pProps[0] = RecvPropInt("should_never_see_this", 0, sizeof(int));

		return pRt;
	}

	auto props = new RecvProp[pRt->m_nProps];

	int x=0;

	for each (auto i in m_ClientClass->RecvProps)
	{
		auto pw = CRecvPropWrapper(i);
		std::string szName = marshal_as<std::string>(i->Name);
		m_vPropNames.push_back(szName);

		switch (i->Type)
		{
		case DPT_Int:
			{
				auto funct = [&pw](const CRecvProxyData *pData, void *pStruct, void *pOut){
					auto o = static_cast<CBaseEntity*>(pOut)->Get();
					pw.Get()->SetValue(o, pData->m_Value.m_Int);
				};

				m_vFunctions.push_back(funct);
				props[x] = RecvPropInt((char*)m_vPropNames[x].c_str(), 0, SIZEOF_IGNORE, i->Flags, m_vFunctions[x].target<RecvVarProxyFnNoPtr>());
			}
			break;

		case DPT_Float:
			{
				auto funct = [&pw](const CRecvProxyData *pData, void *pStruct, void *pOut){
					auto o = static_cast<CBaseEntity*>(pOut)->Get();
					pw.Get()->SetValue(o, pData->m_Value.m_Float);
				};

				m_vFunctions.push_back(funct);
				props[x] = RecvPropFloat((char*)m_vPropNames[x].c_str(), 0, SIZEOF_IGNORE, i->Flags, m_vFunctions[x].target<RecvVarProxyFnNoPtr>());
			}
			break;

		case DPT_String:
			{
				auto funct = [&pw](const CRecvProxyData *pData, void *pStruct, void *pOut){
					auto o = static_cast<CBaseEntity*>(pOut)->Get();
					pw.Get()->SetValue(o, gcnew String(pData->m_Value.m_pString));
				};

				m_vFunctions.push_back(funct);
				props[x] = RecvPropString((char*)m_vPropNames[x].c_str(), 0, SIZEOF_IGNORE, i->Flags, m_vFunctions[x].target<RecvVarProxyFnNoPtr>());
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