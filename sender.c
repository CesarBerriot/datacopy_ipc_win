#include <stdio.h>
#include <windows.h>
#include "shared.h"

int main(void)
{	HWND receiver_window = NULL;
	do
	{	receiver_window = FindWindowA(WINDOW_CLASS_NAME, NULL);
		if(!receiver_window)
		{	puts("couldn't find the receiver window. retrying in 5 seconds.");
			Sleep(5000);
		}
	} while(!receiver_window);

	puts("receiver window found. you can start typing messages (max 30 characters).");

	for(;;)
	{	fflush(stdin);
		char input_buffer[31] = { '\0' };
		do
		{	scanf("%30[^\n]", input_buffer);
			fseek(stdin, 0, SEEK_END);
		} while(!strlen(input_buffer));

		printf("sending message : '%s'\n", input_buffer);

		int message_buffer_length = 16 + strlen(input_buffer) + 1;
		BYTE * message_buffer = malloc(message_buffer_length);
		memcpy(message_buffer, MESSAGE_VALIDATION_GUID, 16);
		memcpy(message_buffer + 16, input_buffer, strlen(input_buffer) + 1);

		COPYDATASTRUCT data = { 0 };
		data.lpData = message_buffer;
		data.cbData = message_buffer_length;

		if(SendMessageA(receiver_window, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&data) != TRUE)
			if(GetLastError() == ERROR_INVALID_WINDOW_HANDLE)
				fail("the receiver window has been closed");
			else
				fail("the receiver window failed to process the sent WM_COPYDATA message. win32 error code : %lu.", GetLastError());
	}
}
