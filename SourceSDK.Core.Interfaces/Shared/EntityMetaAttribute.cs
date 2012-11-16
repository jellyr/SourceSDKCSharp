using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
    [AttributeUsage(AttributeTargets.Class)]
    public class EntityMetaAttribute : Attribute
    {
        public String ClassName { get; set; }
        public String SentTableName { get; set; }
    }

    [AttributeUsage(AttributeTargets.Property)]
    public class EntitySendAttribute : Attribute
    {
        public String Name;
        public int? Flags;

        public int? FieldLength;

        public float? FloatMin;
        public float? FloatMax;
    }
}
