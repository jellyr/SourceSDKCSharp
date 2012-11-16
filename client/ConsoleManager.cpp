#include "Stdafx.h"
#include <msclr\marshal_cppstd.h>

#include "ConsoleManager.h"
#include "tier1/convar.h"
#include <string>

#include "CVarWrapper.h"
#include "ConCommandWrapper.h"
#include "Color.h"

using namespace SourceSDK;
using namespace msclr::interop;


using namespace SourceSDK;

static void Callback()
{
	int a=1;
}

ConCommand test("test", &Callback);


ConsoleManager::ConsoleManager(ICvar* pCvar)
{
	m_pCvar = pCvar;
	m_DllIdentifier = m_pCvar->AllocateDLLIdentifier();
	m_pCvar->RegisterConCommand(&test);
}

ConsoleManager::~ConsoleManager()
{
	m_pCvar->UnregisterConCommands(m_DllIdentifier);
}

void ConsoleManager::Register(IConCommand^ conCommand)
{
	m_pCvar->RegisterConCommand(new ConCommandWrapper(conCommand));
}

void ConsoleManager::Unregister(IConCommand^ conCommand)
{
	std::string szName = marshal_as<std::string>(conCommand->Name);
	ConCommandWrapper* pCCW = dynamic_cast<ConCommandWrapper*>(m_pCvar->FindCommand(szName.c_str()));

	if (pCCW)
		m_pCvar->UnregisterConCommand(pCCW);
}


void ConsoleManager::Register(IConVariable^ conVariable)
{
	m_pCvar->RegisterConCommand(new ConVarWrapper(conVariable));
}

void ConsoleManager::Unregister(IConVariable^ conVariable)
{
	std::string szName = marshal_as<std::string>(conVariable->Name);
	ConVarWrapper* pCVW = dynamic_cast<ConVarWrapper*>(m_pCvar->FindVar(szName.c_str()));

	if (pCVW)
		m_pCvar->UnregisterConCommand(pCVW);
}


List<IConCommand^>^ ConsoleManager::GetConCommands()
{
	auto ret = gcnew List<IConCommand^>();
	auto cmds = m_pCvar->GetCommands();

	while (cmds)
	{
		if (cmds->IsCommand())
		{
			ConCommandWrapper* pCCW = dynamic_cast<ConCommandWrapper*>(cmds);

			if (pCCW)
			{
				ret->Add(pCCW->Get());
			}
			else
			{
				ConCommand* pCC = dynamic_cast<ConCommand*>(cmds);

				if (pCC)
					ret->Add(gcnew ConCommandNativeWrapper(pCC));
			}
		}

		cmds = cmds->GetNext();
	}

	return ret;
}

List<IConVariable^>^ ConsoleManager::GetConVariables()
{
	auto ret = gcnew List<IConVariable^>();
	auto cmds = m_pCvar->GetCommands();

	while (cmds)
	{
		if (!cmds->IsCommand())
		{
			ConVarWrapper* pCVW = dynamic_cast<ConVarWrapper*>(cmds);

			if (pCVW)
			{
				ret->Add(pCVW->Get());
			}
			else
			{
				ConVar* pCV = dynamic_cast<ConVar*>(cmds);

				if (pCV)
					ret->Add(gcnew ConVariableNativeWrapper(pCV));
			}
		}

		cmds = cmds->GetNext();
	}

	return ret;
}


IConCommand^ ConsoleManager::FindConCommand(System::String^ name)
{
	std::string szName = marshal_as<std::string>(name);
	ConCommandWrapper* pCCW = dynamic_cast<ConCommandWrapper*>(m_pCvar->FindCommand(szName.c_str()));

	if (pCCW)
		return pCCW->Get();

	return nullptr;
}

IConVariable^ ConsoleManager::FindConVariable(System::String^ name)
{
	std::string szName = marshal_as<std::string>(name);
	ConVarWrapper* pCVW = dynamic_cast<ConVarWrapper*>(m_pCvar->FindVar(szName.c_str()));

	if (pCVW)
		return pCVW->Get();

	return nullptr;
}

void ConsoleManager::Write(String^ line)
{
	std::string szLine = marshal_as<std::string>(line);
	m_pCvar->ConsolePrintf("%s", szLine.c_str());
}

void ConsoleManager::Write(System::Drawing::Color color, String^ line)
{
	std::string szLine = marshal_as<std::string>(line);

	int col = color.ToArgb();
	col = (col << 8) + ((col >> 24)&0xFF); //argb to rgba

	Color c;
	c.SetRawColor(col);

	m_pCvar->ConsoleColorPrintf(c, "%s", szLine.c_str());
}

void ConsoleManager::WriteLine(String^ line)
{
	std::string szLine = marshal_as<std::string>(line);
	m_pCvar->ConsolePrintf("%s\n", szLine.c_str());
}

void ConsoleManager::WriteLine(System::Drawing::Color color, String^ line)
{
	std::string szLine = marshal_as<std::string>(line);

	int col = color.ToArgb();
	col = (col << 8) + ((col >> 24)&0xFF); //argb to rgba

	Color c;
	c.SetRawColor(col);

	m_pCvar->ConsoleColorPrintf(c, "%s\n", szLine.c_str());
}