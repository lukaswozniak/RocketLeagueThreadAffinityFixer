#include "ThreadIdsByProcessId.h"
#include <TlHelp32.h>

std::unordered_set<DWORD> getThreadIdsByProcessId(HANDLE hThreadSnap, DWORD processId)
{ 
  THREADENTRY32 te32; 
  te32.dwSize = sizeof(THREADENTRY32); 

  std::unordered_set<DWORD> result;
  if(Thread32First( hThreadSnap, &te32 )) 
  {
	  do
	  {
		  if (te32.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(te32.th32OwnerProcessID) && te32.th32OwnerProcessID == processId)
		  {
              result.emplace(te32.th32ThreadID);
		  }
          te32.dwSize = sizeof(THREADENTRY32); 
	  } while (Thread32Next(hThreadSnap, &te32));
  }

  return result;
}
