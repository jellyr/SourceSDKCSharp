#include "Stdafx.h"
#include <string>

std::string GetModulePath();

//This resolves C# dll's to the current working dir
class HookAppResolver
{
public:
	HookAppResolver()
	{
		System::AppDomain^ currentDomain = System::AppDomain::CurrentDomain;
		currentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(MyResolveEventHandler);
	}

	static System::Reflection::Assembly^ MyResolveEventHandler(System::Object^ sender, System::ResolveEventArgs^ args)
	{
		auto findName = gcnew System::Reflection::AssemblyName(args->Name);

		for each(System::String^ file in System::IO::Directory::GetFiles(gcnew System::String(GetModulePath().c_str()), "*.dll"))
		{
			try
			{
				System::Reflection::Assembly^ assembly = System::Reflection::Assembly::LoadFile(file);

				auto name = gcnew System::Reflection::AssemblyName(assembly->FullName);

				if (name->Name == findName->Name)
					return assembly;
			}
			catch (System::Exception^)
			{
			}
		}

		return nullptr;
	}
};

static HookAppResolver g_HookAppResolver;