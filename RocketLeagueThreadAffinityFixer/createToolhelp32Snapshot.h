#pragma once
#include <Windows.h>
#include <TlHelp32.h>

HANDLE createToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID);
