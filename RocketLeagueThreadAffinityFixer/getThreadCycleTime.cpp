#include "getThreadCycleTime.h"
#include "throwIf.h"

ULONG64 getThreadCycleTime(HANDLE threadHandle)
{
    ULONG64 result;
    throwIfFalse(QueryThreadCycleTime(threadHandle, &result), "QueryThreadCycleTime");
    return result;
}
