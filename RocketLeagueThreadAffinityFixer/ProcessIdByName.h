#pragma once

#include <Windows.h>

#include <exception>
#include <string>
#include <vector>

class ProcessNotFoundException : public std::exception
{
public:
    ProcessNotFoundException(const char* processName);
    const char* what() const override;
private:
    std::string message;
};

std::vector<DWORD> getAllProcessIdsByName(HANDLE snapshot, const char* processName);
DWORD getProcessIdByName(HANDLE snapshot, const char* processName, int index = 0);
