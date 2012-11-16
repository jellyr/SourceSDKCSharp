using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface NI_NetworkStringTableContainer
    {
        MI_NetworkStringTable CreateStringTable(String tableName, int maxCount);
    }
}
