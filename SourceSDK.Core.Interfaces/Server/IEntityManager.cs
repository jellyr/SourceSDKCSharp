using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Server
{
    public interface IEntityManager
    {
        bool ParseAllEntities(string mapEntites);

        void ResetAllEntities();

        void PrecachePointTemplates();

        void CleanupDeleteList();

        void ServerActivate();

        void Think();

        void InvalidateMdlCache();

        BaseEntityServer CreateEntity(String className, int index = -1);

        IServerClass[] ServerClasses { get; }

        bool GenerateServerClasses();
    }
}
