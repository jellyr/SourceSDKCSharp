using SourceSDK.Core.Interfaces.Client;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Client
{
    public delegate BaseEntityClient CreateEntityHandler(String classname);

    class ClientClass : IClientClass
    {
        public CreateEntityHandler CreateEntity;

        public ClientClass()
        {
        }

        public ClientClass(string className)
        {
            Name = className;
            RecvNetTableName = className;
        }

        public ClientClass(string className, EntityMetaAttribute meta)
        {
            if (meta != null && !String.IsNullOrEmpty(meta.ClassName))
                Name = meta.ClassName;
            else
                Name = className;

            if (meta != null && !String.IsNullOrEmpty(meta.SentTableName))
                RecvNetTableName = meta.SentTableName;
            else
                RecvNetTableName = className;
        }

        public string Name
        {
            get;
            set;
        }

        public bool IsEvent
        {
            get;
            set;
        }

        public string RecvNetTableName
        {
            get;
            set;
        }

        public M_RecvProp[] RecvProps
        {
            get;
            set;
        }

        public M_RecvDecoder Decoder
        {
            get;
            set;
        }

        public BaseEntityClient Create()
        {
            if (CreateEntity != null)
                return CreateEntity(Name);

            return null;
        }
    }
}
