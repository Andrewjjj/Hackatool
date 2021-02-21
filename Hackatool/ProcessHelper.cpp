#include "ProcessHelper.h"
#include <iostream>
void ProcessHelper::getAllRunningProcesses(std::vector<DWORD> &vec)
{
	DWORD lpidProcesses[1024], cbNeeded, numProcesses;

	if (!EnumProcesses(lpidProcesses, sizeof(lpidProcesses), &cbNeeded))
	{
		return;
	}

	numProcesses = cbNeeded / sizeof(DWORD);

	for (int i = 0; i < numProcesses; i++) {
		if (lpidProcesses[i] != 0)
		{
			vec.push_back(lpidProcesses[i]);
		}
	}
	return;
}

std::string ProcessHelper::getProcessName(DWORD processID)
{
	TCHAR processName[MAX_PATH] = TEXT("unknown");
	HANDLE handleProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
	if (handleProcess != NULL)
	{
		HMODULE hModule;
		DWORD cbNeeded;
		if (EnumProcessModules(handleProcess, &hModule, sizeof(hModule), &cbNeeded))
		{
			GetModuleBaseName(handleProcess, hModule, processName, sizeof(processName) / sizeof(TCHAR));
		}
	}
	CloseHandle(handleProcess);
	std::wstring wstr(&processName[0]);
	std::string str(wstr.begin(), wstr.end());
	return str;
}

DWORD ProcessHelper::findProcessID(std::string processName)
{
	std::vector<DWORD> processVec;
	getAllRunningProcesses(processVec);
	for (auto item : processVec) {
		if (getProcessName(item) == processName) {
			return item;
		}
	}
	return 0;
}

void ProcessHelper::printAllProcesses() {
	std::vector<DWORD> processVec;
	getAllRunningProcesses(processVec);
	for (auto item : processVec) {
		std::cout << getProcessName(item) << std::endl;
	}
}