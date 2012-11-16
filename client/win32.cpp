#include <Windows.h>
#include <string>
#include <Psapi.h>

std::string GetModulePath()
{
	HMODULE handle = GetModuleHandle("client.dll");

	char buff[255];
	GetModuleFileName(handle, buff, 255);

	std::string ret(buff);

	while (ret.back() != '\\')
		ret.erase(ret.end()-1);

	return ret;
}
