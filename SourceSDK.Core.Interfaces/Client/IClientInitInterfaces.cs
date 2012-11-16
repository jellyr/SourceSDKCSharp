using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Client
{
    public interface IClientInitInterfaces
    {
        NI_ConsoleManager ConsoleManager { get; }
        NI_VEngineClient EngineClient { get; }
        NI_VModelRender ModelRender { get; }
        NI_VEfx Effects { get; }
        NI_EngineTrace EngineTrace { get; }
        NI_VRenderView RenderView { get; }
        NI_VDebugOverlay DebugOverlay { get; }
        NI_DataCache DataCache { get; }
        NI_VModelInfoClient ModelInfoClient {get;}
        NI_EngineVgui EngineVgui { get; }
        NI_NetworkStringTable NetworkStringTable { get; }
        NI_SpatialPartition SpatialPartition { get; }
        NI_ShadowManager ShadowManager { get; }
        NI_StaticPropManager StaticPropManager { get; }
        NI_EngineSound EngineSound { get; }
        NI_FileSystem FileSystem { get; }
        NI_Random Random { get; }
        NI_GameUiFunctions GameUiFunctions { get; }
        NI_GameEventManager GameEventManager { get; }
        NI_SoundEmitterBase SoundSmitterBase { get; }
        NI_InputSystem InputSystem { get; }

        IClientGameDll ClientGameDll { get; set; }
    }
}
