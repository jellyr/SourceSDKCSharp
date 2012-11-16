#pragma once

#include "game/client/IGameClientExports.h"


class CSourceSDKGameClientExports : public IGameClientExports
{
public:
	bool IsPlayerGameVoiceMuted(int playerIndex) override;
	void MutePlayerGameVoice(int playerIndex) override;
	void UnmutePlayerGameVoice(int playerIndex) override;

	void OnGameUIActivated() override;
	void OnGameUIHidden() override;
};