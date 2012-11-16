// This is the main DLL file.
#include "stdafx.h"
#include "server.h"
#include <string>

using namespace System;
using namespace System::Reflection;

std::string GetModulePath();

bool CSourceSDKServer::DLLInit(CreateInterfaceFn appSystemFactory, CreateInterfaceFn physicsFactory, CreateInterfaceFn fileSystemFactory, CGlobalVars *pGlobals)
{

	//ICvar * pCvar = (ICvar*)appSystemFactory(CVAR_INTERFACE_VERSION, NULL);

	//if (!pCvar)
	//	return false;

	//ServerInitInterfaces^ cii = gcnew ServerInitInterfaces();
	//cii->ConsoleManager = gcnew ConsoleManager(pCvar);



	//auto workingDir = gcnew String(GetModulePath().c_str());

	//auto assembly = Assembly::LoadFile(workingDir + "SourceSDK.Core.dll");
	//auto type = assembly->GetType("SourceSDK.Core.Entry");

	//auto args = gcnew cli::array<Object^, 1>(1);
	//args[0] = cii;

	//type->InvokeMember(gcnew String("ServerInit"), BindingFlags::Public|BindingFlags::Static|BindingFlags::InvokeMethod, nullptr, nullptr, args);



//	// init each (seperated for ease of debugging)
//	if ( (engine = (IVEngineServer*)appSystemFactory(INTERFACEVERSION_VENGINESERVER, NULL)) == NULL )
//		return false;
//	if ( (g_pVoiceServer = (IVoiceServer*)appSystemFactory(INTERFACEVERSION_VOICESERVER, NULL)) == NULL )
//		return false;
//	if ( (networkstringtable = (INetworkStringTableContainer *)appSystemFactory(INTERFACENAME_NETWORKSTRINGTABLESERVER,NULL)) == NULL )
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
//	if ( (gameeventmanager = (IGameEventManager2 *)appSystemFactory(INTERFACEVERSION_GAMEEVENTSMANAGER2,NULL)) == NULL )
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
	return true;
}

bool CSourceSDKServer::LevelInit(char const *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame, bool background)
{
	return true;
}

void CSourceSDKServer::ServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
}

void CSourceSDKServer::GameFrame(bool simulating)
{
}

void CSourceSDKServer::PreClientUpdate(bool simulating)
{
}

void CSourceSDKServer::LevelShutdown()
{
}

void CSourceSDKServer::GameShutdown()
{
}

void CSourceSDKServer::DLLShutdown()
{
}

float CSourceSDKServer::GetTickInterval() const
{
	return 0.015f;
}

ServerClass* CSourceSDKServer::GetAllServerClasses()
{
	return nullptr;
}

const char* CSourceSDKServer::GetGameDescription()
{
	return "Source SDK C#";
}

void CSourceSDKServer::CreateNetworkStringTables()
{
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
	return nullptr;
}

void CSourceSDKServer::PostInit()
{
}

void CSourceSDKServer::Think(bool finalTick)
{
}

void CSourceSDKServer::PreSaveGameLoaded(char const *pSaveName, bool bCurrentlyInGame)
{
}

bool CSourceSDKServer::ShouldHideServer()
{
	return false;
}

void CSourceSDKServer::InvalidateMdlCache()
{
}

void CSourceSDKServer::OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue)
{
}
