using SourceSDK.Core.Interfaces.Shared;
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

        String RecvNetTableName { get; }

        M_RecvProp[] RecvProps { get; }
        M_RecvDecoder Decoder { get; }

        BaseEntityClient Create();
    }
}
