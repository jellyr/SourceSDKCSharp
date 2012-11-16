#include "Stdafx.h"
#include "client.h"
#include "prediction.h"
#include "clientEntityList.h"
#include "centerPrint.h"
#include "clientLeafSystem.h"
#include "gameClientExports.h"

#include <string>


//"ClientRenderTargets001"				render targets
//"VClientDllSharedAppSystems001"		shared dll's
//"VProcessUtils001"					process utils
//"NetworkSystemVersion001"
//"VP4001"
//"VMDLLIB001"							model stripping
//"QueuedLoaderVersion001"				map loading
//"VDmeMakeFileUtils001"
//"RunGameEngine005"


extern "C" __declspec( dllexport ) void* CreateInterface(const char* szName, int *pReturnCode)
{

	if (std::string(szName) == CLIENT_DLL_INTERFACE_VERSION)
		return new CSourceSDKClient();
	else if (std::string(szName) == VCLIENT_PREDICTION_INTERFACE_VERSION)
		return new CSourceSDKPrediction();
	else if (std::string(szName) == VCLIENTENTITYLIST_INTERFACE_VERSION)
		return new CSourceSDKClientEntityList();
	else if (std::string(szName) == VCENTERPRINT_INTERFACE_VERSION)
		return new CSourceSDKCenterPrint();
	else if (std::string(szName) == CLIENTLEAFSYSTEM_INTERFACE_VERSION)
		return new CSourceSDKClientLeafSystem();
	else if (std::string(szName) == GAMECLIENTEXPORTS_INTERFACE_VERSION)
		return new CSourceSDKGameClientExports();

	return nullptr;
}