using SourceSDK.Core.Interfaces;
using SourceSDK.Core.Interfaces.Client;
using SourceSDK.Core.Interfaces.Server;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core
{
    internal class GameInfo : IGameInfo
    {
        internal GameInfo(bool isServer)
        {
            IsServer = isServer;
            IsClient = !isServer;
        }

        public bool IsServer { get; protected set; }
        public bool IsClient { get; protected set; }
    }

    public class Entry
    {
        public static void GetPlayerLimits(ref int minplayers, ref int maxplayers, ref int defaultMaxPlayers)
        {
            minplayers = defaultMaxPlayers = 2;
            maxplayers = 16;
        }

        public static void ClientInit(IClientInitInterfaces initInterfaces)
        {
            MefClient.Init(Assembly.GetExecutingAssembly());
            MefClient.AddType<IGameInfo>(new GameInfo(false));

            LoadMefTypes<IClientInitInterfaces>(initInterfaces, typeof(MefClient));

            var entMng = MefClient.GetExportedValue<IEntityManagerClient>();
            entMng.GenerateClientClasses();

            var consoleManager = MefClient.GetExportedValue<NI_ConsoleManager>();

            foreach (var conCommand in MefClient.GetExportedValues<IConCommand>())
                consoleManager.Register(conCommand);

            foreach (var conVar in MefClient.GetExportedValues<IConVariable>())
                consoleManager.Register(conVar);

            initInterfaces.ClientGameDll = MefClient.GetExportedValue<M_IClientGameDll>();
        }

        public static void ServerInit(IServerInitInterfaces initInterfaces)
        {
            MefServer.Init(Assembly.GetExecutingAssembly());
            MefServer.AddType<IGameInfo>(new GameInfo(true));

            LoadMefTypes<IServerInitInterfaces>(initInterfaces, typeof(MefServer));

            MefServer.GetExportedValue<IEntityManager>().GenerateServerClasses();


            var consoleManager = MefServer.GetExportedValue<NI_ConsoleManager>();

            foreach (var conCommand in MefServer.GetExportedValues<IConCommand>())
                consoleManager.Register(conCommand);

            foreach (var conVar in MefServer.GetExportedValues<IConVariable>())
                consoleManager.Register(conVar);


            initInterfaces.ServerGameDll = MefServer.GetExportedValue<M_IServerGameDll>();
            initInterfaces.ServerGameClients = MefServer.GetExportedValue<M_IServerGameClients>();
            initInterfaces.ServerGameEnts = MefServer.GetExportedValue<M_IServerGameEnts>();
        }

        private static void LoadMefTypes<T>(T initInterfaces, Type mefType)
        {
            var addType = mefType.GetMethod("AddType");

            var it = initInterfaces.GetType();
            foreach (var p in it.GetProperties())
            {
                var val = p.GetValue(initInterfaces);

                if (val != null)
                {
                    var generic = addType.MakeGenericMethod(p.PropertyType);
                    generic.Invoke(null, new object[] { val });
                }
            }
        }
    }
}
