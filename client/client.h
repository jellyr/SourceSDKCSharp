// client.h
#pragma once


typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);


#include <gcroot.h>
#include "xboxstub.h"
#include "cdll_int.h"

class ICvar;


class CSourceSDKClient : public IBaseClientDLL
{
public:
	int Init(CreateInterfaceFn appSystemFactory, CreateInterfaceFn physicsFactory, CGlobalVarsBase *pGlobals) override;

	void PostInit() override;
	void Shutdown() override;

	void LevelInitPreEntity(const char *pMapName) override;
	void LevelInitPostEntity() override;
	void LevelShutdown() override;

	ClientClass	*GetAllClasses() override;

	int HudVidInit() override;
	void HudProcessInput(bool bActive) override;
	void HudUpdate(bool bActive) override;
	void HudReset() override;
	void HudText(const char * message) override;

	// Mouse Input Interfaces
	void IN_ActivateMouse() override;
	void IN_DeactivateMouse() override;
	void IN_Accumulate() override;
	void IN_ClearStates() override;
	bool IN_IsKeyDown(const char *name, bool& isdown) override;
	// Raw signal
	int IN_KeyEvent(int eventcode, ButtonCode_t keynum, const char *pszCurrentBinding) override;
	void IN_SetSampleTime(float frametime) override;
	// Create movement command
	void CreateMove(int sequence_number, float input_sample_frametime, bool active) override;
	void ExtraMouseSample(float frametime, bool active) override;
	bool WriteUsercmdDeltaToBuffer(bf_write *buf, int from, int to, bool isnewcommand) override;	
	void EncodeUserCmdToBuffer(bf_write& buf, int slot) override;
	void DecodeUserCmdFromBuffer(bf_read& buf, int slot) override;


	void View_Render(vrect_t *rect) override;
	void RenderView(const CViewSetup &view, int nClearFlags, int whatToDraw) override;
	void View_Fade(ScreenFade_t *pSF) override;
	
	void SetCrosshairAngle(const QAngle& angle) override;

	void InitSprite(CEngineSprite *pSprite, const char *loadname) override;
	void ShutdownSprite(CEngineSprite *pSprite) override;

	int GetSpriteSize() const override;

	void VoiceStatus(int entindex, qboolean bTalking) override;

	void InstallStringTableCallback(const char *tableName) override;

	void FrameStageNotify(ClientFrameStage_t curStage) override;

	bool DispatchUserMessage(int msg_type, bf_read &msg_data) override;

	// Save/restore system hooks
	CSaveRestoreData *SaveInit(int size) override;
	void SaveWriteFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int) override;
	void SaveReadFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int) override;
	void PreSave(CSaveRestoreData *) override;
	void Save(CSaveRestoreData *) override;
	void WriteSaveHeaders(CSaveRestoreData *) override;
	void ReadRestoreHeaders( CSaveRestoreData *) override;
	void Restore(CSaveRestoreData *, bool ) override;
	void DispatchOnRestore() override;
	void WriteSaveGameScreenshot(const char *pFilename) override;

	// Given a list of "S(wavname) S(wavname2)" tokens, look up the localized text and emit
	//  the appropriate close caption if running with closecaption = 1
	void EmitSentenceCloseCaption(char const *tokenstream) override;
	void EmitCloseCaption(char const *captionname, float duration) override;

	CStandardRecvProxies* GetStandardRecvProxies() override;

	bool CanRecordDemo(char *errorMsg, int length) const override;

	// save game screenshot writing
	void WriteSaveGameScreenshotOfSize(const char *pFilename, int width, int height) override;

	// Gets the location of the player viewpoint
	bool GetPlayerView(CViewSetup &playerView) override;

	// Matchmaking
	void SetupGameProperties(CUtlVector< XUSER_CONTEXT > &contexts, CUtlVector< XUSER_PROPERTY > &properties) override;
	uint GetPresenceID(const char *pIDName) override;
	const char *GetPropertyIdString(const uint id) override;
	void GetPropertyDisplayString(uint id, uint value, char *pOutput, int nBytes) override;
	void StartStatsReporting(HANDLE handle, bool bArbitrated) override;

	void InvalidateMdlCache() override;

	gcroot<SourceSDK::Core::Interfaces::Client::IClientInitInterfaces^> ClientInterfaces;
};
