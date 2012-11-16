using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
    public class M_QAngle
    {
        public readonly static M_QAngle Origin = new M_QAngle();

        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }
    }
}
