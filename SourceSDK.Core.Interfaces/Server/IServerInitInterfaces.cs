using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface IServerInitInterfaces
    {
        NI_ConsoleManager ConsoleManager { get; }
        NI_VEngineServer EngineServer { get; }
        NI_VoiceServer VoiceServer { get; }
        NI_NetworkStringTableContainer NetworkStringTableContainer { get; }
        NI_StaticPropManagerServer StaticPropManagerServer { get; }
        NI_EngineSound EngineSound { get; }
        NI_FileSystem FileSystem { get; }
        NI_Random Random { get; }
        NI_SpatialPartition SpatialPartition { get; }
        NI_EngineTrace EngineTrace { get; }
        NI_GameEventManager2 GameEventManager2 { get; }
        NI_DataCache DataCache { get; }
        NI_SoundEmitterSystemBase SoundEmitterSystemBase { get; }
        NI_ServerPluginHelpers ServerPluginHelpers { get; }
        NI_ScenceFileCache SceneFileCache { get; }

        M_IServerGameDll ServerGameDll { get; set; }
        M_IServerGameClients ServerGameClients { get; set; }
        M_IServerGameEnts ServerGameEnts { get; set; }
    }
}
