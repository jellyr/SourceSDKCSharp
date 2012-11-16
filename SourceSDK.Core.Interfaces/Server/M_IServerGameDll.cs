using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface M_IServerGameDll
    {
        bool GameInit();

        bool LevelInit(String mapName, String mapEntites, String oldLevel, String landmarkName, bool loadGame, bool background);

        void ServerActivate(IEdict[] edictList, int clientMax);

        void GameFrame(bool simulating);

        void PreClientUpdate(bool simulating);

        void LevelShutdown();

        void GameShutdown();

        void DllShutDown();

        float GetTickInterval();

        IServerClass[] GetAllServerClasses();

        String GetGameDescription();

        void CreateNetworkStringTables();

        IStandardSendProxies[] GetStandardSendProxies();

        void PostInit();

        void Think(bool finalTick);

        bool ShouldHideServer();

        void InvalidateMdlCache();
    }
}
