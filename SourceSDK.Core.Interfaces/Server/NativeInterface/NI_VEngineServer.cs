using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface NI_VEngineServer
    {
        bool LoadGameState(String mapName, bool createPlayers);

        void LoadAdjacentEnts(String oldLevel, String landmarkName);

        void CreateEdict(IEntity serverEntity, int index = -1);

        void RemoveEdict(IEdict edict);
    }
}
