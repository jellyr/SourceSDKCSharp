#include "Stdafx.h"
#include <string>

#include "server.h"



//0x0F9BE74C "HLTVDirector001"
//0x0F9BE700 "ServerGameTags001"
//0x0F9E28D8 "PluginHelpersCheck001"

static CSourceSDKServer *g_pServerGameDll;

extern "C" __declspec( dllexport ) void* CreateInterface(const char* szName, int *pReturnCode)
{
	if (std::string(szName) == INTERFACEVERSION_SERVERGAMEDLL)
	{
		if (!g_pServerGameDll)
			g_pServerGameDll = new CSourceSDKServer();

		return g_pServerGameDll;
	}
	else
	{
		Assert(g_pServerGameDll);
		return g_pServerGameDll->CreateInterface(std::string(szName));
	}
}