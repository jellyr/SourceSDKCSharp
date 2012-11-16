using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;

namespace SourceSDK.Core.Interfaces.Server
{

    public class M_SendProp
    {
        public String Name { get; set; }
        public PropType Type { get; set; }
        public int Flags { get; set; }
        public PropertyInfo Property { get; set; }

        public float FloatMin { get; set; }
        public float FloatMax { get; set; }

        public int FieldLength { get; set; }

        public int GetInt(Object o)
        {
            if (Type != PropType.DPT_Int)
            {
                Debug.Assert(false);
                return 0;
            }

            return (int)Property.GetValue(o);
        }

        public float GetFloat(Object o)
        {
            if (Type != PropType.DPT_Float)
            {
                Debug.Assert(false);
                return 0.0f;
            }

            return (float)Property.GetValue(o);
        }

        public String GetString(Object o)
        {
            if (Type != PropType.DPT_String)
            {
                Debug.Assert(false);
                return "";
            }

            return (String)Property.GetValue(o);
        }

    }
}
