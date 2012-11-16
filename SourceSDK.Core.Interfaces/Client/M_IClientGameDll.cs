using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Interfaces.Client
{
    public enum ButtonCode
    {
    }

    public enum ClientFrameStage
    {
	    FRAME_UNDEFINED=-1,			// (haven't run any frames yet)
	    FRAME_START,
	    // A network packet is being recieved
	    FRAME_NET_UPDATE_START,
		// Data has been received and we're going to start calling PostDataUpdate
		FRAME_NET_UPDATE_POSTDATAUPDATE_START,
		// Data has been received and we've called PostDataUpdate on all data recipients
		FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	    // We've received all packets, we can now do interpolation, prediction, etc..
	    FRAME_NET_UPDATE_END,		
	    // We're about to start rendering the scene
	    FRAME_RENDER_START,
	    // We've finished rendering the scene.
	    FRAME_RENDER_END
    }

    public interface M_IClientGameDll
    {
        void PostInit();
        void Shutdown();

        void LevelInitPreEntity(String mapName);
        void LevelInitPostEntity();
        void LevelShutdown();

        IClientClass[] GetAllClasses();

        int HudVidinit();
        void HudProcessInput(bool active);
        void HudUpdate(bool active);
        void HudReset();
        void HudText(String message);

        void OnActiveMouse();
        void OnDeactiveMouse();
        void OnAccumlate();
        void OnClearStates();
        int OnKeyEvent(int eventcode, ButtonCode keynum, String currentBinding);

        bool IsKeyDown(String name, ref bool isDown);

        void SetSampleTime(float time);
        void CreateMove(int seqNumber, float inputFrametime, bool active);
        void ExtraMouseSample(float frametime, bool active);

        bool WriteUserCmdDeltaToBuffer(ref byte[] buffer, int from, int to, bool isNewCmd);

        void EncodeUserCmdToBuffer(ref byte[] buffer, int slot);
        void DecodeUserCmdFromBuffer(ref byte[] buffer, int slot);


	    void ViewRender(M_VRect rect);
	    void RenderView(M_ViewSetup viewsetup, int nClearFlags, int whatToDraw);
	    void ViewFade(M_ScreenFade screenFade);
	
	    void SetCrosshairAngle(ref M_QAngle angle);

	    void VoiceStatus(int entindex, bool talking);
	    void InstallStringTableCallback(String tableName);
	    void FrameStageNotify(ClientFrameStage curStage);

	    bool DispatchUserMessage(int msgType, byte[] data);

        bool GetPlayerView(ref M_ViewSetup playerView);
    }
}
