#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <string>

struct MemoryPage {
	char* baseAddress;
	size_t size;

	MemoryPage(char* address, size_t size) : baseAddress(address), size(size) {}
};

namespace ProcessHelper
{
	template <class T>
	static std::vector<char> sliceData(T data);

	static void getAllRunningProcesses(std::vector<DWORD> &vec);
	static std::string getProcessName(DWORD processID);
	static DWORD findProcessID(std::string processName);
	static void printAllProcesses();
	static HANDLE getProcessHandle(DWORD processID);
	static void closeProcess(HANDLE processHandle);

	template <class T>
	static void scanMemory(HANDLE handle, std::vector<MemoryPage> pageVec, T value);
	static DWORD getBaseAddress(HANDLE processHandle);

	static std::vector<MemoryPage> getMemoryPages(HANDLE processHandle);
	static std::vector<char> readMemory(HANDLE processHandle, MemoryPage page);
	//ProcessHelper() {  };
	//static std::vector<DWORD> processVec;
};

