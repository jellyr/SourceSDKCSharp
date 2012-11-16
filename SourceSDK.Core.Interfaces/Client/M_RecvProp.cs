using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;

namespace SourceSDK.Core.Interfaces.Client
{
    public enum PropType
    {
        DPT_Int = 0,
        DPT_Float,
        DPT_Vector,
        DPT_String,
        DPT_Array,	// An array of the base types (can't be of datatables).
        DPT_DataTable,
    }

    public class M_RecvProp
    {
        public String Name { get; set; }
        public PropType Type { get; set; }
        public int Flags { get; set; }
        public PropertyInfo Property { get; set; }

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
