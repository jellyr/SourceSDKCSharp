#pragma once
#include "eiface.h"

#include <gcroot.h>

using namespace SourceSDK::Core::Interfaces::Server;

class CSourceSDKServerGameClients : public IServerGameClients
{
public:
	void GetPlayerLimits( int& minplayers, int& maxplayers, int &defaultMaxPlayers ) const override;
	bool ClientConnect( edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen ) override;
		 
	void ClientActive( edict_t *pEntity, bool bLoadGame ) override;
	void ClientDisconnect( edict_t *pEntity ) override;
	void ClientPutInServer( edict_t *pEntity, char const *playername ) override;
	void ClientCommand( edict_t *pEntity, const CCommand &args ) override;
	void SetCommandClient( int index ) override;
		 
	void ClientSettingsChanged( edict_t *pEdict ) override;
	void ClientSetupVisibility( edict_t *pViewEntity, edict_t *pClient, unsigned char *pvs, int pvssize ) override;
		 
	float ProcessUsercmds( edict_t *player, bf_read *buf, int numcmds, int totalcmds, int dropped_packets, bool ignore, bool paused ) override;
	void PostClientMessagesSent() override;
	void ClientEarPosition( edict_t *pEntity, Vector *pEarOrigin ) override;
	int	 GetReplayDelay( edict_t *player, int& entity ) override;
	void GetBugReportInfo( char *buf, int buflen ) override;
	void NetworkIDValidated( const char *pszUserName, const char *pszNetworkID ) override;

	CPlayerState *GetPlayerState( edict_t *player ) override;

	gcroot<M_IServerGameClients^> m_pServerGameClients;
};