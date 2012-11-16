// server.h

#pragma once

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
#include "eiface.h"

#include <gcroot.h>

//IPlayerInfoManager
//IBotManager
//IEffects
//IServerGameClients
//IHLTVDirector
//IParticleSystemQuery
//IPluginHelpersCheck
//IServerTools
//IGameMovement



class CSourceSDKServer : public IServerGameDLL
{
public:
	// Initialize the game (one-time call when the DLL is first loaded )
	// Return false if there is an error during startup.
	bool DLLInit(CreateInterfaceFn engineFactory, CreateInterfaceFn physicsFactory, CreateInterfaceFn fileSystemFactory, CGlobalVars *pGlobals) override;

	// This is called when a new game is started. (restart, map)
	bool GameInit() override;

	// Called any time a new level is started (after GameInit() also on level transitions within a game)
	bool LevelInit(char const *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame, bool background) override;

	// The server is about to activate
	void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax) override;

	// The server should run physics/think on all edicts
	void GameFrame(bool simulating) override;

	// Called once per simulation frame on the final tick
	void PreClientUpdate(bool simulating) override;

	// Called when a level is shutdown (including changing levels)
	void LevelShutdown() override;
	// This is called when a game ends (server disconnect, death, restart, load)
	// NOT on level transitions within a game
	void GameShutdown() override;

	// Called once during DLL shutdown
	void DLLShutdown() override;

	// Get the simulation interval (must be compiled with identical values into both client and game .dll for MOD!!!)
	// Right now this is only requested at server startup time so it can't be changed on the fly, etc.
	float GetTickInterval() const override;

	// Give the list of datatable classes to the engine.  The engine matches class names from here with
	//  edict_t::classname to figure out how to encode a class's data for networking
	ServerClass* GetAllServerClasses() override;

	// Returns string describing current .dll.  e.g., TeamFortress 2, Half-Life 2.  
	//  Hey, it's more descriptive than just the name of the game directory
	const char* GetGameDescription() override;  
	
	// Let the game .dll allocate it's own network/shared string tables
	void CreateNetworkStringTables() override;
	
	// Save/restore system hooks
	CSaveRestoreData  *SaveInit(int size) override;
	void SaveWriteFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int) override;
	void SaveReadFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int) override;
	void SaveGlobalState(CSaveRestoreData *) override;
	void RestoreGlobalState(CSaveRestoreData *) override;
	void PreSave(CSaveRestoreData *) override;
	void Save(CSaveRestoreData *) override;
	void GetSaveComment(char *comment, int maxlength, float flMinutes, float flSeconds, bool bNoTime = false) override;
	void WriteSaveHeaders(CSaveRestoreData *) override;
	void ReadRestoreHeaders(CSaveRestoreData *) override;
	void Restore(CSaveRestoreData *, bool) override;
	bool IsRestoring() override;

	// Returns the number of entities moved across the transition
	int CreateEntityTransitionList(CSaveRestoreData *, int) override;
	// Build the list of maps adjacent to the current map
	void BuildAdjacentMapList() override;

	// Retrieve info needed for parsing the specified user message
	bool GetUserMessageInfo(int msg_type, char *name, int maxnamelength, int& size) override;

	// Hand over the StandardSendProxies in the game DLL's module.
	CStandardSendProxies* GetStandardSendProxies() override;

	// Called once during startup, after the game .dll has been loaded and after the client .dll has also been loaded
	void PostInit() override;
	// Called once per frame even when no level is loaded...
	void Think(bool finalTick) override;

#ifdef _XBOX
	void GetTitleName(const char *pMapName, char* pTitleBuff, int titleBuffSize) override;
#endif

	void PreSaveGameLoaded(char const *pSaveName, bool bCurrentlyInGame) override;

	// Returns true if the game DLL wants the server not to be made public.
	// Used by commentary system to hide multiplayer commentary servers from the master.
	bool ShouldHideServer() override;

	void InvalidateMdlCache() override;

	// * This function is new with version 6 of the interface.
	//
	// This is called when a query from IServerPluginHelpers::StartQueryCvarValue is finished.
	// iCookie is the value returned by IServerPluginHelpers::StartQueryCvarValue.
	// Added with version 2 of the interface.
	void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue) override;


	gcroot<SourceSDK::Core::Interfaces::Server::IServerInitInterfaces^> ServerInterfaces;

private:
	std::string m_szGameDesc;
};