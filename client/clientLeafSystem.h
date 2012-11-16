#pragma once

#include "tier0/platform.h"
#include "engine/iclientleafsystem.h"


class CSourceSDKClientLeafSystem : public IClientLeafSystemEngine
{
public:
	// Adds and removes renderables from the leaf lists
	// CreateRenderableHandle stores the handle inside pRenderable.
	void CreateRenderableHandle( IClientRenderable* pRenderable, bool bIsStaticProp = false ) override;
	void RemoveRenderable( ClientRenderHandle_t handle ) override;
	void AddRenderableToLeaves( ClientRenderHandle_t renderable, int nLeafCount, unsigned short *pLeaves ) override;
	void ChangeRenderableRenderGroup( ClientRenderHandle_t handle, RenderGroup_t group ) override;
};