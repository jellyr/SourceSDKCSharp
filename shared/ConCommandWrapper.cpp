#include "Stdafx.h"


#include "ConCommandWrapper.h"
#include "tier1/convar.h"
#include <string>


using namespace SourceSDK;
using namespace msclr::interop;
using namespace SourceSDK;


static void Callback()
{
}

// sizeof(ConCommand) = 36

ConCommandWrapper::ConCommandWrapper(IConCommand^ conCommand)
	: ConCommand("", &Callback, "", (int)conCommand->Flags)
{
	m_szName = marshal_as<std::string>(conCommand->Name);
	m_szHelp = marshal_as<std::string>(conCommand->HelpString);

	//ConCommandWrapper::Create(m_szName.c_str(), m_szHelp.c_str(), (int)conCommand->Flags);
	m_ConCommand = conCommand;
}

bool ConCommandWrapper::IsCommand() const
{
	return true;
}

bool ConCommandWrapper::CanAutoComplete()
{
	return true;
}

int ConCommandWrapper::AutoCompleteSuggest(const char *partial, CUtlVector<CUtlString> &commands)
{
	//Not working atm. Causes a crash :(
	return 0;

	//String^ partal = gcnew String(partial);
	//List<String^>^ list = gcnew List<String^>();
	//m_ConCommand->AutoComplete(partal, list);

	//for each (String^ i in list)
	//{
	//	std::string szCommand = marshal_as<std::string>(i);
	//	commands.AddToTail(szCommand.c_str());
	//}

	//return list->Count;
}

void ConCommandWrapper::Dispatch(const CCommand &command)
{
	auto args = gcnew List<String^>();

	for (int x=0; x<command.ArgC(); ++x)
		args->Add(gcnew String(command[x]));

	m_ConCommand->Execute(args->ToArray());
}

const char* ConCommandWrapper::GetName( void ) const
{
	return m_szName.c_str();
}

const char* ConCommandWrapper::GetHelpText( void ) const
{
	return m_szHelp.c_str();
}

IConCommand^ ConCommandWrapper::Get()
{
	return m_ConCommand;
}