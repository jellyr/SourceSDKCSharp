using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Client
{
    public interface M_IClientRenderable
    {
        M_IClientUnknown ClientUnknown { get; }

        int Body { get; }
        int Skin { get; }

        M_Vector RenderOrigin { get; }
        M_QAngle RenderAngles { get; }

        bool ShouldDraw { get; }
        bool IsTransparent { get; }
        bool UsesPowerOfTwoFrameBufferTexture { get; }
        bool UsesFullFrameBufferTexture { get; }

        UInt16 RenderHandle { get; }
        IntPtr Model { get; }

        int DrawModel(int flags);
        void DoAnimationEvents();
    }
}
