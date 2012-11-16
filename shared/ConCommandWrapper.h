#pragma once

#include "tier1/convar.h"
using namespace SourceSDK::Core::Interfaces::Shared;

namespace SourceSDK
{


class ConCommandWrapper : public ConCommand
{
public:
	ConCommandWrapper(IConCommand^ conCommand);

	virtual bool IsCommand() const override;
	virtual bool CanAutoComplete() override;

	virtual int AutoCompleteSuggest(const char *partial, CUtlVector<CUtlString> &commands) override;

	virtual const char *GetName( void ) const override;
	virtual const char *GetHelpText( void ) const override;

	virtual void Dispatch(const CCommand &command) override;

	IConCommand^ Get();

private:
	std::string m_szName;
	std::string m_szHelp;
	gcroot<IConCommand^> m_ConCommand;
};

public ref class  ConCommandNativeWrapper : public IConCommand
{
public:
	ConCommandNativeWrapper(ConCommand *pConCommand)
	{
		m_pConCommand = pConCommand;
	}

	virtual property String^ Name
	{
		String^ get() sealed
		{
			return gcnew String(m_pConCommand->GetName());
		}
	}

	virtual property String^ HelpString
	{
		String^ get() sealed
		{
			return gcnew String(m_pConCommand->GetHelpText());
		}
	}

	virtual property CVarFlags Flags
	{
		CVarFlags get() sealed
		{
			return CVarFlags::NONE;
		}
	}

	virtual void AutoComplete(String^ partial, List<String^>^ suggetions) sealed
	{
		if (!m_pConCommand->CanAutoComplete())
			return;

		std::string szPartial = marshal_as<std::string>(partial);

		CUtlVector<CUtlString> commands;
		int ret = m_pConCommand->AutoCompleteSuggest(szPartial.c_str(), commands);

		for (int x=0; x<ret; ++x)
			suggetions->Add(gcnew String(commands[x].Get()));
	}

	virtual void Execute(cli::array<String^,1>^ args) sealed
	{
		int count = args->Length;

		if (count == 0)
		{
			CCommand command(0, NULL);
			m_pConCommand->Dispatch(command);
		}
		else
		{
			std::vector<std::string> vItems;
			const char** szArgs = new const char*[count];

			int x=0;
			for each (auto a in args)
			{
				vItems.push_back(marshal_as<std::string>(a));
				szArgs[x] = vItems[x].c_str();
				x++;
			}

			CCommand command(count, szArgs);
			m_pConCommand->Dispatch(command);

			delete []szArgs;
		}
	}

	virtual property bool Managed
	{
		bool get() sealed
		{
			return false;
		}
	}

private:
	ConCommand* m_pConCommand;
};






}