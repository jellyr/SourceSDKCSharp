using SourceSDK.Core.Interfaces.Server;
using SourceSDK.Core.Interfaces.Shared;
using SourceSDK.Entities.Server.Core;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Entities.Server.Info
{
    [Export(typeof(BaseEntityServer))]
    [Export("info_player_start", typeof(BaseEntityServer))]
    [EntityMeta(ClassName = "info_player_start")]
    class PlayerStartEntity : PointEntity
    {
    }
}
