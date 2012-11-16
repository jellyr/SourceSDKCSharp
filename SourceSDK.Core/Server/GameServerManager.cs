using SourceSDK.Core.Interfaces.Server;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Server
{
    [Export(typeof(IGameRuleManager))]
    class GameServerManager : IGameRuleManager
    {
        public string StringTableName
        {
            get { return "GameRuleTable"; }
        }

        public void StartFrame()
        {
        }

        public void EndFrame()
        {
        }

        public void WorldSpawn()
        {
        }

        public void CreateStandardEntities()
        {
        }
    }
}
