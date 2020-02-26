#pragma once

#include <Windows.h>
#include <ostream>

namespace RocketLeague
{

using ThreadId = DWORD;
struct ThreadData
{
    ThreadId id;

    ThreadData(ThreadId id);

    void measureCurrentCpuUsage();
    double getCpuUsage() const;
    DWORD getIdealProcessor() const;
    DWORD getIdealProcessor();
    void setIdealProcessor(DWORD idealProcessor);
    void trySetIdealProcessor(DWORD idealProcessor);

    static bool compareByCpuUsage(const ThreadData& a, const ThreadData& b);

private:
    DWORD idealProcessor;
    HANDLE handle = NULL;
    ULONG64 cycleTime = 0;
    ULONGLONG measurementTime = 0;
    ULONG64 prevCycleTime = 0;
    ULONGLONG prevMeasurementTime = 0;
};

std::ostream& operator<<(std::ostream& os, const ThreadData& data);

}

