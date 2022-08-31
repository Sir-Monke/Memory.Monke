#include "stdafx.h"
#include <iostream>
#include "mem.h"
#include "hook.h"
#include "glDraw.h"
#include "gltext.h"
#include "esp.h"

//Credits: @Rake

using namespace std;

//Attach to Running proc
uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

//Setting up the basics of the hack and esp
bool bhealth = false, bammo = false, brecoil = false, barmor = false, bgrenade = false, bnoclip = false;

//Template Function
typedef BOOL(__stdcall* twglSwapBuffers) (HDC hDc);

//I mean kinda obvious what this is doing
//Calling the class "GL" from the file gltext and setting the height and size of the text
GL::Font glFont;
const int FONT_HEIGHT = 15;
const int FONT_WIDTH = 9;

twglSwapBuffers owglSwapBuffers;
twglSwapBuffers wglSwapBuffersGateway;

typedef int(__cdecl* _getCrossHairEntity)();
_getCrossHairEntity getCrossEntity = (_getCrossHairEntity)0x4607C0;

ESP esp;


//Setting up a VERY NICE VOID so i can draw shiz "esp"
void Draw()
{
	HDC currentHDC = wglGetCurrentDC();

	if (!glFont.bBuilt || currentHDC != glFont.hdc)
	{
		glFont.Build(FONT_HEIGHT);
	}

	GL::SetupOrtho();
	esp.Draw(glFont);
	GL::RestoreGL();
}

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
	if (GetAsyncKeyState(VK_NUMPAD1) & 1) 
	{
		bhealth = !bhealth; //Setting the toggle to true 
	}

	if (GetAsyncKeyState(VK_NUMPAD2) & 1)
	{
		bammo = !bammo; //Setting the toggle to true
	}

	if (GetAsyncKeyState(VK_NUMPAD3) & 1)
	{
		barmor = !barmor; //Setting the toggle to true
	}

	if (GetAsyncKeyState(VK_NUMPAD4) & 1)
	{
		bgrenade = !bgrenade;
	}

	if (GetAsyncKeyState(VK_NUMPAD5) & 1)
	{
		bnoclip = !bnoclip;
		
		if (bnoclip) 
		{
			*(int*)mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x82 }) = 4;
		}
		if (!bnoclip) 
		{
			*(int*)mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x82 }) = 0;
		}
	}

	//no recoil NOP
	if (GetAsyncKeyState(VK_NUMPAD6) & 1)
	{
		brecoil = !brecoil; //Setting the toggle to true

		if (brecoil)
		{
			mem::Nop((BYTE*)(moduleBase + 0x63786), 10);
		}

		else
		{
			//50 8D 4C 24 1C 51 8B CE FF D2 the original stack setup and call
			mem::Patch((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
		}
	}

	//need to use uintptr_t for pointer arithmetic later
	uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x10F4F4);

	//continuous writes / freeze
	if (*localPlayerPtr)
	{
		if (bhealth)
		{
			*(int*)(*localPlayerPtr + 0xF8) = 500;
		}

		if (bammo)
		{
			*(int*)mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x374, 0x14, 0x0 }) = 100;
		}

		if (bgrenade) 
		{
			*(int*)mem::FindDMAAddy(moduleBase + 0x10F4F4, { 0x158 }) = 100;
		}
	}

	Draw();

	return wglSwapBuffersGateway(hDc);
}

DWORD WINAPI MainHack(HMODULE hModule)
{
	//Create Console
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	std::cout << "    The Memory Monke   \n";
	std::cout << "-----------------------\n";
	std::cout << "Health  --> [NumPad1]  \n";
	std::cout << "Ammo    --> [NumPad2]  \n";
	std::cout << "Armor   --> [NumPad3]  \n";
	std::cout << "Grenade --> [NumPad4]  \n";
	std::cout << "Noclip  --> [NumPad5]  \n";
	std::cout << "Recoil  --> [NumPad6]  \n";

	// Hook
	Hook SwapBuffersHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkwglSwapBuffers, (BYTE*)&wglSwapBuffersGateway, 5);
	SwapBuffersHook.Enable();

	bool bexit = false;

	while (true) 
	{
		if (GetAsyncKeyState(VK_NUMPAD0) & 1)
		{
			Sleep(5);
			SwapBuffersHook.Disable();
			break;
		}
		Sleep(5);
	}

	//This will close remove the .ddl from the game although the mem values will stay the same due to manual mem change

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainHack, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}










//                
//                               __------__
//                   1      0  /~          ~\
//                             |    //^\\//^\|   1       0           1
//                      0    /~~\  ||  o| |o|:~\
//                          | |6   ||___|_|_||:|    1         0         0
//                      1   \__.  /      o  \/'
//                  0         |   (       O   )          1        0
//                   /~~~~\  1 `\  \         /    1         0
//                  | |~~\ |     )  ~------~`\
//                 /' |  | |   /     ____ /~~~)\       1          0       1
//                (_/' 1 | | |     /'    |    ( |   0
//                       | | |     \    /   __)/ \          1
//                  1    \  \ \      \/    /' \   `\               0
//                    0    \  \|\        /   | |\___|
//                     0     \ |  \____/     | |       1             1         0 
//                  1     1  /^~>  \        _/ <    0        1
//                    0     |  |         \       \
//                       0  |  | \        \        \                 1 
//                   1    1 -^-\  \        |        )         1
//                    0          `\_______/^\______/    0                1       0