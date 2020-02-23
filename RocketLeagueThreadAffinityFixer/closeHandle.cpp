#include "closeHandle.h"

void closeHandle(HANDLE handle) noexcept
{
	if (handle != NULL)
	{
		try { CloseHandle(handle); } catch (...) {}
	}
}
