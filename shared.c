#include "shared.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char WINDOW_CLASS_NAME[] = "datacopy_ipc_win window class {EAD63431-D6DC-49F9-9604-D78F6133F8F5}";

BYTE MESSAGE_VALIDATION_GUID[16] = { 0xe6, 0x6a, 0x7d, 0x25, 0xca, 0xb5, 0x4d, 0x0e, 0x83, 0x26, 0x4, 0xd4, 0x7d, 0xd2, 0x9c, 0xe };

noreturn void fail(char format[], ...)
{	fputs("fatal error : ", stderr);
	va_list arguments;
	va_start(arguments, format);
	vfprintf(stderr, format, arguments);
	va_end(arguments);
	fputc('\n', stderr);
	exit(EXIT_FAILURE);
}
