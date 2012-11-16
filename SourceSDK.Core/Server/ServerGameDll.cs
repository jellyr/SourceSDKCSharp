using SourceSDK.Core.Interfaces;
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
        IGameRuleManager _GameRulesManager;
        NI_GlobalVars _Globals;
        IEntityManager _EntityManager;

        NI_NetworkStringTableContainer _StringTable;
        NI_VEngineServer _VEngineServer;

        [ImportingConstructor]
        public ServerGameDll(NI_NetworkStringTableContainer stringTable, IEntityManager entManager, IGameRuleManager gameRulesManager, NI_GlobalVars globals, NI_VEngineServer engineServer)
        {
            _StringTable = stringTable;
            _EntityManager = entManager;
            _Globals = globals;
            _GameRulesManager = gameRulesManager;
            _VEngineServer = engineServer;
        }

        public bool GameInit()
        {
            return true;
        }

        public bool LevelInit(string mapName, string mapEntites, string oldLevel, string landmarkName, bool loadGame, bool background)
        {
            bool bOldLevel = !String.IsNullOrEmpty(oldLevel);

            if (loadGame)
            {
                if (!_VEngineServer.LoadGameState(mapName, true))
                {
                    if (!bOldLevel)
                        _EntityManager.ParseAllEntities(mapEntites);
                    else
                        return false; // Regular save load case
                }

                if (!bOldLevel)
                    _VEngineServer.LoadAdjacentEnts(oldLevel, landmarkName);
            }
            else
            {
                _EntityManager.ResetAllEntities();
                _EntityManager.ParseAllEntities(mapEntites);
            }

            _EntityManager.PrecachePointTemplates();
            _EntityManager.CleanupDeleteList();

            return true;
        }

        public void ServerActivate(IEdict[] edictList, int clientMax)
        {
            _EntityManager.ServerActivate();
        }

        public void GameFrame(bool simulating)
        {
            _GameRulesManager.StartFrame();

            _EntityManager.CleanupDeleteList();
            _EntityManager.Think();
            _EntityManager.CleanupDeleteList();

            _GameRulesManager.EndFrame();
        }

        public void PreClientUpdate(bool simulating)
        {
            
        }

        public void LevelShutdown()
        {
            _EntityManager.ResetAllEntities();
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
            return _EntityManager.ServerClasses;
        }

        public string GetGameDescription()
        {
            return "SDK C#";
        }

        public void CreateNetworkStringTables()
        {
            var gamerulesName = _GameRulesManager.StringTableName;

            var particalTable = _StringTable.CreateStringTable("ParticleEffectNames", (1<<10));
            var effectsTable = _StringTable.CreateStringTable("EffectDispatch", (1 << 10));
            var vguiScreenTable = _StringTable.CreateStringTable("VguiScreen", (1<<8));
            var materialsTable = _StringTable.CreateStringTable("Materials", (1<<10));
            var infoPanelTable = _StringTable.CreateStringTable("InfoPanel", 128);
            var scenesTable = _StringTable.CreateStringTable("Scenes", (1<<12));
            var gamerulesTable = _StringTable.CreateStringTable(gamerulesName, 1);

            MefServer.AddTypeAndName<MI_NetworkStringTable>("ParticleEffectNames", particalTable);
            MefServer.AddTypeAndName<MI_NetworkStringTable>("EffectDispatch", effectsTable);
            MefServer.AddTypeAndName<MI_NetworkStringTable>("VguiScreen", vguiScreenTable);
            MefServer.AddTypeAndName<MI_NetworkStringTable>("Materials", materialsTable);
            MefServer.AddTypeAndName<MI_NetworkStringTable>("InfoPanel", infoPanelTable);
            MefServer.AddTypeAndName<MI_NetworkStringTable>("Scenes", scenesTable);
            MefServer.AddTypeAndName<MI_NetworkStringTable>(gamerulesName, gamerulesTable);
            
            //_MatieralManager.Precache("debug/debugempty");
            //_ParticalManager.Precache("error");
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
            _EntityManager.InvalidateMdlCache();
        }
    }
}
