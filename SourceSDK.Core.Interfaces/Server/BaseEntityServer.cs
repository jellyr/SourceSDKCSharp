using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Server
{
    public class BaseEntityServer : IEntity
    {
        public IEdict Edict { get; set; }
        public IPvsInfo PvsInfo { get; set; }

        public int AreaNum { get; set; }
        public int ModelIndex { get; set; }

        public string ClassName { get; set; }
        public string ModelName { get; set; }

        public M_Vector LocalOrigin { get; set; }
        public M_QAngle LocalAngles { get; set; }

        public virtual void Release()
        {
        }

        public virtual int RequiredEdictIndex() 
        { 
            return -1; 
        }

        public virtual void LoadMapData(Dictionary<string, string> keyValues)
        {
        }

        public virtual ObjectCap ObjectCaps()
        {
            return ObjectCap.FCAP_ACROSS_TRANSITION;
        }

        public void PostCreate()
        {
        }

        public virtual void Activate()
        {
        }

        public virtual void Spawn()
        {
        }

        public virtual void Precache()
        {
        }

        public void AddFlag(WorldFlags flag)
        {
        }

        public void AddEFlags(EntityFlags flags)
        {
        }

        public void SetMoveType(MoveType moveType)
        {
        }

        public void SetSolid(SolidType solidType)
        {
        }

        public IEntityHandle Handle
        {
            get;
            set;
        }

        public bool IsServerOnly
        {
            get;
            protected set;
        }
    }
}
