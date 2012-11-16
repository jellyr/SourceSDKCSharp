using SourceSDK.Core.Interfaces.Client;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Entities.Client.Core
{
    [Export(typeof(BaseEntityClient))]
    [Export("worldspawn", typeof(BaseEntityClient))]
    [EntityMeta(ClassName = "worldspawn")]
    class WorldEntity : BaseEntityClient
    {
    }
}
