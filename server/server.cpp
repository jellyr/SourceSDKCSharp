// This is the main DLL file.
#include "stdafx.h"
#include <msclr\marshal_cppstd.h>

#include "server.h"
#include <string>
#include <vector>
#include <algorithm>

#include "icvar.h"
#include "ConsoleManager.h"
#include "ServerInitInterfaces.h"
#include "EdictWrapper.h"
#include "ServerClassWrapper.h"
#include "VEngineServerWrapper.h"
#include "NetworkStringTableContainerWrapper.h"
#include "GlobalVarsWrapper.h"

#include "igameevents.h"

// Holds global variables shared between engine and game.
CGlobalVars *gpGlobals;


ServerClass *g_pServerClassHead = nullptr;

using namespace System;
using namespace System::Reflection;
using namespace msclr::interop;

std::string GetModulePath();

class CMockGameEventListener2 : public IGameEventListener2
{
public:
	virtual void FireGameEvent(IGameEvent *event) override
	{
	}
};

bool CSourceSDKServer::DLLInit(CreateInterfaceFn appSystemFactory, CreateInterfaceFn physicsFactory, CreateInterfaceFn fileSystemFactory, CGlobalVars *pGlobals)
{
	gpGlobals = pGlobals;

	auto pCvar = (ICvar*)appSystemFactory(CVAR_INTERFACE_VERSION, NULL);

	if (!pCvar)
		return false;

	auto pEngine = (IVEngineServer*)appSystemFactory(INTERFACEVERSION_VENGINESERVER, NULL);

	if (!pEngine)
		return false;

	auto pNetworkStringTable = (INetworkStringTableContainer *)appSystemFactory(INTERFACENAME_NETWORKSTRINGTABLESERVER,NULL);

	if (!pNetworkStringTable)
		return false;

	auto gameeventmanager = (IGameEventManager2*)appSystemFactory(INTERFACEVERSION_GAMEEVENTSMANAGER2,NULL);

	if (!gameeventmanager)
		return false;

	//If we dont do this engine.dll will crash
	gameeventmanager->AddListener(new CMockGameEventListener2(), "player_connect", true);


	ServerInitInterfaces^ sii = gcnew ServerInitInterfaces();
	sii->ConsoleManager = gcnew SourceSDK::ConsoleManager(pCvar);
	sii->EngineServer = gcnew VEngineServerWrapper(pEngine);
	sii->NetworkStringTableContainer = gcnew NetworkStringTableContainerWrapper(pNetworkStringTable);
	sii->GlobalVars = gcnew GlobalVarsWrapper();

	ServerInterfaces = sii;

	auto workingDir = gcnew String(GetModulePath().c_str());

	auto assembly = Assembly::LoadFile(workingDir + "SourceSDK.Core.dll");
	auto type = assembly->GetType("SourceSDK.Core.Entry");

	auto args = gcnew cli::array<Object^, 1>(1);
	args[0] = sii;

	type->InvokeMember(gcnew String("ServerInit"), BindingFlags::Public|BindingFlags::Static|BindingFlags::InvokeMethod, nullptr, nullptr, args);





//	// init each (seperated for ease of debugging)
//	if ( (g_pVoiceServer = (IVoiceServer*)appSystemFactory(INTERFACEVERSION_VOICESERVER, NULL)) == NULL )
//		return false;
//	if ( (staticpropmgr = (IStaticPropMgrServer *)appSystemFactory(INTERFACEVERSION_STATICPROPMGR_SERVER,NULL)) == NULL )
//		return false;
//	if ( (random = (IUniformRandomStream *)appSystemFactory(VENGINE_SERVER_RANDOM_INTERFACE_VERSION, NULL)) == NULL )
//		return false;
//	if ( (enginesound = (IEngineSound *)appSystemFactory(IENGINESOUND_SERVER_INTERFACE_VERSION, NULL)) == NULL )
//		return false;
//	if ( (partition = (ISpatialPartition *)appSystemFactory(INTERFACEVERSION_SPATIALPARTITION, NULL)) == NULL )
//		return false;
//	if ( (modelinfo = (IVModelInfo *)appSystemFactory(VMODELINFO_SERVER_INTERFACE_VERSION, NULL)) == NULL )
//		return false;
//	if ( (enginetrace = (IEngineTrace *)appSystemFactory(INTERFACEVERSION_ENGINETRACE_SERVER,NULL)) == NULL )
//		return false;
//	if ( (filesystem = (IFileSystem *)fileSystemFactory(FILESYSTEM_INTERFACE_VERSION,NULL)) == NULL )
//		return false;

//	if ( (datacache = (IDataCache*)appSystemFactory(DATACACHE_INTERFACE_VERSION, NULL )) == NULL )
//		return false;
//	if ( (soundemitterbase = (ISoundEmitterSystemBase *)appSystemFactory(SOUNDEMITTERSYSTEM_INTERFACE_VERSION, NULL)) == NULL )
//		return false;
//#ifndef _XBOX
//	if ( (gamestatsuploader = (IUploadGameStats *)appSystemFactory( INTERFACEVERSION_UPLOADGAMESTATS, NULL )) == NULL )
//		return false;
//#endif
//	if ( !mdlcache )
//		return false;
//	if ( (serverpluginhelpers = (IServerPluginHelpers *)appSystemFactory(INTERFACEVERSION_ISERVERPLUGINHELPERS, NULL)) == NULL )
//		return false;
//	if ( (scenefilecache = (ISceneFileCache *)appSystemFactory( SCENE_FILE_CACHE_INTERFACE_VERSION, NULL )) == NULL )
//		return false;


	return true;
}

bool CSourceSDKServer::GameInit()
{
	return ServerInterfaces->ServerGameDll->GameInit();
}

bool CSourceSDKServer::LevelInit(char const *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame, bool background)
{
	if ( loadGame )
	{
		if ( pOldLevel )
		{
			gpGlobals->eLoadType = MapLoad_Transition;
		}
		else
		{
			gpGlobals->eLoadType = MapLoad_LoadGame;
		}
	}
	else
	{
		if ( background )
		{
			gpGlobals->eLoadType = MapLoad_Background;
		}
		else
		{
			gpGlobals->eLoadType = MapLoad_NewGame;
		}
	}

	return ServerInterfaces->ServerGameDll->LevelInit(gcnew String(pMapName), gcnew String(pMapEntities), gcnew String(pOldLevel), gcnew String(pLandmarkName), loadGame, background);
}

void CSourceSDKServer::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	auto edicts = gcnew cli::array<IEdict^, 1>(edictCount);
	
	for (int x=0; x<edictCount; ++x)
		edicts[x] = gcnew EdictWrapper(pEdictList[x]);

	ServerInterfaces->ServerGameDll->ServerActivate(edicts, clientMax);
}

void CSourceSDKServer::GameFrame(bool simulating)
{
	ServerInterfaces->ServerGameDll->GameFrame(simulating);
}

void CSourceSDKServer::PreClientUpdate(bool simulating)
{
	ServerInterfaces->ServerGameDll->PreClientUpdate(simulating);
}

void CSourceSDKServer::LevelShutdown()
{
	ServerInterfaces->ServerGameDll->LevelShutdown();
}

void CSourceSDKServer::GameShutdown()
{
	ServerInterfaces->ServerGameDll->GameShutdown();
}

void CSourceSDKServer::DLLShutdown()
{
	ServerInterfaces->ServerGameDll->DllShutDown();
}

float CSourceSDKServer::GetTickInterval() const
{
	return ServerInterfaces->ServerGameDll->GetTickInterval();
}

ServerClass* CSourceSDKServer::GetAllServerClasses()
{
	if (!ServerInterfaces)
		return nullptr;

	if (g_pServerClassHead)
		return g_pServerClassHead;

	auto classes = ServerInterfaces->ServerGameDll->GetAllServerClasses();

	if (classes == nullptr)
		return nullptr;

	std::vector<CServerClassWrapper*> vList;

	for each (auto i in classes)
	{
		//reset this to null so we can do post create sort
		g_pServerClassHead = nullptr;
		vList.push_back(new CServerClassWrapper(i));
	}

	std::sort(vList.begin(), vList.end(), [](CServerClassWrapper* a, CServerClassWrapper* b) -> bool
	{
		return a->GetNameAsString().compare(b->GetNameAsString()) >= 0;
	});

	for (size_t x=0; x<vList.size(); x++)
	{
		if (x == 0)
		{
			g_pServerClassHead = vList[x];
			g_pServerClassHead->m_pNext = nullptr;
		}
		else
		{
			vList[x]->m_pNext = g_pServerClassHead;
			g_pServerClassHead = vList[x];
		}		
	}

	return g_pServerClassHead;
}

const char* CSourceSDKServer::GetGameDescription()
{
	if (!ServerInterfaces)
		return "Source SDK C# Pre Init";

	m_szGameDesc = marshal_as<std::string>(ServerInterfaces->ServerGameDll->GetGameDescription());
	return m_szGameDesc.c_str();
}

void CSourceSDKServer::CreateNetworkStringTables()
{
	ServerInterfaces->ServerGameDll->CreateNetworkStringTables();
}

CSaveRestoreData* CSourceSDKServer::SaveInit(int size)
{
	return nullptr;
}

void CSourceSDKServer::SaveWriteFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int)
{
}

void CSourceSDKServer::SaveReadFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int)
{
}

void CSourceSDKServer::SaveGlobalState(CSaveRestoreData *)
{
}

void CSourceSDKServer::RestoreGlobalState(CSaveRestoreData *)
{
}

void CSourceSDKServer::PreSave(CSaveRestoreData *)
{
}

void CSourceSDKServer::Save(CSaveRestoreData *)
{
}

void CSourceSDKServer::GetSaveComment(char *comment, int maxlength, float flMinutes, float flSeconds, bool bNoTime)
{
}

void CSourceSDKServer::WriteSaveHeaders(CSaveRestoreData *)
{
}

void CSourceSDKServer::ReadRestoreHeaders(CSaveRestoreData *)
{
}

void CSourceSDKServer::Restore(CSaveRestoreData *, bool)
{
}

bool CSourceSDKServer::IsRestoring()
{
	return false;
}

int CSourceSDKServer::CreateEntityTransitionList(CSaveRestoreData *, int)
{
	return 0;
}

void CSourceSDKServer::BuildAdjacentMapList()
{
}

bool CSourceSDKServer::GetUserMessageInfo(int msg_type, char *name, int maxnamelength, int& size)
{
	return false;
}

CStandardSendProxies* CSourceSDKServer::GetStandardSendProxies()
{
	return &g_StandardSendProxies;
}

void CSourceSDKServer::PostInit()
{
	ServerInterfaces->ServerGameDll->PostInit();
}

void CSourceSDKServer::Think(bool finalTick)
{
	ServerInterfaces->ServerGameDll->Think(finalTick);
}

void CSourceSDKServer::PreSaveGameLoaded(char const *pSaveName, bool bCurrentlyInGame)
{
}

bool CSourceSDKServer::ShouldHideServer()
{
	return ServerInterfaces->ServerGameDll->ShouldHideServer();
}

void CSourceSDKServer::InvalidateMdlCache()
{
	ServerInterfaces->ServerGameDll->InvalidateMdlCache();
}

void CSourceSDKServer::OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue)
{
}
