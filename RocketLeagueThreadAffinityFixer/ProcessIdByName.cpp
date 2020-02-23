#include "ProcessIdByName.h"
#include <TlHelp32.h>
#include <sstream>

ProcessNotFoundException::ProcessNotFoundException(const char* processName)
    : message((std::stringstream() << "Process " << processName << " was not found!").str().c_str())
{}

const char* ProcessNotFoundException::what() const
{
    return message.c_str();
}

std::vector<DWORD> getAllProcessIdsByName(HANDLE snapshot, const char* processName)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    std::vector<DWORD> result;

    if (Process32First(snapshot, &entry) == TRUE)
    {
        do
        {
            if (strcmp(entry.szExeFile, processName) == 0)
            {  
                result.push_back(entry.th32ProcessID);
            }
            entry.dwSize = sizeof(PROCESSENTRY32);
        } while (Process32Next(snapshot, &entry) == TRUE);
    }
    return result;
}

DWORD getProcessIdByName(HANDLE snapshot, const char* processName, int index)
{
    auto processes = getAllProcessIdsByName(snapshot, processName);
    if (processes.size() <= index)
    {
        throw ProcessNotFoundException(processName);
    }
    return processes[index];
}
