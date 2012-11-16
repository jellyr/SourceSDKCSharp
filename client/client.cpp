#include "stdafx.h"
#include "client.h"
#include "EngineSprite.h"

#include <string>
#include "icvar.h"
#include "ClientInitInterfaces.h"
#include "ConsoleManager.h"
#include "ClientClassWrapper.h"

#include "shake.h"

using namespace System::Reflection;
using namespace System;

std::string GetModulePath();

ClientClass* g_pClientClassHead = nullptr;

int CSourceSDKClient::Init(CreateInterfaceFn appSystemFactory, CreateInterfaceFn physicsFactory, CGlobalVarsBase *pGlobals)
{
	ICvar * pCvar = (ICvar*)appSystemFactory(CVAR_INTERFACE_VERSION, NULL);

	if (!pCvar)
		return false;

	auto cii = gcnew ClientInitInterfaces();
	cii->ConsoleManager = gcnew SourceSDK::ConsoleManager(pCvar);


	ClientInterfaces = cii;


	auto workingDir = gcnew String(GetModulePath().c_str());

	auto assembly = Assembly::LoadFile(workingDir + "SourceSDK.Core.dll");
	auto type = assembly->GetType("SourceSDK.Core.Entry");

	auto args = gcnew cli::array<Object^, 1>(1);
	args[0] = cii;

	type->InvokeMember(gcnew String("ClientInit"), BindingFlags::Public|BindingFlags::Static|BindingFlags::InvokeMethod, nullptr, nullptr, args);


	//if ( (engine = (IVEngineClient *)appSystemFactory( VENGINE_CLIENT_INTERFACE_VERSION, NULL )) == NULL )
	//	return false;

	//if ( (modelrender = (IVModelRender *)appSystemFactory( VENGINE_HUDMODEL_INTERFACE_VERSION, NULL )) == NULL )
	//	return false;

	//if ( (effects = (IVEfx *)appSystemFactory( VENGINE_EFFECTS_INTERFACE_VERSION, NULL )) == NULL )
	//	return false;

	//if ( (enginetrace = (IEngineTrace *)appSystemFactory( INTERFACEVERSION_ENGINETRACE_CLIENT, NULL )) == NULL )
	//	return false;

	//if ( (render = (IVRenderView *)appSystemFactory( VENGINE_RENDERVIEW_INTERFACE_VERSION, NULL )) == NULL )
	//	return false;

	//if ( (debugoverlay = (IVDebugOverlay *)appSystemFactory( VDEBUG_OVERLAY_INTERFACE_VERSION, NULL )) == NULL )
	//	return false;

	//if ( (datacache = (IDataCache*)appSystemFactory(DATACACHE_INTERFACE_VERSION, NULL )) == NULL )
	//	return false;

	//if ( (modelinfo = (IVModelInfoClient *)appSystemFactory(VMODELINFO_CLIENT_INTERFACE_VERSION, NULL )) == NULL )
	//	return false;

	//if ( (enginevgui = (IEngineVGui *)appSystemFactory(VENGINE_VGUI_VERSION, NULL )) == NULL )
	//	return false;





	//if ( (networkstringtable = (INetworkStringTableContainer *)appSystemFactory(INTERFACENAME_NETWORKSTRINGTABLECLIENT,NULL)) == NULL )
	//	return false;

	//if ( (partition = (ISpatialPartition *)appSystemFactory(INTERFACEVERSION_SPATIALPARTITION, NULL)) == NULL )
	//	return false;

	//if ( (shadowmgr = (IShadowMgr *)appSystemFactory(ENGINE_SHADOWMGR_INTERFACE_VERSION, NULL)) == NULL )
	//	return false;

	//if ( (staticpropmgr = (IStaticPropMgrClient *)appSystemFactory(INTERFACEVERSION_STATICPROPMGR_CLIENT, NULL)) == NULL )
	//	return false;

	//if ( (enginesound = (IEngineSound *)appSystemFactory(IENGINESOUND_CLIENT_INTERFACE_VERSION, NULL)) == NULL )
	//	return false;

	//if ( (filesystem = (IFileSystem *)appSystemFactory(FILESYSTEM_INTERFACE_VERSION, NULL)) == NULL )
	//	return false;

	//if ( (random = (IUniformRandomStream *)appSystemFactory(VENGINE_CLIENT_RANDOM_INTERFACE_VERSION, NULL)) == NULL )
	//	return false;

	//if ( (gameuifuncs = (IGameUIFuncs * )appSystemFactory( VENGINE_GAMEUIFUNCS_VERSION, NULL )) == NULL )
	//	return false;

	//if ( (gameeventmanager = (IGameEventManager2 *)appSystemFactory(INTERFACEVERSION_GAMEEVENTSMANAGER2,NULL)) == NULL )
	//	return false;

	//if ( (soundemitterbase = (ISoundEmitterSystemBase *)appSystemFactory(SOUNDEMITTERSYSTEM_INTERFACE_VERSION, NULL)) == NULL )
	//	return false;

	//if ( (inputsystem = (IInputSystem *)appSystemFactory(INPUTSYSTEM_INTERFACE_VERSION, NULL)) == NULL )
	//	return false;

	//if ( (cvar = ( ICvar * )pFactoryList[i]( CVAR_INTERFACE_VERSION, NULL ) == NULL )
	//	return false;

	//if ( (g_pProcessUtils = ( IProcessUtils * )pFactoryList[i]( PROCESS_UTILS_INTERFACE_VERSION, NULL )) == NULL )
	//	return false;


	return true;
}

void CSourceSDKClient::PostInit()
{
	ClientInterfaces->ClientGameDll->PostInit();
}

void CSourceSDKClient::Shutdown()
{
	ClientInterfaces->ClientGameDll->Shutdown();
}


void CSourceSDKClient::LevelInitPreEntity(const char *pMapName)
{
	ClientInterfaces->ClientGameDll->LevelInitPreEntity(gcnew String(pMapName));
}

void CSourceSDKClient::LevelInitPostEntity()
{
	ClientInterfaces->ClientGameDll->LevelInitPostEntity();
}

void CSourceSDKClient::LevelShutdown()
{
	ClientInterfaces->ClientGameDll->LevelShutdown();
}


ClientClass* CSourceSDKClient::GetAllClasses()
{
	if (g_pClientClassHead)
		return g_pClientClassHead;

	auto classes = ClientInterfaces->ClientGameDll->GetAllClasses();

	if (classes == nullptr)
		return nullptr;

	for each (auto i in classes)
		new CClientClassWrapper(i);

	return g_pClientClassHead;
}


int CSourceSDKClient::HudVidInit()
{
	return ClientInterfaces->ClientGameDll->HudVidinit();
}

void CSourceSDKClient::HudProcessInput(bool bActive)
{
	ClientInterfaces->ClientGameDll->HudProcessInput(bActive);
}

void CSourceSDKClient::HudUpdate(bool bActive)
{
	ClientInterfaces->ClientGameDll->HudUpdate(bActive);
}

void CSourceSDKClient::HudReset()
{
	ClientInterfaces->ClientGameDll->HudReset();
}

void CSourceSDKClient::HudText(const char * message)
{
	ClientInterfaces->ClientGameDll->HudText(gcnew String(message));
}


// Mouse Input Interfaces
void CSourceSDKClient::IN_ActivateMouse()
{
	ClientInterfaces->ClientGameDll->OnActiveMouse();
}

void CSourceSDKClient::IN_DeactivateMouse()
{
	ClientInterfaces->ClientGameDll->OnDeactiveMouse();
}

void CSourceSDKClient::IN_Accumulate()
{
	ClientInterfaces->ClientGameDll->OnAccumlate();
}

void CSourceSDKClient::IN_ClearStates()
{
	if (ClientInterfaces)
		ClientInterfaces->ClientGameDll->OnClearStates();
}

bool CSourceSDKClient::IN_IsKeyDown(const char *name, bool& isdown)
{
	return ClientInterfaces->ClientGameDll->IsKeyDown(gcnew String(name), isdown);
}

// Raw signal
int CSourceSDKClient::IN_KeyEvent(int eventcode, ButtonCode_t keynum, const char *pszCurrentBinding)
{
	return ClientInterfaces->ClientGameDll->OnKeyEvent(eventcode, (ButtonCode)keynum, gcnew String(pszCurrentBinding));
}

void CSourceSDKClient::IN_SetSampleTime(float frametime)
{
	ClientInterfaces->ClientGameDll->SetSampleTime(frametime);
}

// Create movement command
void CSourceSDKClient::CreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	ClientInterfaces->ClientGameDll->CreateMove(sequence_number, input_sample_frametime, active);
}

void CSourceSDKClient::ExtraMouseSample(float frametime, bool active)
{
	ClientInterfaces->ClientGameDll->ExtraMouseSample(frametime, active);
}

bool CSourceSDKClient::WriteUsercmdDeltaToBuffer(bf_write *buf, int from, int to, bool isnewcommand)
{
	cli::array<byte,1>^ outBuff = nullptr;
	ClientInterfaces->ClientGameDll->WriteUserCmdDeltaToBuffer(outBuff, from, to, isnewcommand);

	cli::pin_ptr<byte> byteArry = &outBuff[0];
	buf->WriteBytes(byteArry, outBuff->Length);

	return false;
}

void CSourceSDKClient::EncodeUserCmdToBuffer(bf_write& buf, int slot)
{
	cli::array<byte,1>^ outBuff = nullptr;
	ClientInterfaces->ClientGameDll->EncodeUserCmdToBuffer(outBuff, slot);

	cli::pin_ptr<byte> byteArry = &outBuff[0];

	buf.WriteLong(outBuff->Length);
	buf.WriteBytes(byteArry, outBuff->Length);
}

void CSourceSDKClient::DecodeUserCmdFromBuffer(bf_read& buf, int slot)
{
	int count = buf.ReadLong();
	auto outBuff = gcnew cli::array<byte,1>(count);

	cli::pin_ptr<byte> byteArry = &outBuff[0];
	buf.ReadBytes(byteArry, count);

	ClientInterfaces->ClientGameDll->DecodeUserCmdFromBuffer(outBuff, slot);
}

void CSourceSDKClient::View_Render(vrect_t *rect)
{
	std::vector<vrect_t*> vList;

	while (rect)
	{
		vList.push_back(rect);
		rect = rect->pnext;
	}

	auto items = gcnew cli::array<M_VRect^, 1>(vList.size());

	for (size_t x=0; x<vList.size(); x++)
	{
		items[x] = gcnew M_VRect();
		items[x]->X = vList[x]->x;
		items[x]->Y = vList[x]->y;
		items[x]->Width = vList[x]->width;
		items[x]->Height = vList[x]->height;
	}

	ClientInterfaces->ClientGameDll->ViewRender(items);
}

void CSourceSDKClient::RenderView(const CViewSetup &view, int nClearFlags, int whatToDraw)
{
	Assert(false); //todo
	//M_ViewSetup^ vs = gcnew M_ViewSetup();
	//
	//ClientInterfaces->ClientGameDll->RenderView(vs, nClearFlags, whatToDraw);
}

void CSourceSDKClient::View_Fade(ScreenFade_t *pSF)
{
	auto sf = gcnew M_ScreenFade();
	sf->Duration = pSF->duration;
	sf->HoldTime = pSF->holdTime;
	sf->FadeFlags = pSF->fadeFlags;
	sf->Color = System::Drawing::Color::FromArgb(pSF->a, pSF->r, pSF->g, pSF->b);

	ClientInterfaces->ClientGameDll->ViewFade(sf);
}

	
void CSourceSDKClient::SetCrosshairAngle(const QAngle& angle)
{
	auto ang = gcnew M_QAngle();

	ang->X = angle.x;
	ang->Y = angle.y;
	ang->Z = angle.z;

	ClientInterfaces->ClientGameDll->SetCrosshairAngle(ang);
}


void CSourceSDKClient::InitSprite(CEngineSprite *pSprite, const char *loadname)
{
	if (pSprite)
		pSprite->Init(loadname);
}

void CSourceSDKClient::ShutdownSprite(CEngineSprite *pSprite)
{
	if (pSprite)
		pSprite->Shutdown();
}


int CSourceSDKClient::GetSpriteSize() const
{
	return sizeof(CEngineSprite);
}


void CSourceSDKClient::VoiceStatus(int entindex, qboolean bTalking)
{
	ClientInterfaces->ClientGameDll->VoiceStatus(entindex, bTalking?true:false);
}


void CSourceSDKClient::InstallStringTableCallback(const char *tableName)
{
	ClientInterfaces->ClientGameDll->InstallStringTableCallback(gcnew String(tableName));
}


void CSourceSDKClient::FrameStageNotify(ClientFrameStage_t curStage)
{
	ClientInterfaces->ClientGameDll->FrameStageNotify((ClientFrameStage)curStage);
}


bool CSourceSDKClient::DispatchUserMessage(int msg_type, bf_read &msg_data)
{
	Assert(false); //todo
	//ClientInterfaces->ClientGameDll->DispatchUserMessage();
	return false;
}


// Save/restore system hooks
CSaveRestoreData* CSourceSDKClient::SaveInit(int size)
{
	return nullptr;
}

void CSourceSDKClient::SaveWriteFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int)
{
}

void CSourceSDKClient::SaveReadFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int)
{
}

void CSourceSDKClient::PreSave(CSaveRestoreData *)
{
}

void CSourceSDKClient::Save(CSaveRestoreData *)
{
}

void CSourceSDKClient::WriteSaveHeaders(CSaveRestoreData *)
{
}

void CSourceSDKClient::ReadRestoreHeaders( CSaveRestoreData *)
{
}

void CSourceSDKClient::Restore(CSaveRestoreData *, bool )
{
}

void CSourceSDKClient::DispatchOnRestore()
{
}

void CSourceSDKClient::WriteSaveGameScreenshot(const char *pFilename)
{
}


// Given a list of "S(wavname) S(wavname2)" tokens, look up the localized text and emit
//  the appropriate close caption if running with closecaption = 1
void CSourceSDKClient::EmitSentenceCloseCaption(char const *tokenstream)
{
}

void CSourceSDKClient::EmitCloseCaption(char const *captionname, float duration)
{
}


CStandardRecvProxies* CSourceSDKClient::GetStandardRecvProxies()
{
	auto proxies = ClientInterfaces->ClientGameDll->GetStandardRecvProxies();

	return nullptr;
}


bool CSourceSDKClient::CanRecordDemo(char *errorMsg, int length) const
{
	return false;
}


// save game screenshot writing
void CSourceSDKClient::WriteSaveGameScreenshotOfSize(const char *pFilename, int width, int height)
{
}


// Gets the location of the player viewpoint
bool CSourceSDKClient::GetPlayerView(CViewSetup &playerView)
{
	Assert(false); //todo
	//auto pv = gcnew M_ViewSetup();
	//return ClientInterfaces->ClientGameDll->GetPlayerView(pv);
	return false;
}


// Matchmaking
void CSourceSDKClient::SetupGameProperties(CUtlVector< XUSER_CONTEXT > &contexts, CUtlVector< XUSER_PROPERTY > &properties)
{
}

uint CSourceSDKClient::GetPresenceID(const char *pIDName)
{
	return 0;
}

const char* CSourceSDKClient::GetPropertyIdString(const uint id)
{
	return "";
}

void CSourceSDKClient::GetPropertyDisplayString(uint id, uint value, char *pOutput, int nBytes)
{
}

void CSourceSDKClient::StartStatsReporting(HANDLE handle, bool bArbitrated)
{
}

void CSourceSDKClient::InvalidateMdlCache()
{
}
