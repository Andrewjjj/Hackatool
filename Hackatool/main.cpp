#include "ProcessHelper.cpp"
#include <iostream>

int main()
{
	ProcessHelper::printAllProcesses();
	std::string str;
	std::cin >> str;
	DWORD processID = ProcessHelper::findProcessID(str);
	std::cout << "Process ID: " << processID << std::endl;
	HANDLE handle = ProcessHelper::getProcessHandle(processID);
	//int baseAddress = ProcessHelper::getBaseAddress(handle);

	
	std::vector<MemoryPage> pageVec = ProcessHelper::getMemoryPages(handle);
	std::cout << "44 ID: " << processID << std::endl;

	for (auto &page : pageVec)
	{
		ProcessHelper::readMemory(handle, page);
		//for (auto m : page)
		//{
		//	std::cout << m << std::endl;
		//}
	}
	std::cout << "Process ID: " << processID << std::endl;

	ProcessHelper::scanMemory(handle, pageVec, 0.1f);
	std::cout << "Process ID: " << processID << std::endl;
	return 0;
}