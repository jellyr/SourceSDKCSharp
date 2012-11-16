using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;

namespace SourceSDK.Core.Interfaces.Client
{
    public class M_RecvProp
    {
        public M_RecvProp(PropertyInfo prop)
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

            if (sendAtt != null)
            {
                if (!String.IsNullOrEmpty(sendAtt.Name))
                    Name = sendAtt.Name;

                if (sendAtt.Flags.HasValue)
                    Flags = sendAtt.Flags.Value;
            }
        }

        public String Name { get; set; }
        public PropType Type { get; set; }
        public int Flags { get; set; }
        public PropertyInfo Property { get; set; }

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

        public void SetValue(Object o, int val)
        {
            if (Type != PropType.DPT_Int)
            {
                Debug.Assert(false);
                return;
            }

            Property.SetValue(0, val);
        }

        public void SetValue(Object o, float val)
        {
            if (Type != PropType.DPT_Float)
            {
                Debug.Assert(false);
                return;
            }

            Property.SetValue(0, val);
        }

        public void SetValue(Object o, String val)
        {
            if (Type != PropType.DPT_String)
            {
                Debug.Assert(false);
                return;
            }

            Property.SetValue(0, val);
        }
    }
}
