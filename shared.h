#pragma once

#include <stdnoreturn.h>
#include <minwindef.h>

extern char WINDOW_CLASS_NAME[];
extern BYTE MESSAGE_VALIDATION_GUID[16];

#define fail_if(condition, ...) do { if(condition) fail(__VA_ARGS__); } while(0)

noreturn void fail(char format[], ...);
