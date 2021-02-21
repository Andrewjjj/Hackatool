#include "ProcessHelper.cpp"
#include <iostream>

int main()
{
	ProcessHelper::printAllProcesses();
	std::string str;
	std::cin >> str;
	DWORD processID = ProcessHelper::findProcessID(str);

	std::cout << "Process ID: " << processID << std::endl;
	return 0;
}