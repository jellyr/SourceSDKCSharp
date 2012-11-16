#pragma once

#include "edict.h"

using namespace System;
using namespace SourceSDK::Core::Interfaces::Shared;

ref class EdictWrapper : public IEdict
{
public:
	EdictWrapper(const edict_t edict)
	{
		m_pEdict = new edict_t(edict);
	}

	~EdictWrapper()
	{
		delete m_pEdict;
	}

	virtual property String^ ClassName
	{ 
		String^ get()
		{
			return gcnew String(m_pEdict->GetClassName());
		}
	}

private:
	edict_t *m_pEdict;
};