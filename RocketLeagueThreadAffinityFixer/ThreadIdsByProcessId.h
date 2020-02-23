#pragma once

#include <Windows.h>
#include <unordered_set>

std::unordered_set<DWORD> getThreadIdsByProcessId(HANDLE hThreadSnap, DWORD processId);
