using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
    public class M_ScreenFade
    {
        public UInt16 Duration { get; set; }
        public UInt16 HoldTime { get; set; }
        public UInt16 FadeFlags { get; set; }
        public Color Color { get; set; }
    }
}
