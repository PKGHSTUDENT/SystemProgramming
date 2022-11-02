#include <windows.h>
#include <stdio.h>

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow();

int main()
{
	HWND hWindow = NULL;
	HDC hDeviceContext;
	HPEN hPen;
	HGDIOBJ hObject;

	hWindow = GetConsoleWindow();
	if (hWindow == NULL)
	{
		printf("Get console window failed.\n");
		return 1;
	}
	else
		printf("Get console window is done.\n");
	
	hDeviceContext = GetDC(hWindow);
	
	hPen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
	
	hObject = SelectObject(hDeviceContext, hPen);
	
	MoveToEx(hDeviceContext, 100, 100, NULL);
	LineTo(hDeviceContext, 500, 100);
	SelectObject(hDeviceContext, hObject);
	DeleteObject(hPen);
	ReleaseDC(hWindow, hDeviceContext);

	system("pause");

	return 0;
}