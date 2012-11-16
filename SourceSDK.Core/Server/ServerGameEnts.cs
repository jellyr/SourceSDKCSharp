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
    [Export(typeof(M_IServerGameEnts))]
    class ServerGameEnts : M_IServerGameEnts
    {
        public void SetDebugEdictBase(IEdict edict)
        {
            
        }

        public void MarkEntitiesAsTouching(IEdict e1, IEdict e2)
        {
            
        }

        public void FreeContainingEntity(IEdict edict)
        {
            
        }

        public IEdict BaseEntityToEdict(IEntity entity)
        {
            return null;
        }

        public IEntity EdictToBaseEntity(IEdict edict)
        {
            return null;
        }

        public void CheckTransmit(ICheckTransmitInfo info, ushort[] edictIndices)
        {
            
        }
    }
}
