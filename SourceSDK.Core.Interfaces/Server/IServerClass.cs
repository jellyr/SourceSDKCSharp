using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface IServerClass
    {
        String Name { get; }
        String SendNetTableName { get; }

        M_SendProp[] SendProps { get; }

        bool WriteFlag { get; set; }
        bool PropsEncodedAgainstTickCount { get; set; }
    }
}
