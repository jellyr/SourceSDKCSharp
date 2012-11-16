#pragma once

#include "iprediction.h"

class CSourceSDKPrediction : public IPrediction
{
public:
	void Init() override;
	void Shutdown() override;

	// Run prediction
	void Update(int startframe,	bool validframe, int incoming_acknowledged,	int outgoing_command) override;

	// We are about to get a network update from the server.  We know the update #, so we can pull any
	//  data purely predicted on the client side and transfer it to the new from data state.
	void PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) override;
	void PostEntityPacketReceived() override;
	void PostNetworkDataReceived(int commands_acknowledged) override;

	void OnReceivedUncompressedPacket() override;

	// The engine needs to be able to access a few predicted values
	void GetViewOrigin(Vector& org) override;
	void SetViewOrigin(Vector& org) override;
	void GetViewAngles(QAngle& ang) override;
	void SetViewAngles(QAngle& ang) override;
	void GetLocalViewAngles(QAngle& ang) override;
	void SetLocalViewAngles(QAngle& ang) override;
};