#include "Stdafx.h"
#include <string>

#include "server.h"
#include "serverGameEnts.h"
#include "serverGameClients.h"


//0x0F9BE74C "HLTVDirector001"
//0x0F9BE700 "ServerGameTags001"
//0x0F9E28D8 "PluginHelpersCheck001"
	
extern "C" __declspec( dllexport ) void* CreateInterface(const char* szName, int *pReturnCode)
{
	if (std::string(szName) == INTERFACEVERSION_SERVERGAMEDLL)
		return new CSourceSDKServer();
	else if (std::string(szName) == INTERFACEVERSION_SERVERGAMEENTS)
		return new CSourceSDKServerGameEnts();
	else if (std::string(szName) == INTERFACEVERSION_SERVERGAMECLIENTS)
		return new CSourceSDKServerGameClients();

	return nullptr;
}