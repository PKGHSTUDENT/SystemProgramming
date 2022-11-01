#include <windows.h>
#include <iostream>
using namespace std;


HANDLE hStdIn, hStdOut;
BOOL bRead = TRUE;

VOID KeyEventProc(KEY_EVENT_RECORD kir)
{
	cout << "\tKey event record:" << endl;
	cout << "bKeyDown = " << hex << kir.bKeyDown << endl;
	cout << "wRepeatCount = " << dec << kir.wRepeatCount << endl;
	cout << "wVirtualKeyCode = " << hex << kir.wVirtualKeyCode << endl;
	cout << "wVirtualScanCode = " << kir.wVirtualScanCode << endl;
	cout << "uChar.AsciiChar = " << kir.uChar.AsciiChar << endl;
	cout << "dwControlKeyState = " << kir.dwControlKeyState << endl;
	
	if (kir.uChar.AsciiChar == 'q')
		bRead = FALSE;
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
	cout << "\tMouse event record:" << endl << dec;

	cout << "dwMousePosition.X = " << mer.dwMousePosition.X << endl;
	cout << "dwMousePosition.Y = " << mer.dwMousePosition.Y << endl;
	cout << "dwButtonState = " << hex << mer.dwButtonState << endl;
	cout << "dwControlKeyState = " << mer.dwControlKeyState << endl;
	cout << "dwEventFlags = " << mer.dwEventFlags << endl;
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	SetConsoleScreenBufferSize(hStdOut, wbsr.dwSize);
}

int main()
{
	INPUT_RECORD ir;
	DWORD cNumRead;

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);

	if (hStdIn == INVALID_HANDLE_VALUE)
	{
		cout << "Get standard input handle failed." << endl;

		return GetLastError();
	}
		
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		
	if (hStdOut == INVALID_HANDLE_VALUE)
	{
		cout << "Get standard output handle failed." << endl;
		return GetLastError();
	}

	cout << "Begin input event queue processing." << endl;
	cout << "Input 'q' to quit." << endl << endl;
		
	while (bRead)
	{
		WaitForSingleObject(hStdIn, INFINITE);
	
		if (!ReadConsoleInput(
			hStdIn,
			&ir,
			1,
			&cNumRead))
		{
			cout << "Read console input failed." << endl;
			break;
		}
	
		switch (ir.EventType)
		{
		case KEY_EVENT:
			KeyEventProc(ir.Event.KeyEvent);
			break;
		case MOUSE_EVENT:
			MouseEventProc(ir.Event.MouseEvent);
			break;
		case WINDOW_BUFFER_SIZE_EVENT:
			ResizeEventProc(
				ir.Event.WindowBufferSizeEvent);
			break;
		case FOCUS_EVENT:
			break;
		case MENU_EVENT:
			break;
		default:
			cout << "Unknown event type.";
			break;
		}
	}

	return 0;
}