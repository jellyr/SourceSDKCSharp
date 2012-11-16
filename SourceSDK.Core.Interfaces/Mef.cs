using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.ComponentModel.Composition.Hosting;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;


namespace SourceSDK.Core.Interfaces
{
    public static class MefClient
    {
        private static object _MefLock = new object();
        private static CompositionContainer _Container;

        public static T GetExportedValue<T>()
        {
            return _Container.GetExportedValue<T>();
        }

        public static IEnumerable<T> GetExportedValues<T>()
        {
            return _Container.GetExportedValues<T>();
        }

        public static void Init(Assembly entryAssembly)
        {
            if (_Container != null)
                return;

            var path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

            var catalog = new AggregateCatalog(new DirectoryCatalog(path, "*.Client.dll"), new AssemblyCatalog(entryAssembly));
            _Container = new CompositionContainer(catalog);
        }

        public static void AddType<T>(T instance)
        {
            _Container.ComposeExportedValue<T>(instance);
        }

        public static void AddTypeAndName<T>(String name, T instance)
        {
            _Container.ComposeExportedValue<T>(name, instance);
        }
    }

    public static class MefServer
    {
        private static object _MefLock = new object();
        private static CompositionContainer _Container;

        public static T GetExportedValue<T>()
        {
            return _Container.GetExportedValue<T>();
        }

        public static IEnumerable<T> GetExportedValues<T>()
        {
            return _Container.GetExportedValues<T>();
        }

        public static void Init(Assembly entryAssembly)
        {
            if (_Container != null)
                return;

            var path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

            var catalog = new AggregateCatalog(new DirectoryCatalog(path, "*.Server.dll"), new AssemblyCatalog(entryAssembly));
            _Container = new CompositionContainer(catalog);
        }

        public static void AddType<T>(T instance)
        {
            _Container.ComposeExportedValue<T>(instance);
        }

        public static void AddTypeAndName<T>(String name, T instance)
        {
            _Container.ComposeExportedValue<T>(name, instance);
        }
    }
}
