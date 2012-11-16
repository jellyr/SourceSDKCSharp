using SourceSDK.Core.Interfaces.Server;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Entities.Server.Core
{
    [Export(typeof(BaseEntityServer))]
    [Export("worldspawn", typeof(BaseEntityServer))]
    [EntityMeta(ClassName = "worldspawn")]
    class WorldEntity : BaseEntityServer
    {
        M_Vector WorldMax = new M_Vector();
        M_Vector WorldMin = new M_Vector();

        String SkyName;
        String DetailMaterial;
        String DeatilVbsp;

        int MaxPropScreenWidth;
        int MapVersion;

        IGameRuleManager _GameRuleManager;

        [ImportingConstructor]
        public WorldEntity(IGameRuleManager gameRules)
        {
            AddEFlags(EntityFlags.EFL_NO_AUTO_EDICT_ATTACH | EntityFlags.EFL_KEEP_ON_RECREATE_ENTITIES);
            //NetworkProp()->AttachEdict(RequiredEdictIndex());

            SetSolid(SolidType.SOLID_BSP);
            SetMoveType(MoveType.MOVETYPE_NONE);

            _GameRuleManager = gameRules;
        }

        public override void Spawn()
        {
            LocalOrigin = M_Vector.Origin;
            LocalAngles = M_QAngle.Origin;

            // NOTE:  SHOULD NEVER BE ANYTHING OTHER THAN 1!!!
            ModelIndex = 1;

            // world model
            AddFlag(WorldFlags.FL_WORLDBRUSH);
            Precache();
        }

        public override int RequiredEdictIndex()
        {
            // the world always needs to be in slot 0
            return 0;
        }

        public override void Precache()
        {
            _GameRuleManager.WorldSpawn();
            _GameRuleManager.CreateStandardEntities();
        }

        public override void LoadMapData(Dictionary<string, string> keyValues)
        {

        }
    }
}
