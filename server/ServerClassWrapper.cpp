#include "Stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "ServerClassWrapper.h"


using namespace msclr::interop;

typedef void (SendVarProxyFnNoPtr)( const SendProp *pProp, const void *pStructBase, const void *pData, DVariant *pOut, int iElement, int objectID );

class CSendPropWrapper
{
public:
	CSendPropWrapper(M_SendProp^ sendProp)
	{
		m_SendProp = sendProp;
	}

	M_SendProp^ Get() const
	{
		return m_SendProp;
	}

	gcroot<M_SendProp^> m_SendProp;
};

static void DoAssert()
{
	Assert(false);
}

CServerClassWrapper::CServerClassWrapper(IServerClass^ serverClass)
	: ServerClass(nullptr, nullptr)
{
	m_pServerClass = serverClass;

	m_szNetworkName = marshal_as<std::string>(serverClass->Name);
	m_pNetworkName = (char*)m_szNetworkName.c_str();

	m_pTable = CreateSendTable();
}

SendTable* CServerClassWrapper::CreateSendTable()
{
	auto ret = new SendTable();
	auto props = m_pServerClass->SendProps;

	ret->m_pProps = new SendProp[props->Length];
	int x=0;

	for each (auto p in props)
	{
		auto pw = CSendPropWrapper(p);

		std::string szName = marshal_as<std::string>(p->Name);
		m_vPropNames.push_back(szName);

		switch (p->Type)
		{
		case DPT_Int:
			{
				auto funct = [pw](const SendProp *pProp, const void *pStructBase, const void *pData, DVariant *pOut, int iElement, int objectID){

					System::Object^ o = nullptr; //pData
					pOut->m_Int = pw.Get()->GetInt(o);
				};

				m_vFunctions.push_back(funct);
				ret->m_pProps[x] = SendPropInt((char*)m_vPropNames[x].c_str(), 0, SIZEOF_IGNORE, p->FieldLength, p->Flags, m_vFunctions[x].target<SendVarProxyFnNoPtr>());
			}
			break;

		case DPT_Float:
			{
				auto funct = [pw](const SendProp *pProp, const void *pStructBase, const void *pData, DVariant *pOut, int iElement, int objectID){

					System::Object^ o = nullptr; //pData
					pOut->m_Float = pw.Get()->GetFloat(o);
				};

				m_vFunctions.push_back(funct);
				ret->m_pProps[x] = SendPropFloat((char*)m_vPropNames[x].c_str(), 0, SIZEOF_IGNORE, p->FieldLength, p->Flags, p->FloatMin, p->FloatMax, m_vFunctions[x].target<SendVarProxyFnNoPtr>());
			}
			break;

		case DPT_String:
			{
				auto funct = [&, pw, x](const SendProp *pProp, const void *pStructBase, const void *pData, DVariant *pOut, int iElement, int objectID){

					System::Object^ o = nullptr; //pData
					m_vPropStringVals[x] = marshal_as<std::string>(pw.Get()->GetString(o));
					pOut->m_pString = (char*)m_vPropStringVals[x].c_str();
				};

				m_vFunctions.push_back(funct);
				ret->m_pProps[x] = SendPropString((char*)m_vPropNames[x].c_str(), 0, p->FieldLength, p->Flags, m_vFunctions[x].target<SendVarProxyFnNoPtr>());
			}
			break;

		default:
			DoAssert(); //todo
		}

		x++;
	}

	m_vPropStringVals.resize(x);
	return ret;
}