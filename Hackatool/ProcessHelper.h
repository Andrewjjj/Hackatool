#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <string>

namespace ProcessHelper
{
	static void getAllRunningProcesses(std::vector<DWORD> &vec);
	static std::string getProcessName(DWORD processID);
	static DWORD findProcessID(std::string processName);
	static void printAllProcesses();
	//ProcessHelper() {  };
	//static std::vector<DWORD> processVec;
};

