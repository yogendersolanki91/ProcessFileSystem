#include <Psapi.h>
#include <windows.h>
#include <tlhelp32.h>
#include <list>
std::list<PROCESSENTRY32> GetAllProcess(){
	std::list<PROCESSENTRY32> processList;
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		//	printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
		return processList;
	}
	pe32.dwSize = sizeof(PROCESSENTRY32);
	do
	{
		WCHAR *name = pe32.szExeFile;
		//_tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
		// Retrieve the priority class.
		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		processList.push_back(pe32);
	} while (Process32Next(hProcessSnap, &pe32));
	return processList;
}