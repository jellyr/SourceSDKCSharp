using SourceSDK.Core.Interfaces.Client;
using SourceSDK.Core.Interfaces.Shared;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SourceSDK.Core.Client
{
    [Export(typeof(M_IClientGameDll))]
    class ClientGameDll : M_IClientGameDll
    {
        IEntityManagerClient _EntManager;

        [ImportingConstructor]
        public ClientGameDll(IEntityManagerClient entManager)
        {
            _EntManager = entManager;
        }

        public void PostInit()
        {
            
        }

        public void Shutdown()
        {
            
        }

        public void LevelInitPreEntity(string mapName)
        {
            
        }

        public void LevelInitPostEntity()
        {
            
        }

        public void LevelShutdown()
        {
            
        }

        public IClientClass[] GetAllClasses()
        {
            return _EntManager.ClientClasses;
        }

        public int HudVidinit()
        {
            return 0;
        }

        public void HudProcessInput(bool active)
        {
            
        }

        public void HudUpdate(bool active)
        {
            
        }

        public void HudReset()
        {
            
        }

        public void HudText(string message)
        {
            
        }

        public void OnActiveMouse()
        {
            
        }

        public void OnDeactiveMouse()
        {
            
        }

        public void OnAccumlate()
        {
            
        }

        public void OnClearStates()
        {
            
        }

        public int OnKeyEvent(int eventcode, ButtonCode keynum, string currentBinding)
        {
            return 0;
        }

        public bool IsKeyDown(string name, ref bool isDown)
        {
            return false;
        }

        public void SetSampleTime(float time)
        {
            
        }

        public void CreateMove(int seqNumber, float inputFrametime, bool active)
        {
            
        }

        public void ExtraMouseSample(float frametime, bool active)
        {
            
        }

        public bool WriteUserCmdDeltaToBuffer(ref byte[] buffer, int from, int to, bool isNewCmd)
        {
            return false;
        }

        public void EncodeUserCmdToBuffer(ref byte[] buffer, int slot)
        {
            
        }

        public void DecodeUserCmdFromBuffer(ref byte[] buffer, int slot)
        {
            
        }

        public void ViewRender(M_VRect rect)
        {
            
        }

        public void RenderView(M_ViewSetup viewsetup, int nClearFlags, int whatToDraw)
        {
            
        }

        public void ViewFade(M_ScreenFade screenFade)
        {
            
        }

        public void SetCrosshairAngle(ref M_QAngle angle)
        {
            
        }

        public void InitSprite(IEngineSprite sprite, string loadname)
        {
            
        }

        public void ShutdownSprite(IEngineSprite sprite)
        {
            
        }

        public int GetSpriteSize()
        {
            return 0;
        }

        public void VoiceStatus(int entindex, bool talking)
        {
            
        }

        public void InstallStringTableCallback(string tableName)
        {
            
        }

        public void FrameStageNotify(ClientFrameStage curStage)
        {
            
        }

        public bool DispatchUserMessage(int msgType, byte[] data)
        {
            return false;
        }

        public IStandardRecvProxies[] GetStandardRecvProxies()
        {
            return null;
        }

        public bool GetPlayerView(ref M_ViewSetup playerView)
        {
            return false;
        }
    }
}
