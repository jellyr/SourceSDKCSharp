#include "Stdafx.h"
#include "CVarWrapper.h"




ConVarWrapperCallback::ConVarWrapperCallback(ConVarWrapper *pWrapper)
{
	m_pWrapper = pWrapper;
}

void ConVarWrapperCallback::ValueUpdated(String^ value)
{
	std::string szValue = marshal_as<std::string>(value);
	m_pWrapper->SetValue(szValue.c_str());
}



ConVarWrapper::ConVarWrapper(IConVariable^ conVar)
{
	m_szName = marshal_as<std::string>(conVar->Name);
	m_szHelp = marshal_as<std::string>(conVar->HelpString);

	std::string szDefault = marshal_as<std::string>(conVar->DefaultValue);
	int flags = (int)conVar->Flags;

	Create("", szDefault.c_str(), flags, "", false, 0.0, false, 0.0, &ConVarWrapper::Update);

	auto callback = gcnew ConVarWrapperCallback(this);
	conVar->ValueUpdated = gcnew ValueUpdatedHandler(callback, &ConVarWrapperCallback::ValueUpdated);

	m_ConVar = conVar;
}

IConVariable^ ConVarWrapper::Get()
{
	return m_ConVar;
}

void ConVarWrapper::Update(const char* pOldValue)
{
	String^ val = gcnew String(GetString());
	m_ConVar->Value = val;
}

void ConVarWrapper::Update(IConVar *var, const char *pOldValue, float flOldValue)
{
	ConVarWrapper* pCVW = dynamic_cast<ConVarWrapper*>(var);

	if (pCVW)
		pCVW->Update(pOldValue);
}

const char *ConVarWrapper::GetName( void ) const
{
	return m_szName.c_str();
}

const char *ConVarWrapper::GetHelpText( void ) const
{
	return m_szHelp.c_str();
}