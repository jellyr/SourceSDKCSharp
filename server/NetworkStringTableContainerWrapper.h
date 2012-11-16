#pragma once

#include "networkstringtabledefs.h"

using namespace SourceSDK::Core::Interfaces::Server;

ref class NetworkStringTableContainerWrapper : public NI_NetworkStringTableContainer
{
public:
	NetworkStringTableContainerWrapper(INetworkStringTableContainer *pNetworkStringTable);


	virtual MI_NetworkStringTable^ CreateStringTable(String^ tableName, int maxCount);

private:
	INetworkStringTableContainer *m_pNetworkStringTable;
};