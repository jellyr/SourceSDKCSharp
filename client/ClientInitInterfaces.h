#pragma once

#include "CVarWrapper.h"

using namespace SourceSDK::Core::Interfaces::Client;
using namespace SourceSDK::Core::Interfaces::Shared;

ref class ClientInitInterfaces : public IClientInitInterfaces
{
public:
	virtual property NI_ConsoleManager^ ConsoleManager;
	virtual property NI_VEngineClient^ EngineClient;
	virtual property NI_VModelRender^ ModelRender;
	virtual property NI_VEfx^ Effects;
	virtual property NI_EngineTrace^ EngineTrace;
	virtual property NI_VRenderView^ RenderView;
	virtual property NI_VDebugOverlay^ DebugOverlay;
	virtual property NI_DataCache^ DataCache;
	virtual property NI_VModelInfoClient^ ModelInfoClient;
	virtual property NI_EngineVgui^ EngineVgui;
	virtual property NI_NetworkStringTable^ NetworkStringTable;
	virtual property NI_SpatialPartition^ SpatialPartition;
	virtual property NI_ShadowManager^ ShadowManager;
	virtual property NI_StaticPropManager^ StaticPropManager;
	virtual property NI_EngineSound^ EngineSound;
	virtual property NI_FileSystem^ FileSystem;
	virtual property NI_Random^ Random;
	virtual property NI_GameUiFunctions^ GameUiFunctions;
	virtual property NI_GameEventManager^ GameEventManager;
	virtual property NI_SoundEmitterBase^ SoundSmitterBase;
	virtual property NI_InputSystem^ InputSystem;

	virtual property IClientGameDll^ ClientGameDll;
};
