#pragma once

#include <msclr\marshal_cppstd.h>
#include <gcroot.h>

#include "tier1/convar.h"
#include <string>

using namespace SourceSDK;
using namespace System;
using namespace System::Collections::Generic;
using namespace SourceSDK::Core::Interfaces::Shared;
using namespace msclr::interop;

namespace SourceSDK
{
	class ConVarWrapper;

	ref class ConVarWrapperCallback
	{
	public:
		ConVarWrapperCallback(ConVarWrapper *pWrapper);
		void ValueUpdated(String^ value);

		ConVarWrapper *m_pWrapper;
	};

	class ConVarWrapper : public ConVar
	{
	public:
		ConVarWrapper(IConVariable^ conVar);
		IConVariable^ Get();

	protected:
		void Update(const char* pOldValue);
		static void Update(IConVar *var, const char *pOldValue, float flOldValue);

		virtual const char *GetName( void ) const override;
		virtual const char *GetHelpText( void ) const override;

	private:
		std::string m_szName;
		std::string m_szHelp;

		gcroot<IConVariable^> m_ConVar;
	};



	public ref class ConVariableNativeWrapper : public IConVariable
	{
	public:
		ConVariableNativeWrapper(ConVar* pConVar)
		{
			m_pConVar = pConVar;
		}

		virtual property String^ Name
		{
			String^ get() sealed
			{
				return gcnew String(m_pConVar->GetName());
			}
		}

		virtual property String^ HelpString
		{
			String^ get() sealed
			{
				return gcnew String(m_pConVar->GetHelpText());
			}
		}

		virtual property CVarFlags Flags
		{
			CVarFlags get() sealed
			{
				return CVarFlags::NONE;
			}
		}

		virtual property String^ Value
		{
			String^ get() sealed
			{
				return gcnew String(m_pConVar->GetString());
			}

			void set(String^ value) sealed
			{
				std::string szValue = marshal_as<std::string>(value);
				m_pConVar->SetValue(szValue.c_str());
			}
		}

		virtual property String^ DefaultValue
		{
			String^ get() sealed
			{
				return gcnew String(m_pConVar->GetDefault());
			}
		}

		virtual property bool Managed
		{
			bool get() sealed
			{
				return false;
			}
		}

		virtual property ValueUpdatedHandler^ ValueUpdated
		{
			void set(ValueUpdatedHandler^) sealed
			{
			}
		}

	private:
		ConVar *m_pConVar;
	};




}