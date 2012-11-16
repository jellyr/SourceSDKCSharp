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

    public interface NI_GlobalVars
    {
        String MapName { get; }
        String StartSpot { get; }

        int MapVersion { get; }
        int MaxEntites { get; }
        int FrameCount { get; }
        int MaxClients { get; }
        int TickCount { get; }

        float RealTime { get; }
        float AbsFrameTime { get; }
        float CurTime { get; }
        float FrameTime { get; }
        float IntervalPerTick { get; }
    }
}
