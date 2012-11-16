#pragma once

using namespace SourceSDK::Core::Interfaces::Server;
using namespace SourceSDK::Core::Interfaces::Shared;

ref class ServerInitInterfaces : public IServerInitInterfaces
{
public:
	virtual property NI_ConsoleManager^ ConsoleManager;
	virtual property NI_VEngineServer^ EngineServer;
	virtual property NI_VoiceServer^ VoiceServer;
	virtual property NI_NetworkStringTableContainer^ NetworkStringTableContainer;
	virtual property NI_StaticPropManagerServer^ StaticPropManagerServer;
	virtual property NI_EngineSound^ EngineSound;
	virtual property NI_FileSystem^ FileSystem;
	virtual property NI_Random^ Random;
	virtual property NI_SpatialPartition^ SpatialPartition;
	virtual property NI_EngineTrace^ EngineTrace;
	virtual property NI_GameEventManager2^ GameEventManager2;
	virtual property NI_DataCache^ DataCache;
	virtual property NI_SoundEmitterSystemBase^ SoundEmitterSystemBase;
	virtual property NI_ServerPluginHelpers^ ServerPluginHelpers;
	virtual property NI_ScenceFileCache^ SceneFileCache;

	virtual property NI_GlobalVars^ GlobalVars;

	virtual property M_IServerGameDll^ ServerGameDll;
	virtual property M_IServerGameClients^ ServerGameClients;
	virtual property M_IServerGameEnts^ ServerGameEnts;
};