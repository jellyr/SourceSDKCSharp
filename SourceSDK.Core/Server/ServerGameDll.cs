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
    [Export(typeof(IServerGameDll))]
    class ServerGameDll : IServerGameDll
    {
        public bool GameInit()
        {
            return true;
        }

        public bool levelInit(string mapName, string mapEntites, string oldLevel, string landmarkName, bool loadGame, bool background)
        {
            return true;
        }

        public void ServerActivate(Interfaces.Shared.IEdict[] edictList, int clientMax)
        {
            
        }

        public void GameGrame(bool simulating)
        {
            
        }

        public void PreClientUpdate(bool simulating)
        {
            
        }

        public void LevelShutdown()
        {
            
        }

        public void GameShutdown()
        {
            
        }

        public void DllShutDown()
        {
            
        }

        public float GetTickInterval()
        {
            return 0.015f;
        }

        public IServerClasses[] GetAllServerClasses()
        {
            return null;
        }

        public string GetGameDescription()
        {
            return "SDK C#";
        }

        public void CreateNetworkStringTables()
        {
            
        }

        public IStandardSendProxies[] GetStandardSendProxies()
        {
            return null;
        }

        public void PostInit()
        {
            
        }

        public void Think(bool finalTick)
        {
            
        }

        public bool ShouldHideServer()
        {
            return false;
        }

        public void InvalidateMdlCache()
        {
            
        }
    }
}
