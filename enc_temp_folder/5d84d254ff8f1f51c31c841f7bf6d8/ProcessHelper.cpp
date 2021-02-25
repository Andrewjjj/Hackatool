#include "ProcessHelper.h"
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <sys/types.h>

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

HANDLE ProcessHelper::getProcessHandle(DWORD processID)
{
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	if (!processHandle)
	{
		std::cerr << "Failed to Open Process" << std::endl;
	}
	return processHandle;
}

DWORD ProcessHelper::getBaseAddress(HANDLE processHandle)
{
	HMODULE hModule = NULL;
	LPWSTR buffer = NULL;
	DWORD cbNeeded;
	DWORD baseAddress;

	if (GetModuleBaseName(processHandle, hModule, buffer, sizeof(buffer))) {
		return (DWORD)hModule;
	}
	return -1;
}

void ProcessHelper::closeProcess(HANDLE processHandle)
{
	CloseHandle(processHandle);
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

template <class T>
void ProcessHelper::scanMemory(HANDLE handle, std::vector<MemoryPage> pageVec, T value)
{
	int blockSize = sizeof(T);
	T* content = nullptr;
	SIZE_T toRead;
	for (int i = 0; i < pageVec.size(); i++) {
		if (ReadProcessMemory(handle, pageVec[i].baseAddress, (LPVOID)content, blockSize, &toRead))
		{
			//if(content)
			std::cout << *content << std::endl;
			if (*content == value) {
				//std::cout << "FOUND!!!!" << std::endl;
				//std::cout << content << std::endl;
			}
		}
	}
	return; 
}

std::vector<MemoryPage> ProcessHelper::getMemoryPages(HANDLE processHandle)
{
	std::cout << "32323" << std::endl;

	std::vector<MemoryPage> pageVec;
	MEMORY_BASIC_INFORMATION blockInfo;
	typedef char byte_t;
	typedef byte_t* address_t;
	int i = 0;
	std::cout << "555" << std::endl;

	for (char* address = nullptr;
		VirtualQueryEx(processHandle, address, &blockInfo, sizeof(blockInfo)) == sizeof(blockInfo);
		address = static_cast<char*>(blockInfo.BaseAddress) + blockInfo.RegionSize)
	{
		//std::cout << i << std::endl;
		//i++;
		////std::cout << address << std::endl;

		if (blockInfo.State == MEM_COMMIT && blockInfo.Type == MEM_PRIVATE && blockInfo.Protect == PAGE_READWRITE)
		{
			//std::cout << address << std::endl;
			std::cout << i << std::endl;
			i++;
			pageVec.emplace_back(static_cast<char*>(address), blockInfo.RegionSize);
		}
	}
	return pageVec;
}



