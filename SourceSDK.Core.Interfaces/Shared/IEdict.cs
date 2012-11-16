using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
    public interface IEdict
    {
        String ClassName { get; }
        void SetSlotAndSerial(int slot, int serial);
    }
}
