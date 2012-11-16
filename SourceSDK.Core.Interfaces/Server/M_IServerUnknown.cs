using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Server
{
	public interface M_IServerUnknown
	{
		M_ICollideable Collideable { get; }
		M_IServerNetworkable Networkable { get; }
		BaseEntityServer BaseEntity { get; }
	}
}
