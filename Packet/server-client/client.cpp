#include "client.h"

using namespace std;

// This function gets current epoch time with decimals, formats it to string and returns it.
string getCurrentTimeString(){
    gettimeofday(&currentTime, NULL);
    long double t = currentTime.tv_sec + currentTime.tv_usec / 1000000.0;
    string s = to_string(t);
    size_t pos = s.find(".");
    return s.substr(0,pos+3);
}

int main(int argc, char *argv[]){
    int portNumber = stoi(argv[1]); // Get the port number from argument
    string ipAddress = argv[2]; // Get the ip address number from argument
    
    // Get the client host name (machine name) and store it as string
    char hostNameChar[1024];
    gethostname(hostNameChar, sizeof(hostNameChar));
    string hostName = hostNameChar;

    pid_t pid = getpid(); // Get pid

    // Combine hostname + pid to send to server.
    string hostNameToSend = hostName + "." + to_string(pid);

    // Initial print of port number, ip address and host name + pid
    cout << "Using port " << to_string(portNumber) << endl;
    cout << "Using server address " << ipAddress << endl;
    cout << "Host " << hostNameToSend << endl;
    
    string s;
    while(getline(cin, s)){
        // string timeAmount = s.substr(1);
        // We are sending hostname + Tx in the same buffer.
        // For example, if the machineName was ug00 and we want to do T100,
        // The buffer to send would look like: ug00|100.
        // If we are sending acknowledgement for Done, it would be: ug00|Done.
        // string msgToSend = hostNameToSend + "|" + timeAmount;
        // string doneStr = hostNameToSend + "|Done";
        // int timeAmountInt = stoi(timeAmount);
        printf("Sending %s\n", s.c_str());
        char c = s[0];

        // Check if it is sleep. If it is, sleep then skip the cycle.
        // if(c == 'S'){
        //     cout << "Sleep " + timeAmount + " units" << endl;
        //     Sleep(timeAmountInt);
        //     continue;
        // }        

        // Setting up message sending to server.
        char msgToSendBuf[1024];
        strcpy(msgToSendBuf, s.c_str());

        // Create socket
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if(fd < 0) {
            cout << "FD Error" << endl;
            return -1;
        }

        // Create struct to store information about the server
        struct sockaddr_in serv_addr;

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[2]);
        serv_addr.sin_port = htons(portNumber);

        // Attempt to connect to the server
        if(connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            cout << "Connect Error" << endl;
            return -1;
        }

        // print "Sending" and sends it to the server and increase the total transaction count.
        // totalTransactions++;
        // cout << getCurrentTimeString() << ": Send (T" << timeAmount << ")" << endl;
        cout << "Size: " << sizeof(s) << endl;
        write(fd, msgToSendBuf, s.length());

        // Receiving the "Done #" from server and store it in a string
        // string doneNumber;
        // char buffer[1024];
        // if(recv(fd, buffer, 1000, 0) < 0)
		// {
		// 	puts("recv failed");
		// 	break;
		// }
        // doneNumber = buffer;
        // Print "Done", receive "Done" from the server, send acknowledgement to server then close the connection.
        // cout << getCurrentTimeString() << ": Recv (D" << doneNumber << ")" << endl;
        // char doneBuf[1024];
        // strcpy(doneBuf, doneStr.c_str());
        // write(fd, doneBuf, sizeof(doneBuf));
        close(fd);
        fflush(stdout);
    }
    // Print Summary
    cout << "Sent " << totalTransactions << " transactions" << endl;
    return 0;
}