#pragma once

#include "icvar.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace SourceSDK::Core::Interfaces::Shared;

namespace SourceSDK
{
	
	public ref class ConsoleManager : public NI_ConsoleManager
	{
	public:
		ConsoleManager(ICvar* pCvar);
		~ConsoleManager();

		virtual void Register(IConCommand^ conCommand);
		virtual void Unregister(IConCommand^ conCommand);

		virtual void Register(IConVariable^ conVariable);
		virtual void Unregister(IConVariable^ conVariable);

		virtual List<IConCommand^>^ GetConCommands();
		virtual List<IConVariable^>^ GetConVariables();

		virtual IConCommand^ FindConCommand(String^ name);
		virtual IConVariable^ FindConVariable(String^ name);

		virtual void Write(String^ line);
		virtual void Write(System::Drawing::Color color, String^ line);

		virtual void WriteLine(String^ line);
		virtual void WriteLine(System::Drawing::Color color, String^ line);

	private:
		CVarDLLIdentifier_t m_DllIdentifier;
		ICvar* m_pCvar;
	};
}