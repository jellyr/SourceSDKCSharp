#pragma once

#include "networkstringtabledefs.h"

using namespace SourceSDK::Core::Interfaces::Server;

ref class NetworkStringTableWrapper : public MI_NetworkStringTable
{
public:
	NetworkStringTableWrapper(INetworkStringTable* pNetworkStringTable)
	{
		m_pNetworkStringTable = pNetworkStringTable;
	}

private:
	INetworkStringTable* m_pNetworkStringTable;
};