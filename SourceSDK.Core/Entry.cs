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
    public class Entry
    {
        public static void ClientInit(IClientInitInterfaces initInterfaces)
        {
            Mef.Init(false);

            LoadMefTypes<IClientInitInterfaces>(initInterfaces);
            LoadCVars();

            initInterfaces.ClientGameDll = Mef.GetExportedValue<IClientGameDll>();
        }

        public static void ServerInit(IServerInitInterfaces initInterfaces)
        {
            Mef.Init(true);

            LoadMefTypes<IServerInitInterfaces>(initInterfaces);
            LoadCVars();

            initInterfaces.ServerGameDll = Mef.GetExportedValue<IServerGameDll>();
            initInterfaces.ServerGameClients = Mef.GetExportedValue<IServerGameClients>();
            initInterfaces.ServerGameEnts = Mef.GetExportedValue<IServerGameEnts>();
        }

        private static void LoadCVars()
        {
            var consoleManager = Mef.GetExportedValue<NI_ConsoleManager>();

            foreach (var conCommand in Mef.GetExportedValues<IConCommand>())
                consoleManager.Register(conCommand);

            foreach (var conVar in Mef.GetExportedValues<IConVariable>())
                consoleManager.Register(conVar);
        }

        private static void LoadMefTypes<T>(T initInterfaces)
        {
            var addType = typeof(Mef).GetMethod("AddType");

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
