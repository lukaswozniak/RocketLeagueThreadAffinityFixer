#pragma once

#include <Windows.h>

HANDLE openThread(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId);
