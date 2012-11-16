using SourceSDK.Core.Interfaces.Server;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{
    public interface IEntity
    {
        //Handle for client
        IEntityHandle Handle { get; set; }

        //Edict for server
        IEdict Edict { get; set; }

        void Release();


        int AreaNum { get; }
        IPvsInfo PvsInfo { get; }

        String ClassName { get; }
        String ModelName { get; }
        int ModelIndex { get; set; }
    }
}
