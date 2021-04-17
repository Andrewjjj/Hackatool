#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>   
#include <unistd.h>
#include <sys/select.h>
#include <ctime>
#include <sys/time.h>
#include <unordered_map>
#include <cstring>

// Server timeout value
#define TIMEOUT 30

using namespace std;

// This unordered_map is used to keep track of number of transactions per machinename.
unordered_map<string, int> transactionCount;

struct timeval currentTime; // This will be used to continuously update the current time
struct timeval firstTime; // This is updated only once when the very first connection with Tx happens 
struct timeval lastTime; // This is updated constantly only when message is being passed between clients

bool firstTimeBool = false; // Used to check and store the firstTime

int doneCount = 1; // This is the Done count used to display how many jobs server has done.

// This function is used to get current time, parse and returns it as string
string getCurrentTimeString();

// Forward declaration of the two functions
int Trans(int n);
int Sleep(int n);