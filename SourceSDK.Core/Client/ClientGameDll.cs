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

        public void VoiceStatus(int entindex, bool talking)
        {
            
        }

        public void InstallStringTableCallback(string tableName)
        {
            
        }

        ClientFrameStage _CurFrameStage;

        public void FrameStageNotify(ClientFrameStage curStage)
        {
	        _CurFrameStage = curStage;

	        switch (curStage)
	        {
	        default:
		        break;

            case ClientFrameStage.FRAME_RENDER_START:
			    // Last thing before rendering, run simulation.
			    OnRenderStart();
		        break;

            case ClientFrameStage.FRAME_RENDER_END:
			    OnRenderEnd();
		        break;

            case ClientFrameStage.FRAME_NET_UPDATE_START:
                //// disabled all recomputations while we update entities
                //C_BaseEntity::EnableAbsRecomputations( false );
                //C_BaseEntity::SetAbsQueriesValid( false );
                //Interpolation_SetLastPacketTimeStamp( engine->GetLastTimeStamp() );
                //partition->SuppressLists( PARTITION_ALL_CLIENT_EDICTS, true );
		        break;

            case ClientFrameStage.FRAME_NET_UPDATE_END:
                //ProcessCacheUsedMaterials();

                //// reenable abs recomputation since now all entities have been updated
                //C_BaseEntity::EnableAbsRecomputations( true );
                //C_BaseEntity::SetAbsQueriesValid( true );
                //partition->SuppressLists( PARTITION_ALL_CLIENT_EDICTS, false );
		        break;

            case ClientFrameStage.FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		        break;

            case ClientFrameStage.FRAME_NET_UPDATE_POSTDATAUPDATE_END:
                //// Let prediction copy off pristine data
                //prediction->PostEntityPacketReceived();
                //HLTVCamera()->PostEntityPacketReceived();
		        break;

            case ClientFrameStage.FRAME_START:
                //// Mark the frame as open for client fx additions
                //SetFXCreationAllowed( true );
                //SetBeamCreationAllowed( true );
                //C_BaseEntity::CheckCLInterpChanged();
		        break;
	        }            
        }

        private void OnRenderEnd()
        {

        }

        private void OnRenderStart()
        {

        }

        public bool DispatchUserMessage(int msgType, byte[] data)
        {
            return false;
        }

        public bool GetPlayerView(ref M_ViewSetup playerView)
        {
            return false;
        }
    }
}
