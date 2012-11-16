using SourceSDK.Core.Interfaces.Server;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Entities.Server.Core
{
    class PointEntity : BaseEntityServer
    {

        public override void Spawn()
        {
            SetSolid(SolidType.SOLID_NONE);
        }

        public override ObjectCap ObjectCaps() 
        {
            return (ObjectCap)(base.ObjectCaps() & ~ObjectCap.FCAP_ACROSS_TRANSITION); 
        }
    }
}
