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
        public M_SendProp(PropertyInfo prop)
        {
            EntitySendAttribute sendAtt = null;

            foreach (var att in prop.GetCustomAttributes())
            {
                if (att.GetType() != typeof(EntitySendAttribute))
                    continue;

                sendAtt = att as EntitySendAttribute;
                break;
            }

            Name = prop.Name;
            Property = prop;

            PropType type;
            GetPropType(prop, out type);
            Type = type;

            switch (Type)
            {
                case PropType.DPT_Float:
                case PropType.DPT_Int:
                    FieldLength = 32;
                    break;

                case PropType.DPT_String:
                    FieldLength = 64;
                    break;
            }

            if (sendAtt != null)
            {
                if (!String.IsNullOrEmpty(sendAtt.Name))
                    Name = sendAtt.Name;

                if (sendAtt.Flags.HasValue)
                    Flags = sendAtt.Flags.Value;

                if (sendAtt.FloatMin.HasValue)
                    FloatMin = sendAtt.FloatMin.Value;

                if (sendAtt.FloatMax.HasValue)
                    FloatMax = sendAtt.FloatMax.Value;

                if (sendAtt.FieldLength.HasValue)
                    FieldLength = sendAtt.FieldLength.Value;
            }
        }

        public static bool GetPropType(PropertyInfo prop, out PropType type)
        {
            type = PropType.DPT_Array;

            if (prop.PropertyType == typeof(int))
            {
                type = PropType.DPT_Int;
                return true;
            }
            else if (prop.PropertyType == typeof(float))
            {
                type = PropType.DPT_Float;
                return true;
            }
            else if (prop.PropertyType == typeof(string))
            {
                type = PropType.DPT_String;
                return true;
            }

            return false;
        }

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
