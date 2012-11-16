#include "Stdafx.h"
#include "prediction.h"



void CSourceSDKPrediction::Init()
{
}

void CSourceSDKPrediction::Shutdown()
{
}

void CSourceSDKPrediction::Update(int startframe,	bool validframe, int incoming_acknowledged,	int outgoing_command)
{
}

void CSourceSDKPrediction::PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet)
{
}

void CSourceSDKPrediction::PostEntityPacketReceived()
{
}

void CSourceSDKPrediction::PostNetworkDataReceived(int commands_acknowledged)
{
}

void CSourceSDKPrediction::OnReceivedUncompressedPacket()
{
}

void CSourceSDKPrediction::GetViewOrigin(Vector& org)
{
}

void CSourceSDKPrediction::SetViewOrigin(Vector& org)
{
}

void CSourceSDKPrediction::GetViewAngles(QAngle& ang)
{
}

void CSourceSDKPrediction::SetViewAngles(QAngle& ang)
{
}

void CSourceSDKPrediction::GetLocalViewAngles(QAngle& ang)
{
}

void CSourceSDKPrediction::SetLocalViewAngles(QAngle& ang)
{
}
