#include "pch.h"

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" int count = -5;

extern "C" int Add(int n)
{
	count += n;
	return count;
}

extern "C" int Sub(int n)
{
	count -= n;
	return count;
}