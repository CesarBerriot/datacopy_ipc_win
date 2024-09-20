#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <signal.h>
#include "shared.h"

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
void handle_interrupt(void);

int main(void)
{	signal(SIGINT, (void(*)(int))handle_interrupt);
	WNDCLASSA window_class = { 0 };
	window_class.lpszClassName = WINDOW_CLASS_NAME;
	window_class.lpfnWndProc = window_procedure;
	fail_if(!RegisterClassA(&window_class), "failed to register the window class. win32 error code : %lu", GetLastError());
	fail_if(FindWindowA(WINDOW_CLASS_NAME, NULL), "an instance of the receiver is already running");
	HWND window = CreateWindowA(WINDOW_CLASS_NAME, "DataCopyIpcWin", 0, 0, 0, 0, 0, NULL, NULL, NULL, 0);
	fail_if(!window, "failed to create the receiver window");
	puts("listening for messages...");
	//signal(SIGINT);
	bool loop = true;
	MSG message;
	while(loop)
		switch(GetMessageA(&message, window, 0, 0))
		{	default: DispatchMessageA(&message); break;
			case 0 : loop = false; break;
			case -1 : fail("message loop failed. win32 error code : %lu", GetLastError());
		}
	printf("Hello, World!\n");
	return 0;
}

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{	switch(message)
	{	case WM_COPYDATA:
		{	COPYDATASTRUCT info = *(COPYDATASTRUCT*)lparam;

			if(info.cbData < 17)
			{	fputs("received a message-less data buffer\n", stderr);
				return FALSE;
			}

			BYTE * raw_data = info.lpData;
			BYTE * validation_guid = &raw_data[0];
			char * message = (char*)&raw_data[16];

			if(memcmp(validation_guid, MESSAGE_VALIDATION_GUID, 16))
			{	fputs("received a data buffer containing an invalid validation guid\n", stderr);
				return FALSE;
			}

			printf("received message : '%s'\n", message);
			return TRUE;
		}
	}
	return DefWindowProcA(window, message, wparam, lparam);
}

void handle_interrupt(void)
{	puts("execution interrupted");
	signal(SIGINT, SIG_DFL);
	raise(SIGINT);
}
