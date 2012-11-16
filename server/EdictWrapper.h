#pragma once

#include "edict.h"

using namespace System;
using namespace SourceSDK::Core::Interfaces::Shared;

ref class EdictWrapper : public IEdict
{
public:
	EdictWrapper(const edict_t edict)
	{
		m_bDelete = true;
		m_pEdict = new edict_t(edict);
	}

	EdictWrapper(edict_t* edict)
	{
		m_bDelete = false;
		m_pEdict = edict;
	}

	~EdictWrapper()
	{
		if (m_bDelete)
			delete m_pEdict;
	}

	virtual property String^ ClassName
	{ 
		String^ get()
		{
			return gcnew String(m_pEdict->GetClassName());
		}
	}

	edict_t* Get()
	{
		return m_pEdict;
	}

private:
	bool m_bDelete;
	edict_t *m_pEdict;
};