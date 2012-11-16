using SourceSDK.Core.Interfaces.Client;
using SourceSDK.Core.Interfaces.Shared;
using SourceSDK.Entities.Client.Core;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Entities.Client.Info
{
    [Export(typeof(BaseEntityClient))]
    [Export("info_player_start", typeof(BaseEntityClient))]
    [EntityMeta(ClassName = "info_player_start")]
    class PlayerStartEntity : PointEntity
    {
    }
}
