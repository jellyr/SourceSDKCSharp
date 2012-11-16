using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Client
{
    public interface M_IClientThinkable
    {
        M_IClientUnknown ClientUnknown { get; }
        IClientThinkHandle ThinkHandle { get; set; }

        void Think();
        void Release();
    }
}
