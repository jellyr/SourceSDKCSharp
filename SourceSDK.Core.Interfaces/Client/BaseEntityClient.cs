using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Client
{
    public class BaseEntityClient : M_IClientEntity
    {
        public BaseEntityClient()
        {
        }

        public void Release()
        {
        }

        public M_ICollideable Collideable
        {
            get;
            protected set;
        }

        public M_IClientNetworkable ClientNetworkable
        {
            get { return this; }
        }

        public M_IClientRenderable ClientRenderable
        {
            get { return this; }
        }

        public M_IClientEntity ClientEntity
        {
            get { return this; }
        }

        public BaseEntityClient BaseEntity
        {
            get { return this; }
        }

        public M_IClientThinkable ClientThinkable
        {
            get { return this; }
        }

        public BaseHandle BaseHandle
        {
            get;
            set;
        }

        public M_IClientUnknown ClientUnknown
        {
            get { return this; }
        }

        public int Body
        {
            get;
            protected set;
        }

        public int Skin
        {
            get;
            protected set;
        }

        public M_Vector AbsOrigin
        {
            get;
            protected set;
        }

        public M_QAngle AbsAngles
        {
            get;
            protected set;
        }

        public M_Vector RenderOrigin
        {
            get;
            protected set;
        }

        public M_QAngle RenderAngles
        {
            get;
            protected set;
        }

        public bool ShouldDraw
        {
            get;
            protected set;
        }

        public bool IsTransparent
        {
            get;
            protected set;
        }

        public bool UsesPowerOfTwoFrameBufferTexture
        {
            get;
            protected set;
        }

        public bool UsesFullFrameBufferTexture
        {
            get;
            protected set;
        }

        public ushort RenderHandle
        {
            get;
            protected set;
        }

        public IntPtr Model
        {
            get;
            protected set;
        }

        public int DrawModel(int flags)
        {
            return 0;
        }

        public void DoAnimationEvents()
        {
        }


        public IClientClass ClientClass
        {
            get;
            protected set;
        }

        public bool IsDormant
        {
            get { return false; }
        }

        public int EntIndex
        {
            get { return BaseHandle.EntityIndex; }
        }

        public void RecvMessage(int classId, byte[] message)
        {
        }

        public IClientThinkHandle ThinkHandle
        {
            get;
            set;
        }

        public void Think()
        {

        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////

        public virtual int MaxHealth { get { return 100; } }
        public int Health { get; set; }
        public String ClassName { get; set; }
        public BaseEntityClient Parent { get; set; }

        public bool IsAlive { get; set; }
        public virtual bool IsPlayer { get { return false; } }
        public virtual bool IsNpc { get { return false; } }
        public virtual bool IsBot { get { return false; } }

        public bool IsServer { get { return false; } }
        public bool IsClient { get { return true; } }

        public void Spawn()
        {
        }

        public void Precache()
        {
        }

        public void Activate()
        {
        }
    }
}
