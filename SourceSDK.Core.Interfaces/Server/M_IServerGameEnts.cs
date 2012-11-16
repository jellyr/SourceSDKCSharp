using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface M_IServerGameEnts
    {
	    void SetDebugEdictBase(IEdict edict);
	    void MarkEntitiesAsTouching(IEdict e1, IEdict e2);
	    void FreeContainingEntity(IEdict edict); 

	    IEdict BaseEntityToEdict(IBaseEntity entity);
	    IBaseEntity EdictToBaseEntity(IEdict edict);

	    void CheckTransmit(ICheckTransmitInfo info, UInt16[] edictIndices);
    }
}
