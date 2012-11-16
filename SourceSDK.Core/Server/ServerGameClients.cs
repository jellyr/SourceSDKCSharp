using SourceSDK.Core.Interfaces.Server;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Server
{
    [Export(typeof(M_IServerGameClients))]
    class ServerGameClients : M_IServerGameClients
    {
        public void GetPlayerLimits(ref int minplayers, ref int maxplayers, ref int defaultMaxPlayers)
        {
            
        }

        public bool ClientConnect(IEdict pEntity, string name, string address, ref string reject)
        {
            return true;
        }

        public void ClientActive(IEdict entity, bool bLoadGame)
        {
            
        }

        public void ClientDisconnect(IEdict entity)
        {
            
        }

        public void ClientPutInServer(IEdict entity, string playername)
        {
            
        }

        public void ClientCommand(IEdict entity, string[] args)
        {
            
        }

        public void SetCommandClient(int index)
        {
            
        }

        public void ClientSettingsChanged(IEdict edict)
        {
            
        }

        public void ClientSetupVisibility(IEdict viewEntity, IEdict client, ref string pvs)
        {
            
        }

        public float ProcessUsercmds(IEdict player, byte[] buf, int numcmds, int totalcmds, int dropped_packets, bool ignore, bool paused)
        {
            return 0.0f;
        }

        public void PostClientMessagesSent()
        {
            
        }

        public void ClientEarPosition(IEdict pEntity, ref Interfaces.Shared.M_Vector earOrigin)
        {
            
        }

        public int GetReplayDelay(IEdict player, ref int entity)
        {
            return 0;
        }

        public void GetBugReportInfo(ref string buf)
        {
            
        }

        public void NetworkIDValidated(string userName, string networkID)
        {
            
        }

        public IPlayerState GetPlayerState(IEdict player)
        {
            return null;
        }
    }
}
