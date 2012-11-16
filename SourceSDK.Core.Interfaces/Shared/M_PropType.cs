using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
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
}
