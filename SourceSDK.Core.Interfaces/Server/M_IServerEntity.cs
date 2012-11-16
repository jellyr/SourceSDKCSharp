using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface M_IServerEntity : M_IServerUnknown
    {
        int ModelIndex { get; set; }
        String ModelName { get; }
    }
}
