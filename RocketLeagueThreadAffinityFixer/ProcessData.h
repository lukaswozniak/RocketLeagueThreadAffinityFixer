#pragma once
#include <Windows.h>
#include <memory>
#include <vector>
#include <unordered_map>

#include "ThreadData.h"

namespace RocketLeague
{

class ProcessData
{
public:
    using ThreadList = std::vector<std::shared_ptr<ThreadData>>;
    DWORD processId;
    ProcessData();
    ~ProcessData();

    void updateThreadsListAndMeasurements();
    ThreadList getThreadsSortedByUsageDescending();

private:
    void updateSnapshot();
    void updateThreadsList();
    void updateMeasurements();
    void addNewThreadNoThrow(ThreadId threadId) noexcept;

    HANDLE snapshot = NULL;
    std::unordered_map<ThreadId, std::shared_ptr<ThreadData>> threads;
};

}
