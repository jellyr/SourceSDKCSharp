using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Client
{
    public interface IClientClass
    {
        String Name { get; }
        bool IsEvent { get; }

        String RecvTableName { get; }
        String RecvNetTableName { get; }

        M_RecvProp[] RecvProps { get; }
        M_RecvDecoder Decoder { get; }

        M_IClientNetworkable Create();
        M_IClientNetworkable Create(int entnum, int serialNum);

        M_IClientUnknown ClientUnknown { get; }
    }
}
