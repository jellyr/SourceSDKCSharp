using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
    public interface IGameInfo
    {
        bool IsServer { get; }
        bool IsClient { get; }
    }
}
