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
    [Export(typeof(M_IServerGameDll))]
    class ServerGameDll : M_IServerGameDll
    {
        public bool GameInit()
        {
            return true;
        }

        public bool LevelInit(string mapName, string mapEntites, string oldLevel, string landmarkName, bool loadGame, bool background)
        {
            return true;
        }

        public void ServerActivate(Interfaces.Shared.IEdict[] edictList, int clientMax)
        {
            
        }

        public void GameFrame(bool simulating)
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

        public IServerClass[] GetAllServerClasses()
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
