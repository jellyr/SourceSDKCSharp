using SourceSDK.Core.Interfaces;
using SourceSDK.Core.Interfaces.Client;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Client
{
    [Export(typeof(IEntityManagerClient))]
    class EntityManagerClient : IEntityManagerClient
    {
        List<BaseEntityClient> _EntityList = new List<BaseEntityClient>();
        Dictionary<Type, ClientClass> _EntityClasses = new Dictionary<Type, ClientClass>();

        public IClientClass[] ClientClasses { get; protected set; }

        NI_ConsoleManager _ConsoleManager;

        [ImportingConstructor]
        public EntityManagerClient(NI_ConsoleManager consoleManager)
        {
            _ConsoleManager = consoleManager;
        }

        public BaseEntityClient CreateEntity(String className)
        {
            BaseEntityClient ent = null;

            try
            {
                ent = MefServer.GetExportedValue<BaseEntityClient>(className);
                ent.ClassName = className;
            }
            catch (Exception e)
            {
                _ConsoleManager.WriteLine(Color.Red, String.Format("Failed to create entity {0}: {1}", className, e.Message));
                return null;
            }

            _EntityList.Add(ent);
            return ent;
        }

        public bool GenerateClientClasses()
        {
            var ret = new List<ClientClass>();

            foreach (var c in MefClient.GetExports<BaseEntityClient>())
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

                if (!ProcessClientClassType(type))
                {
                    _ConsoleManager.WriteLine(Color.Red, String.Format("Class {0} does not inheirt from BaseEntityClient. Skipping...", type.Name));
                    continue;
                }

                var sc = CombineClientClasses(type);
                ret.Add(sc);
            }

            ClientClasses = ret.ToArray();
            return true;
        }

        private ClientClass CombineClientClasses(Type type)
        {
            var rp = new List<M_RecvProp>();

            ClientClass cc = new ClientClass();

            cc.CreateEntity = (classname) => this.CreateEntity(classname);

            cc.Name = _EntityClasses[type].Name;
            cc.RecvNetTableName = _EntityClasses[type].RecvNetTableName;

            var baseType = type.BaseType;

            while (baseType.UnderlyingSystemType != typeof(object))
            {
                if (_EntityClasses[baseType].RecvProps != null)
                    rp.AddRange(_EntityClasses[baseType].RecvProps);

                baseType = baseType.BaseType;
            }

            if (_EntityClasses[type].RecvProps != null)
                rp.AddRange(_EntityClasses[type].RecvProps);

            cc.RecvProps = rp.ToArray();
            return cc;
        }

        private bool ProcessClientClassType(Type type)
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

            ClientClass cc = null;

            if (meta != null)
                cc = new ClientClass(type.Name, meta);
            else
                cc = new ClientClass(type.Name);

            if (!ProcessClientProps(type, cc))
                return false;

            _EntityClasses.Add(type, cc);
            return ProcessClientClassType(type.BaseType);
        }

        private bool ProcessClientProps(Type type, ClientClass sc)
        {
            var ret = new List<M_RecvProp>();

            foreach (var prop in type.GetProperties(BindingFlags.DeclaredOnly | BindingFlags.GetProperty))
            {
                if (prop.GetCustomAttribute(typeof(EntitySendAttribute)) == null)
                    continue;

                PropType pt = PropType.DPT_Int;
                if (!M_RecvProp.GetPropType(prop, out pt))
                {
                    _ConsoleManager.WriteLine(Color.Red, String.Format("Skipping property {0} in class {1} as it has an unsupported type", prop.Name, type.Name));
                    continue;
                }

                ret.Add(new M_RecvProp(prop));
            }

            return true;
        }

    

    }
}
