#pragma once

#include <string>
#include <vector>
#include <functional>
#include <gcroot.h>
#include "client_class.h"
using namespace SourceSDK::Core::Interfaces::Client;

class CClientClassWrapper : public ClientClass
{
public:
	CClientClassWrapper(IClientClass^ clientClass);

	IClientClass^ Get()
	{
		return m_ClientClass;
	}

protected:
	RecvTable* CreateRecvTable();

private:
	std::vector<std::string> m_vPropNames;
	std::vector<std::function<void (const CRecvProxyData *, void*, void*)>> m_vFunctions;

	std::function<IClientNetworkable* ()> m_CreateEvent;
	std::function<IClientNetworkable* (int, int)> m_CreateEntity;


	std::string m_szNetworkName;
	std::string m_szNetTableName;
	gcroot<IClientClass^> m_ClientClass;
};