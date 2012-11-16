#pragma once

#include <string>
#include <vector>
#include <functional>
#include <gcroot.h>
#include "server_class.h"

using namespace SourceSDK::Core::Interfaces::Server;

class CServerClassWrapper : public ServerClass
{
public:
	CServerClassWrapper(IServerClass^ serverClass);

	std::string GetNameAsString()
	{
		return m_szNetworkName;
	}

protected:
	SendTable* CreateSendTable();

private:
	std::string m_szNetworkName;
	std::vector<std::string> m_vPropNames;
	std::vector<std::string> m_vPropStringVals;
	std::vector<std::function<void (const SendProp *, const void *, const void *, DVariant *, int, int)>> m_vFunctions;

	gcroot<IServerClass^> m_pServerClass;
};