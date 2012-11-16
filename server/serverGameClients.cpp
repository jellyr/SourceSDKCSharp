#include "Stdafx.h"
#include "serverGameClients.h"



void CSourceSDKServerGameClients::GetPlayerLimits( int& minplayers, int& maxplayers, int &defaultMaxPlayers ) const
{
}

bool CSourceSDKServerGameClients::ClientConnect( edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen )
{
	return true;
}
		 
void CSourceSDKServerGameClients::ClientActive( edict_t *pEntity, bool bLoadGame )
{
}

void CSourceSDKServerGameClients::ClientDisconnect( edict_t *pEntity )
{
}

void CSourceSDKServerGameClients::ClientPutInServer( edict_t *pEntity, char const *playername )
{
}

void CSourceSDKServerGameClients::ClientCommand( edict_t *pEntity, const CCommand &args )
{
}

void CSourceSDKServerGameClients::SetCommandClient( int index )
{
}

		 
void CSourceSDKServerGameClients::ClientSettingsChanged( edict_t *pEdict )
{
}

void CSourceSDKServerGameClients::ClientSetupVisibility( edict_t *pViewEntity, edict_t *pClient, unsigned char *pvs, int pvssize )
{
}
		 
float CSourceSDKServerGameClients::ProcessUsercmds( edict_t *player, bf_read *buf, int numcmds, int totalcmds, int dropped_packets, bool ignore, bool paused )
{
	return 0.0f;
}

void CSourceSDKServerGameClients::PostClientMessagesSent()
{
}

void CSourceSDKServerGameClients::ClientEarPosition( edict_t *pEntity, Vector *pEarOrigin )
{
}

int CSourceSDKServerGameClients::GetReplayDelay( edict_t *player, int& entity )
{
	return 0;
}

void CSourceSDKServerGameClients::GetBugReportInfo( char *buf, int buflen )
{
}

void CSourceSDKServerGameClients::NetworkIDValidated( const char *pszUserName, const char *pszNetworkID )
{
}

CPlayerState* CSourceSDKServerGameClients::GetPlayerState( edict_t *player )
{
	return nullptr;
}
