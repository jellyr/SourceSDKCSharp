#include "Stdafx.h"
#include "serverGameClients.h"

#include "EdictWrapper.h"


void CSourceSDKServerGameClients::GetPlayerLimits( int& minplayers, int& maxplayers, int &defaultMaxPlayers ) const
{
	SourceSDK::Core::Entry::GetPlayerLimits(minplayers, maxplayers, defaultMaxPlayers);
}

bool CSourceSDKServerGameClients::ClientConnect( edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen)
{
	auto edi = gcnew EdictWrapper(pEntity);

	auto rej = gcnew String("");
	auto res = m_pServerGameClients->ClientConnect(edi, gcnew String(pszName), gcnew String(pszAddress), rej);

	if (!res)
	{
		std::string szRej = marshal_as<std::string>(rej);
		Q_strncpy(reject, szRej.c_str(), maxrejectlen);
	}

	return res;
}
		 
void CSourceSDKServerGameClients::ClientActive( edict_t *pEntity, bool bLoadGame )
{
	auto edi = gcnew EdictWrapper(pEntity);
	m_pServerGameClients->ClientActive(edi, bLoadGame);
}

void CSourceSDKServerGameClients::ClientDisconnect( edict_t *pEntity )
{
	auto edi = gcnew EdictWrapper(pEntity);
	m_pServerGameClients->ClientDisconnect(edi);
}

void CSourceSDKServerGameClients::ClientPutInServer( edict_t *pEntity, char const *playername )
{
	auto edi = gcnew EdictWrapper(pEntity);
	m_pServerGameClients->ClientPutInServer(edi, gcnew String(playername));
}

void CSourceSDKServerGameClients::ClientCommand(edict_t *pEntity, const CCommand &command)
{
	auto edi = gcnew EdictWrapper(pEntity);

	auto args = gcnew List<String^>();

	for (int x=0; x<command.ArgC(); ++x)
		args->Add(gcnew String(command[x]));

	m_pServerGameClients->ClientCommand(edi, args->ToArray());
}

void CSourceSDKServerGameClients::SetCommandClient(int index)
{
	m_pServerGameClients->SetCommandClient(index);
}

		 
void CSourceSDKServerGameClients::ClientSettingsChanged(edict_t *pEdict)
{
	auto edi = gcnew EdictWrapper(pEdict);
	m_pServerGameClients->ClientSettingsChanged(edi);
}

void CSourceSDKServerGameClients::ClientSetupVisibility(edict_t *pViewEntity, edict_t *pClient, unsigned char *pvs, int pvssize)
{
}
		 
float CSourceSDKServerGameClients::ProcessUsercmds(edict_t *player, bf_read *buf, int numcmds, int totalcmds, int dropped_packets, bool ignore, bool paused)
{
	return 0.0f;
}

void CSourceSDKServerGameClients::PostClientMessagesSent()
{
	m_pServerGameClients->PostClientMessagesSent();
}

void CSourceSDKServerGameClients::ClientEarPosition(edict_t *pEntity, Vector *pEarOrigin)
{
}

int CSourceSDKServerGameClients::GetReplayDelay(edict_t *player, int& entity)
{
	auto edi = gcnew EdictWrapper(player);
	return m_pServerGameClients->GetReplayDelay(edi, entity);
}

void CSourceSDKServerGameClients::GetBugReportInfo(char *buf, int buflen)
{
}

void CSourceSDKServerGameClients::NetworkIDValidated(const char *pszUserName, const char *pszNetworkID)
{
	m_pServerGameClients->NetworkIDValidated(gcnew String(pszUserName), gcnew String(pszNetworkID));
}

CPlayerState* CSourceSDKServerGameClients::GetPlayerState(edict_t *player)
{
	auto edi = gcnew EdictWrapper(player);
	auto ret = m_pServerGameClients->GetPlayerState(edi);

	if (!ret)
		return nullptr;


}
