#include "openThread.h"
#include "throwIf.h"

HANDLE openThread(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId)
{
	return throwIfNull(OpenThread(dwDesiredAccess, bInheritHandle, dwThreadId), "OpenThread");
}
