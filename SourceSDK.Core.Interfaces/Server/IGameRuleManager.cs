using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface IGameRuleManager
    {
        String StringTableName { get; }

        void StartFrame();

        void EndFrame();

        void WorldSpawn();

        void CreateStandardEntities();
    }
}
