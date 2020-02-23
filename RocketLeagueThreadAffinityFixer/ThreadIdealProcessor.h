#pragma once

#include <Windows.h>

DWORD getThreadIdealProcessorNum(HANDLE threadHandle);
void setThreadIdealProcessorNum(HANDLE threadHandle, DWORD idealProcNum);
