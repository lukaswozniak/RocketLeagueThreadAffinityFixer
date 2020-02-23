#include "createToolhelp32Snapshot.h"
#include "throwIf.h"

HANDLE createToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID)
{
	return throwIfNull(CreateToolhelp32Snapshot(dwFlags, th32ProcessID), "CreateToolhelp32Snapshot");
}
