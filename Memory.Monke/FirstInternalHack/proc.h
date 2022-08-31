#pragma once
#include <vector>
#include <windows.h>
#include <TlHelp32.h>

//This is a pice of code that allows me to atach my .dll to the proc
DWORD GetProcId(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);