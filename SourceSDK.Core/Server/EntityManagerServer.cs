using SourceSDK.Core.Interfaces;
using SourceSDK.Core.Interfaces.Server;
using SourceSDK.Core.Interfaces.Shared;
using SourceSDK.Core.Interfaces.Util;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Server
{
    [Export(typeof(IEntityManager))]
    class EntityManagerServer : IEntityManager
    {
        NI_VEngineServer _EngineServer;
        NI_ConsoleManager _ConsoleManager;

        List<BaseEntityServer> _MapEntityList = new List<BaseEntityServer>();
        List<BaseEntityServer> _EntityList = new List<BaseEntityServer>();
        List<BaseEntityServer> _DeleteList = new List<BaseEntityServer>();

        Dictionary<Type, ServerClass> _EntityClasses = new Dictionary<Type, ServerClass>();

        List<int> _EntSerials = new List<int>();

        public IServerClass[] ServerClasses { get; protected set; }

        public const int MaxEntites = (1<<12);

        [ImportingConstructor]
        public EntityManagerServer(NI_VEngineServer engine, NI_ConsoleManager console)
        {
            _EngineServer = engine;
            _ConsoleManager = console;

            Random rand = new Random();

            for (int x = 0; x < MaxEntites; ++x)
                _EntSerials.Add(rand.Next() & 0x7fff);
        }

        public bool ParseAllEntities(string mapEntites)
        {
            var groups = new List<Dictionary<String, String>>();

            if (!KeyValueParser.ParseEntities(mapEntites, groups))
                return false;

            foreach (var g in groups)
            {
                if (!g.ContainsKey("classname"))
                    continue;

                var ent = CreateEntity(g["classname"]);
                ent.LoadMapData(g);

                _MapEntityList.Add(ent);
            }

            return true;
        }

        public void ResetAllEntities()
        {

        }

        public void PrecachePointTemplates()
        {

        }

        public void PostClientMessagesSent()
        {

        }

        public void CleanupDeleteList()
        {
            foreach (var e in _DeleteList)
            {
                e.Release();
                _EngineServer.RemoveEdict(e.Edict);
            }

            _DeleteList.Clear();
        }

        public void ServerActivate()
        {
            foreach (var e in _EntityList)
                e.Activate();
        }

        public void Think()
        {

        }

        public void InvalidateMdlCache()
        {

        }

        public T FindEntity<T>(IEdict edict) where T : class
        {
            foreach (var e in _EntityList)
            {
                if (e.Edict.Equals(edict))
                    return e as T;
            }

            return null;
        }

        public T CreatePlayer<T>(IEdict edict) where T : class
        {
            return CreateEntity("player", edict) as T;
        }

        public BaseEntityServer CreateEntity(String className, int index = -1)
        {
            return CreateEntity(className, null, index);
        }

        private BaseEntityServer CreateEntity(String className, IEdict edict, int index = -1)
        {
            BaseEntityServer ent = null;

            try
            {
                ent = MefServer.GetExportedValue<BaseEntityServer>(className);
                ent.ClassName = className;
            }
            catch (Exception e)
            {
                _ConsoleManager.WriteLine(Color.Red, String.Format("Failed to create entity {0}: {1}", className, e.Message));
                return null;
            }

            if (edict == null)
                _EngineServer.CreateEdict(ent, index);
            else
                ent.Edict = edict;

            _EntityList.Add(ent);

            ent.PostCreate();

            if (ent.IsServerOnly)
            {
                Debug.Assert(false); //todo fix to work
                ent.Edict.SetSlotAndSerial(1, -1);
            }
            else
            {
                int slot = _EngineServer.IndexOfEdict(ent.Edict);
                ent.Edict.SetSlotAndSerial(slot, _EntSerials[slot]);
            }

            return ent;
        }

        public bool GenerateServerClasses()
        {
            var ret = new List<ServerClass>();

            foreach (var c in MefServer.GetExports<BaseEntityServer>())
            {
                object o = null;

                try
                {
                    o = c.Value;
                }
                catch (Exception e)
                {
                    _ConsoleManager.WriteLine(Color.Red, String.Format("Failed to create entity: {0}", e.Message));
                    continue;
                }


                var type = o.GetType();

                if (type == null)
                    continue;

                if (!ProcessServerClassType(type))
                {
                    _ConsoleManager.WriteLine(Color.Red, String.Format("Class {0} does not inheirt from BaseEntityServer. Skipping...", type.Name));
                    continue;
                }

                var sc = CombineServerClasses(type);
                ret.Add(sc);
            }

            ServerClasses = ret.ToArray();
            return true;
        }

        private ServerClass CombineServerClasses(Type type)
        {
            var sp = new List<M_SendProp>();

            ServerClass sc = new ServerClass();
            sc.Name = _EntityClasses[type].Name;
            sc.SendNetTableName = _EntityClasses[type].SendNetTableName;
            
            var baseType = type.BaseType;

            while (baseType.UnderlyingSystemType != typeof(object))
            {
                if (_EntityClasses[baseType].SendProps != null)
                    sp.AddRange(_EntityClasses[baseType].SendProps);

                baseType = baseType.BaseType;
            }

            if (_EntityClasses[type].SendProps != null)
                sp.AddRange(_EntityClasses[type].SendProps);

            sc.SendProps = sp.ToArray();
            return sc;
        }

        private bool ProcessServerClassType(Type type)
        {
            if (_EntityClasses.ContainsKey(type))
                return true;
            else if (type.UnderlyingSystemType == typeof(Object))
                return true;

            EntityMetaAttribute meta = null;

            foreach (var att in Attribute.GetCustomAttributes(type))
            {
                if (att.GetType() != typeof(EntityMetaAttribute))
                    continue;

                meta = att as EntityMetaAttribute;
                break;
            }

            ServerClass sc = null;

            if (meta != null)
                sc = new ServerClass(type.Name, meta);
            else
                sc = new ServerClass(type.Name);

            if (!ProcessServerProps(type, sc))
                return false;

            _EntityClasses.Add(type, sc);
            return ProcessServerClassType(type.BaseType);
        }

        private bool ProcessServerProps(Type type, ServerClass sc)
        {
            var ret = new List<M_SendProp>();

            foreach (var prop in type.GetProperties(BindingFlags.DeclaredOnly | BindingFlags.GetProperty))
            {
                if (prop.GetCustomAttribute(typeof(EntitySendAttribute)) == null)
                    continue;

                PropType pt = PropType.DPT_Int;
                if (!M_SendProp.GetPropType(prop, out pt))
                {
                    _ConsoleManager.WriteLine(Color.Red, String.Format("Skipping property {0} in class {1} as it has an unsupported type", prop.Name, type.Name));
                    continue;
                }

                ret.Add(new M_SendProp(prop));
            }
 
            return true;
        }
    }
}
