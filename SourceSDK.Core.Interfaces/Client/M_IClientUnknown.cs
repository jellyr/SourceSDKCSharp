using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Client
{
    public interface M_IClientUnknown : M_IHandleEntity
    {
        M_ICollideable Collideable { get; }
	    M_IClientNetworkable ClientNetworkable{get;}
	    M_IClientRenderable ClientRenderable{get;}
	    M_IClientEntity ClientEntity{get;}
	    BaseEntityClient BaseEntity {get;}
	    M_IClientThinkable ClientThinkable{get;}
    }
}
