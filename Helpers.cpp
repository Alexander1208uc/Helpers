#include "Helpers.h"
#include <vector>
#include <Psapi.h>

//MISCELLANEOUS
void Helpers::Log(char* szMessage)
{
	std::cout << "[+] " << szMessage << std::endl;
}
void Helpers::LogChar(char szMessage)
{
	std::cout << "[+] " << szMessage << std::endl;
}
void Helpers::LogInt(char* szMessage, int iAdress)
{
	std::cout << "[+] " << szMessage << ": " << std::defaultfloat << iAdress << std::endl;
}
void Helpers::LogAddress(char* szName, int64_t iAddress)
{
	std::cout << "[+] " << szName << ": 0x" << std::hex << iAddress << std::endl;
}
void Helpers::LogFloat(char* szName, float fValue)
{
	std::cout << "[+] " << szName << ": " << std::defaultfloat << fValue << std::endl;
}
void Helpers::LogString(char* szName, std::string sValue)
{
	std::cout << "[+] " << szName << ": " << sValue << std::endl;
}
void Helpers::LogError(char* szMessage)
{
	std::cout << "[Error] " << szMessage << std::endl;
}
void Helpers::LogSuccess(char* szMessage)
{
	std::cout << "[Success] " << szMessage << std::endl;
}

// CONVERTERS
std::string Helpers::VariableText(const char* format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	char buffer[2048];
	vsprintf(buffer, format, argptr);

	va_end(argptr);

	return buffer;
}

void Helpers::GetResolution(UINT horizontal, UINT vertical, HWND window)
{
	RECT desktop;
	GetWindowRect(window, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

DWORD Helpers::FindPattern(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;    //one ?
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}
	return NULL;
}