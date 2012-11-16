using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SourceSDK.Core.Interfaces.Client
{
    public class M_ViewSetup
    {
        // shared by 2D & 3D views

        // left side of view window
        public int X;
        // top side of view window
        public int Y;
        // width of view window
        public int Width;
        // height of view window
        public int Height;

        // the rest are only used by 3D views

        // Orthographic projection?
        public bool Ortho;
        // View-space rectangle for ortho projection.
        public float OrthoLeft;
        public float OrthoTop;
        public float OrthoRight;
        public float OrthoBottom;

        // horizontal FOV in degrees
        public float Fov;
        // horizontal FOV in degrees for in-view model
        public float FovViewmodel;

        // 3D origin of camera
        public M_Vector Origin;

        // heading of camera (pitch, yaw, roll)
        public M_QAngle Angles;
        // local Z coordinate of near plane of camera
        public float zNear;
        // local Z coordinate of far plane of camera
        public float zFar;

        // local Z coordinate of near plane of camera ( when rendering view model )
        public float zNearViewmodel;
        // local Z coordinate of far plane of camera ( when rendering view model )
        public float zFarViewmodel;

        // set to true if this is to draw into a subrect of the larger screen
        // this really is a hack, but no more than the rest of the way this class is used
        public bool RenderToSubrectOfLargerScreen;

        // The aspect ratio to use for computing the perspective projection matrix
        // (0.0f means use the viewport)
        public float AspectRatio;

        // Controls for off-center projection (needed for poster rendering)
        public bool OffCenter;
        public float OffCenterTop;
        public float OffCenterBottom;
        public float OffCenterLeft;
        public float OffCenterRight;

        // Control that the SFM needs to tell the engine not to do certain post-processing steps
        public bool DoBloomAndToneMapping;

        // Cached mode for certain full-scene per-frame varying state such as sun entity coverage
        public bool CacheFullSceneState;
    }
}
