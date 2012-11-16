using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Client
{
	public interface M_IClientEntity : M_IClientUnknown, M_IClientRenderable, M_IClientNetworkable, M_IClientThinkable
	{
		// Network origin + angles
		M_Vector AbsOrigin { get; }
        M_QAngle AbsAngles { get; }

		//M_MouthInfo GetMouth();

		// Retrieve sound spatialization info for the specified sound on this entity
		// Return false to indicate sound is not audible
		//bool GetSoundSpatialization(SpatializationInfo_t& info);
	}
}
