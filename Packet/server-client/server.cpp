#include "server.h"
#include "../packetHelper.h"

using namespace std;

// This function gets current epoch time with decimals, formats it to string and returns it.
string getCurrentTimeString(){
    gettimeofday(&currentTime, NULL);
    long double t = currentTime.tv_sec + currentTime.tv_usec / 1000000.0;;
    string s = to_string(t);
    size_t pos = s.find(".");
    return s.substr(0,pos+3);
}

// Main
int main(int argc, char *argv[]){
    int portNumber = stoi(argv[1]); // Grabs the port number from arguments
    
    cout << "Using port " << to_string(portNumber) << endl; // Prints "Using port xxxx"
    
    int fd = socket(AF_INET, SOCK_STREAM, 0); // Create a file descriptor and binds it to socket created.
    
    if(fd < 0) return -1; // If socket was not successfully created, returns -1.
    
    // Creating a sockaddr struct that holds server information such as port number, letting who to connect etc.
    struct sockaddr_in serv_addr; 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNumber);

    // Binding our sockaddr_in struct to our file descriptor
    if(::bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "Bind Error" << endl;
        return -1;
    }

    // Listening to any incoming connections
    if(listen(fd, 1) < 0){
        cout << "Listen Error" << endl;
        return -1;
    }

    while(1){
        // creating struct to store information about the client.
        struct sockaddr_in client_address;
        int len = sizeof(client_address);
        int client_fd; // File Descriptor for client

        // Variables for timeout
        fd_set set;
        struct timeval timeout;
        int rv;
        FD_ZERO(&set);
        FD_SET(fd, &set);

        // Setting the timeout seconds. TIMEOUT is defined in the header file
        timeout.tv_sec = TIMEOUT;

        // Checking for timeout
        // rv = select(fd + 1, &set, NULL, NULL, &timeout);
        // if(rv == -1){ // Something went wrong
        //     cout << "RV Timeout Error" << endl;
        //     return -1;
        // }
        // else if (rv == 0){ // Timeouts
        //     cout << "Timeout" << endl;
        //     break;
        // }
        // else{ // Normal routine if something is incoming from the client
        
            // Accepts the client to connect to the server 
            client_fd = accept(fd, (struct sockaddr*)&client_address, (socklen_t*)&len); 

            char buffer[1024]; // Buffer to store incoming data from the client
            int readSize = 0; // Variable to check if receiving happened without error.
            string msg; // String to store the incoming data
            string hostName; // String to store the hostname of the client

            // This is where reading from client happens.
            // Client sends the message with the following format: client_name|TNumber.
            // Hence, we find '|', split it into 2. client name and the seconds we need to process Trans
            // However, Client might send Tx or Done, so we will check that as well.
            readSize = recv(client_fd, &buffer, sizeof(buffer), 0);
            while(readSize > 0){
                printf("RECV: %d bytes\n", readSize);
                dump(buffer, readSize);
                readSize = recv(client_fd, &buffer, sizeof(buffer), 0);
                // msg = buffer; // Store the message in string
                // size_t pos = msg.find("|"); // Find the position to split
                // hostName = msg.substr(0,pos); // Split the first half
                // string transValue = msg.substr(pos+1); // Split the second half
                // if(transValue == "Done"){
                //     gettimeofday(&lastTime, NULL); // Continuously update our time for the summary calculation
                //     cout << getCurrentTimeString() << ": # " << doneCount << " (Done) from " << hostName << endl; // Prints
                //     transactionCount[hostName]++;
                //     doneCount++;
                //     break;
                // }
                // else{
                //     // Stores the very first transaction for the summary calculation
                //     if(!firstTimeBool){
                //         gettimeofday(&firstTime, NULL);
                //         firstTimeBool = true;
                //     }
                //     gettimeofday(&lastTime, NULL);
                //     cout << getCurrentTimeString() << ": # " << doneCount << " (T " << transValue << ") from " << hostName << endl;
                //     Trans(stoi(transValue));

                //     // Sending the done #. 1,2,3........
                //     char msgToSend[1024];
                //     strcpy(msgToSend, to_string(doneCount).c_str());
                //     write(client_fd, msgToSend, sizeof(msgToSend));
                // }
            }     
            if(readSize == 0){
                fflush(stdout);
            }   
            close(client_fd);
        // }
        if(client_fd < 0) continue;
        
    }
    cout << "End" << endl;
    // Print Summary
    // cout << "SUMMARY " << endl;
    // // Iterating through transactions and counting the transactions for each of the client names.
    // int totalTransactions = 0;
    // for(auto t: transactionCount){
    //     totalTransactions += t.second;
    //     cout << t.second << " transactions from " << t.first << endl;
    // }
    // // Parsing time for result
    // long double totalTime = 
    //     (lastTime.tv_sec + (lastTime.tv_usec / 1000000.0)) 
    //     - (firstTime.tv_sec + (firstTime.tv_usec / 1000000.0));
    // cout << (long double)totalTransactions / totalTime << " transactions/sec (" << totalTransactions << "/" << totalTime << ")" << endl;
    return 0;
}