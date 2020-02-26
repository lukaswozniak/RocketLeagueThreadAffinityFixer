#include <Windows.h>
#include <iostream>
#include <unordered_map>
#include <thread>

#include "ProcessData.h"

bool hasDuplicatedIdealProc(const RocketLeague::ProcessData::ThreadList& threads, int count)
{
    std::unordered_map<DWORD, bool> wasSeenMap;
    for (int i = 0 ; i < count && i < threads.size() ; ++i)
    {
        auto& thread = threads[i];
        if (wasSeenMap.find(thread->getIdealProcessor()) != wasSeenMap.end())
        {
            return true;
        }
        wasSeenMap[thread->getIdealProcessor()] = true;
    }
    return false;
}


int main()
{
    const auto numberOfThreadsToFix = std::thread::hardware_concurrency() - 1;
    while (true)
    {
        try
        {
            RocketLeague::ProcessData rlProcessData;
            while (true)
            {
                rlProcessData.updateThreadsListAndMeasurements();
                auto threads = rlProcessData.getThreadsSortedByUsageDescending();
                threads.resize(numberOfThreadsToFix);
                std::cout << "Found threads:\n";
                for (const auto& thread : threads)
                {
                    std::cout << *thread << "\n";
                }
				if (hasDuplicatedIdealProc(threads, numberOfThreadsToFix))
				{
					std::cout << "Detected duplicated processors, changing ideal processors.\n";
                    std::cout << "Threads after change:\n";
					for (int i = 0; i < numberOfThreadsToFix && i < threads.size(); ++i)
					{
					    threads[i]->trySetIdealProcessor(i);
						std::cout << *threads[i] << "\n";
					}
                    for (int i = numberOfThreadsToFix; i < threads.size(); ++i)
                    {
                        threads[i]->trySetIdealProcessor(numberOfThreadsToFix);
                        if (i + 1 < threads.size())
                        {
					        threads[++i]->trySetIdealProcessor(numberOfThreadsToFix - 1);
                        }
                    }
				}
                Sleep(2000);
            }
        }
		catch (std::exception& ex)
		{
			std::cerr << ex.what() << "\n";
		}
        Sleep(1000);
    }
}
