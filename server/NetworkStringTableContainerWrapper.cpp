#include "stdafx.h"
#include "NetworkStringTableContainerWrapper.h"

#include "NetworkStringTableWrapper.h"

NetworkStringTableContainerWrapper::NetworkStringTableContainerWrapper(INetworkStringTableContainer *pNetworkStringTable)
{
	m_pNetworkStringTable = pNetworkStringTable;
}

MI_NetworkStringTable^ NetworkStringTableContainerWrapper::CreateStringTable(String^ tableName, int maxCount)
{
	std::string szTableName = marshal_as<std::string>(tableName);
	return gcnew NetworkStringTableWrapper(m_pNetworkStringTable->CreateStringTable(szTableName.c_str(), maxCount));
}