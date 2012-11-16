#pragma once

#include "basehandle.h"

using namespace SourceSDK::Core::Interfaces::Shared;

ref class HandleWrapper : public IEntityHandle
{
public:
	HandleWrapper(CBaseHandle &handle)
		: m_Handle(handle)
	{
	}

private:
	CBaseHandle &m_Handle;
};