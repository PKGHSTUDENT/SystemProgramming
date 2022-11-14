#include <windows.h>

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

extern "C" __declspec(dllexport) int count = 0;

extern "C" __declspec(dllexport) int Add(int n)
{
	count += n;
	return count;
}

extern "C" __declspec(dllexport) int Sub(int n)
{
	count -= n;
	return count;
}