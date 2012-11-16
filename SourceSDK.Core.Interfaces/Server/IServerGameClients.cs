using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface IServerGameClients
    {
	    void GetPlayerLimits(ref int minplayers, ref int maxplayers, ref int defaultMaxPlayers);
	    bool ClientConnect(IEdict pEntity, String name, String address, ref String reject);
		 
	    void ClientActive(IEdict entity, bool bLoadGame);
	    void ClientDisconnect(IEdict entity);
	    void ClientPutInServer(IEdict entity, String playername);
	    void ClientCommand(IEdict entity, String [] args);
	    void SetCommandClient(int index);
		 
	    void ClientSettingsChanged(IEdict edict);
	    void ClientSetupVisibility(IEdict viewEntity, IEdict client, ref String pvs);
		 
	    float ProcessUsercmds(IEdict player, byte[] buf, int numcmds, int totalcmds, int dropped_packets, bool ignore, bool paused);
	    void PostClientMessagesSent();
	    void ClientEarPosition(IEdict pEntity, ref M_Vector earOrigin);
	    int	 GetReplayDelay(IEdict player, ref int entity);

	    void GetBugReportInfo(ref String buf);
	    void NetworkIDValidated(String userName, String networkID);

	    IPlayerState GetPlayerState(IEdict player);
    }
}
