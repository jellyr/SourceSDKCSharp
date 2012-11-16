using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Shared
{

    public enum WorldFlags
    {
        FL_ONGROUND = (1<<0),	// At rest / on the ground
        FL_DUCKING = (1<<1),	// Player flag -- Player is fully crouched
        FL_WATERJUMP = (1<<2),	// player jumping out of water
        FL_ONTRAIN = (1<<3), // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
        FL_INRAIN = (1<<4),	// Indicates the entity is standing in rain
        FL_FROZEN = (1<<5), // Player is frozen for 3rd person camera
        FL_ATCONTROLS = (1<<6), // Player can't move, but keeps key inputs for controlling another entity
        FL_CLIENT = (1<<7),	// Is a player
        FL_FAKECLIENT = (1<<8),	// Fake client, simulated server side; don't send network messages to them

        // NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
        FL_INWATER = (1<<9),	// In water
        FL_FLY = (1<<10),	// Changes the SV_Movestep() behavior to not need to be on ground
        FL_SWIM = (1<<11),	// Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
        FL_CONVEYOR = (1<<12),
        FL_NPC = (1<<13),
        FL_GODMODE = (1<<14),
        FL_NOTARGET = (1<<15),
        FL_AIMTARGET = (1<<16),	// set if the crosshair needs to aim onto the entity
        FL_PARTIALGROUND = (1<<17),	// not all corners are valid
        FL_STATICPROP = (1<<18),	// Eetsa static prop!		
        FL_GRAPHED = (1<<19), // worldgraph has this ent listed as something that blocks a connection
        FL_GRENADE = (1<<20),
        FL_STEPMOVEMENT = (1<<21),	// Changes the SV_Movestep() behavior to not do any processing
        FL_DONTTOUCH = (1<<22),	// Doesn't generate touch functions, generates Untouch() for anything it was touching when this flag was set
        FL_BASEVELOCITY = (1<<23),	// Base velocity has been applied this frame (used to convert base velocity into momentum)
        FL_WORLDBRUSH = (1<<24),	// Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
        FL_OBJECT = (1<<25), // Terrible name. This is an object that NPCs should see. Missiles, for example.
        FL_KILLME = (1<<26),	// This entity is marked for death -- will be freed by game DLL
        FL_ONFIRE = (1<<27),	// You know...
        FL_DISSOLVING = (1<<28), // We're dissolving!
        FL_TRANSRAGDOLL = (1<<29), // In the process of turning into a client side ragdoll.
        FL_UNBLOCKABLE_BY_PLAYER = (1<<30), // pusher that can't be blocked by the player
    }

    // entity flags, CBaseEntity::m_iEFlags
    public enum EntityFlags
    {
	    EFL_KILLME	=				(1<<0),	// This entity is marked for death -- This allows the game to actually delete ents at a safe time
	    EFL_DORMANT	=				(1<<1),	// Entity is dormant, no updates to client
	    EFL_NOCLIP_ACTIVE =			(1<<2),	// Lets us know when the noclip command is active.
	    EFL_SETTING_UP_BONES =		(1<<3),	// Set while a model is setting up its bones.
	    EFL_KEEP_ON_RECREATE_ENTITIES = (1<<4), // This is a special entity that should not be deleted when we restart entities only

	    //Tony; BUG?? I noticed this today while performing stealz on flag 16! look at the definition of the flag above...
	    EFL_HAS_PLAYER_CHILD=		(1<<4),	// One of the child entities is a player.

	    EFL_DIRTY_SHADOWUPDATE =	(1<<5),	// Client only- need shadow manager to update the shadow...
	    EFL_NOTIFY =				(1<<6),	// Another entity is watching events on this entity (used by teleport)

	    // The default behavior in ShouldTransmit is to not send an entity if it doesn't
	    // have a model. Certain entities want to be sent anyway because all the drawing logic
	    // is in the client DLL. They can set this flag and the engine will transmit them even
	    // if they don't have a model.
	    EFL_FORCE_CHECK_TRANSMIT =	(1<<7),

	    EFL_BOT_FROZEN =			(1<<8),	// This is set on bots that are frozen.
	    EFL_SERVER_ONLY =			(1<<9),	// Non-networked entity.
	    EFL_NO_AUTO_EDICT_ATTACH =	(1<<10), // Don't attach the edict; we're doing it explicitly
	
	    // Some dirty bits with respect to abs computations
	    EFL_DIRTY_ABSTRANSFORM =	(1<<11),
	    EFL_DIRTY_ABSVELOCITY =		(1<<12),
	    EFL_DIRTY_ABSANGVELOCITY =	(1<<13),
	    EFL_DIRTY_SURROUNDING_COLLISION_BOUNDS	= (1<<14),
	    EFL_DIRTY_SPATIAL_PARTITION = (1<<15),
	    EFL_PLUGIN_BASED_BOT		= (1<<16),		//this is set on plugin bots, so that if any games include their own bot code, they won't affect plugin bots.
	    EFL_IN_SKYBOX =				(1<<17),	// This is set if the entity detects that it's in the skybox.
											    // This forces it to pass the "in PVS" for transmission.
	    EFL_USE_PARTITION_WHEN_NOT_SOLID = (1<<18),	// Entities with this flag set show up in the partition even when not solid
	    EFL_TOUCHING_FLUID =		(1<<19),	// Used to determine if an entity is floating

	    // FIXME: Not really sure where I should add this...
	    EFL_IS_BEING_LIFTED_BY_BARNACLE = (1<<20),
	    EFL_NO_ROTORWASH_PUSH =		(1<<21),		// I shouldn't be pushed by the rotorwash
	    EFL_NO_THINK_FUNCTION =		(1<<22),
	    EFL_NO_GAME_PHYSICS_SIMULATION = (1<<23),

	    EFL_CHECK_UNTOUCH =			(1<<24),
	    EFL_DONTBLOCKLOS =			(1<<25),		// I shouldn't block NPC line-of-sight
	    EFL_DONTWALKON =			(1<<26),		// NPC;s should not walk on this entity
	    EFL_NO_DISSOLVE =			(1<<27),		// These guys shouldn't dissolve
	    EFL_NO_MEGAPHYSCANNON_RAGDOLL = (1<<28),	// Mega physcannon can't ragdoll these guys.
	    EFL_NO_WATER_VELOCITY_CHANGE  =	(1<<29),	// Don't adjust this entity's velocity when transitioning into water
	    EFL_NO_PHYSCANNON_INTERACTION =	(1<<30),	// Physcannon can't pick these up or punt them
	    EFL_NO_DAMAGE_FORCES =		(1<<31),	// Doesn't accept forces from physics damage
    }

    public enum SolidType
    {
        SOLID_NONE = 0,	// no solid model
        SOLID_BSP = 1,	// a BSP tree
        SOLID_BBOX = 2,	// an AABB
        SOLID_OBB = 3,	// an OBB (not implemented yet)
        SOLID_OBB_YAW = 4,	// an OBB, constrained so that it can only yaw
        SOLID_CUSTOM = 5,	// Always call into the entity for tests
        SOLID_VPHYSICS = 6,	// solid vphysics object, get vcollide from the model and collide with that
        SOLID_LAST,
    }

    public enum SolidFlags
    {
        FSOLID_CUSTOMRAYTEST = 0x0001,	// Ignore solid type + always call into the entity for ray tests
        FSOLID_CUSTOMBOXTEST = 0x0002,	// Ignore solid type + always call into the entity for swept box tests
        FSOLID_NOT_SOLID = 0x0004,	// Are we currently not solid?
        FSOLID_TRIGGER = 0x0008,	// This is something may be collideable but fires touch functions
        // even when it's not collideable (when the FSOLID_NOT_SOLID flag is set)
        FSOLID_NOT_STANDABLE = 0x0010,	// You can't stand on this
        FSOLID_VOLUME_CONTENTS = 0x0020,	// Contains volumetric contents (like water)
        FSOLID_FORCE_WORLD_ALIGNED = 0x0040,	// Forces the collision rep to be world-aligned even if it's SOLID_BSP or SOLID_VPHYSICS
        FSOLID_USE_TRIGGER_BOUNDS = 0x0080,	// Uses a special trigger bounds separate from the normal OBB
        FSOLID_ROOT_PARENT_ALIGNED = 0x0100,	// Collisions are defined in root parent's local coordinate space
        FSOLID_TRIGGER_TOUCH_DEBRIS = 0x0200,	// This trigger will touch debris objects

        FSOLID_MAX_BITS = 10
    }

    public enum MoveType
    {
        MOVETYPE_NONE = 0,	// never moves
        MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
        MOVETYPE_WALK,				// Player only - moving on the ground
        MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
        MOVETYPE_FLY,				// No gravity, but still collides with stuff
        MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
        MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
        MOVETYPE_PUSH,				// no clip to world, push and crush
        MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
        MOVETYPE_LADDER,			// Used by players only when going onto a ladder
        MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
        MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

        // should always be defined as the last item in the list
        MOVETYPE_LAST = MOVETYPE_CUSTOM,

        MOVETYPE_MAX_BITS = 4
    }

    public enum ObjectCap : uint
    {
        FCAP_MUST_SPAWN = 0x00000001,		// Spawn after restore
        FCAP_ACROSS_TRANSITION = 0x00000002,		// should transfer between transitions 
        // UNDONE: This will ignore transition volumes (trigger_transition), but not the PVS!!!
        FCAP_FORCE_TRANSITION = 0x00000004,		// ALWAYS goes across transitions
        FCAP_NOTIFY_ON_TRANSITION = 0x00000008,		// Entity will receive Inside/Outside transition inputs when a transition occurs

        FCAP_IMPULSE_USE = 0x00000010,		// can be used by the player
        FCAP_CONTINUOUS_USE = 0x00000020,		// can be used by the player
        FCAP_ONOFF_USE = 0x00000040,		// can be used by the player
        FCAP_DIRECTIONAL_USE = 0x00000080,		// Player sends +/- 1 when using (currently only tracktrains)
        // NOTE: Normally +USE only works in direct line of sight.  Add these caps for additional searches
        FCAP_USE_ONGROUND = 0x00000100,
        FCAP_USE_IN_RADIUS = 0x00000200,
        FCAP_SAVE_NON_NETWORKABLE = 0x00000400,

        FCAP_MASTER = 0x10000000,		// Can be used to "master" other entities (like multisource)
        FCAP_WCEDIT_POSITION = 0x40000000,		// Can change position and update Hammer in edit mode
        FCAP_DONT_SAVE = 0x80000000,		// Don't save this
    }
}
