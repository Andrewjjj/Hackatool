#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>   
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include <iomanip>

using namespace std;

// This will be used to continuously update the current time
struct timeval currentTime;

// Variable to keep track of total transactions
int totalTransactions = 0;

// This function is used to get current time, parse and returns it as string
string getCurrentTimeString();

// Forward declaration of the two functions
int Trans(int n);
int Sleep(int n);