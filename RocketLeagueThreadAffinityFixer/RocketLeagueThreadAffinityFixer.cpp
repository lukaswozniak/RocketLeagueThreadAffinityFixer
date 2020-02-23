#include <Windows.h>
#include <iostream>
#include <unordered_map>
#include <thread>

#include "ProcessData.h"

bool hasDuplicatedIdealProc(const RocketLeague::ProcessData::ThreadList& threads)
{
    std::unordered_map<DWORD, bool> wasSeenMap;
    for (const auto& thread : threads)
    {
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
    const auto numberOfThreadsToFix = min(std::thread::hardware_concurrency(), 3);
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
				if (hasDuplicatedIdealProc(threads))
				{
					std::cout << "Detected duplicated processors, changing ideal processors.\n";
                    std::cout << "Threads after change:\n";
					for (int i = 0; i < threads.size(); i++)
					{
						auto thread = *threads[i];
                        try
                        {
							thread.setIdealProcessor(i);
                        }
                        catch (std::exception & ex)
                        {
			                std::cerr << ex.what() << "\n";
                        }
						std::cout << thread << "\n";
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
