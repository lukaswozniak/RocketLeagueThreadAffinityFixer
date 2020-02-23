#include "ProcessData.h"

#include "closeHandle.h"
#include "createToolhelp32Snapshot.h"
#include "ProcessIdByName.h"
#include "ThreadIdsByProcessId.h"

#include <algorithm>
#include <iostream>

namespace RocketLeague
{
    ProcessData::ProcessData()
    {
        snapshot = createToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD, NULL);
		processId = getProcessIdByName(snapshot, "RocketLeague.exe", 1);
        for (const auto& threadId : getThreadIdsByProcessId(snapshot, processId))
        {
			addNewThreadNoThrow(threadId);
        }
    }

    ProcessData::~ProcessData()
    {
        closeHandle(snapshot);
    }

    void ProcessData::updateThreadsListAndMeasurements()
    {
        updateSnapshot();
        updateThreadsList();
        updateMeasurements();
    }

    ProcessData::ThreadList ProcessData::getThreadsSortedByUsageDescending()
    {
        ProcessData::ThreadList result;
        for (const auto& thread : threads)
        {
            result.push_back(thread.second);
        }
        std::sort(result.begin(), result.end(), [](auto& a, auto& b) { return ThreadData::compareByCpuUsage(*a, *b); });
        std::reverse(result.begin(), result.end());
        return result;
    }

    void ProcessData::updateSnapshot()
    {
        auto newSnapshot = createToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD, NULL);
        closeHandle(snapshot);
        snapshot = newSnapshot;
        if (processId != getProcessIdByName(snapshot, "RocketLeague.exe", 1))
        {
            throw std::runtime_error("Rocket league process disappeared while updating");
        }
    }
    void ProcessData::updateThreadsList()
    {
        const auto& updatedThreadIds = getThreadIdsByProcessId(snapshot, processId);
        for (auto i = threads.begin() ; i != threads.end() ;)
        {
            if (updatedThreadIds.find(i->first) == updatedThreadIds.end())
            {
                std::cout << "Found thread to erase: " << i->first << "\n";
                i = threads.erase(i);
            }
            else
            {
                ++i;
            }
        }
        for (const auto& threadId : updatedThreadIds)
        {
            if (threads.find(threadId) == threads.end())
            {
                std::cout << "New thread found: " << threadId << "\n";
                addNewThreadNoThrow(threadId);
            }
        }
    }
    void ProcessData::updateMeasurements()
    {
        for (auto& thread : threads)
        {
            thread.second->measureCurrentCpuUsage();
        }
    }

    void ProcessData::addNewThreadNoThrow(ThreadId threadId) noexcept
	try
	{
		threads[threadId] = std::make_shared<ThreadData>(threadId);
	}
	catch (std::exception & ex)
	{
		std::cerr << "Failed to create ThreadData for thread id: " << threadId << "because of error: " << ex.what() << "\n";
	}
}