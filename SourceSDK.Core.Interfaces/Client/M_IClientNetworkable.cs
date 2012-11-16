using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Client
{
    public interface M_IClientNetworkable
    {
        M_IClientUnknown ClientUnknown { get; }
        IClientClass ClientClass { get; }

        void Release();

        bool IsDormant { get; }
        int EntIndex { get; }

        void RecvMessage(int classId, byte[] message);
    }
}
