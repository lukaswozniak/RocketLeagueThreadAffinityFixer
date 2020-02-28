#include "ThreadData.h"

#include "closeHandle.h"
#include "openThread.h"
#include "getThreadCycleTime.h"
#include "ThreadIdealProcessor.h"

#include <iostream>

namespace RocketLeague
{

ThreadData::ThreadData(ThreadId id) : id(id)
{
	handle = openThread(THREAD_ALL_ACCESS, false, id);
	measureCurrentCpuUsage();
	measureCurrentCpuUsage();
	idealProcessor = getThreadIdealProcessorNum(handle);
}

ThreadData::~ThreadData()
{
	closeHandle(handle);
}

void ThreadData::measureCurrentCpuUsage()
{
	prevCycleTime = cycleTime;
	prevMeasurementTime = measurementTime - 1;
	cycleTime = getThreadCycleTime(handle);
	measurementTime = GetTickCount64();
}

double ThreadData::getCpuUsage() const
{
	return static_cast<double>(cycleTime - prevCycleTime) / static_cast<double>(measurementTime - prevMeasurementTime) / 1000.0;
}

DWORD ThreadData::getIdealProcessor() const
{
	return idealProcessor;
}

DWORD ThreadData::getIdealProcessor()
{
	try
	{
		idealProcessor = getThreadIdealProcessorNum(handle);
	}
	catch (...)	{	}
	return idealProcessor;
}

void ThreadData::setIdealProcessor(DWORD idealProcessor)
{
	setThreadIdealProcessorNum(handle, idealProcessor);
	this->idealProcessor = idealProcessor;
}

void ThreadData::trySetIdealProcessor(DWORD idealProcessor)
try
{
	setIdealProcessor(idealProcessor);
}
catch (std::exception & ex)
{
	std::cerr << ex.what() << "\n";
}

bool ThreadData::compareByCpuUsage(const ThreadData& a, const ThreadData& b)
{
	return a.getCpuUsage() < b.getCpuUsage();
}

std::ostream& operator<<(std::ostream& os, const ThreadData& data)
{
    os << "Thread id: " << data.id << " Cpu usage: " << data.getCpuUsage() << " Ideal processor: " << data.getIdealProcessor();
    return os;
}

}
