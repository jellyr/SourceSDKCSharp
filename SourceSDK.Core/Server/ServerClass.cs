using SourceSDK.Core.Interfaces.Server;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Server
{
    class ServerClass : IServerClass
    {
        public ServerClass()
        {
        }

        public ServerClass(string className)
        {
            Name = className;
            SendNetTableName = className;
        }

        public ServerClass(string className, EntityMetaAttribute meta)
        {
            if (meta != null && !String.IsNullOrEmpty(meta.ClassName))
                Name = meta.ClassName;
            else
                Name = className;

            if (meta != null && !String.IsNullOrEmpty(meta.SentTableName))
                SendNetTableName = meta.SentTableName;
            else
                SendNetTableName = className;
        }

        public string Name
        {
            get;
            set;
        }

        public string SendNetTableName
        {
            get;
            set;
        }

        public M_SendProp[] SendProps
        {
            get;
            set;
        }

        public bool WriteFlag
        {
            get;
            set;
        }

        public bool PropsEncodedAgainstTickCount
        {
            get;
            set;
        }
    }
}
