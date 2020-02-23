#include "ThreadIdealProcessor.h"
#include "throwIf.h"

DWORD getThreadIdealProcessorNum(HANDLE threadHandle)
{
	PROCESSOR_NUMBER procNum;
	throwIfFalse(GetThreadIdealProcessorEx(threadHandle, &procNum), "GetThreadIdealProcessorEx");
	return procNum.Number;
}

void setThreadIdealProcessorNum(HANDLE threadHandle, DWORD idealProcNum)
{
	throwIfMinusOne(SetThreadIdealProcessor(threadHandle, idealProcNum), "SetThreadIdealProcessor");
}
