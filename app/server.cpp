/**********************************************************************************************************
*                 2024 All copyrights reserved (A Real Time Chat Application)
*      Author      : Tarun Tej Barrenkala
*      FILENAME    : server.cpp
*      DESCRIPTION : This file consists of server functions - socket(), bind(), listen(), accept(), close() 
***********************************************************************************************************/
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define PORT_NO 1500

using namespace std;

int main()
{
    // Variables Initialization
    int listenSocket, clientSocket;
    bool isExit = false;
    char buffer[BUF_SIZE];
    struct sockaddr_in serverAddress;
    socklen_t size;

    /* ------------ socket() function ------------ */
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    cout << "************ WELCOME TO REAL-TIME CHAT SERVER ************" << endl << endl;
	if (listenSocket < 0) {
        cout << "=> Failed to create socket!" << endl;
		perror("Error: ");
        return EXIT_FAILURE;
    }

    // Defining the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(PORT_NO);

    /* ------------ Binding the socket ------------
       ------------ bind() function ------------ */
    if (bind(listenSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        cout << "=> Binding failed!" << endl;
        perror("Error: ");
		return EXIT_FAILURE;
    }

    /* ------------ Listening the incomming socket ------------
       ------------ listen() function ------------ */
    if (listen(listenSocket, 1) < 0) {
        cout << "=> Listening failed!" << endl;
        perror("Error: ");
		return EXIT_FAILURE;
    }

	cout << "=> Socket server has been successfully created....." << endl;
	cout << "=> bind() OK!....." << endl;
	cout << "=> listen() OK! Listening for the incomming socket connections....." << endl;
    cout << "=> Server is waiting for client connections....." << endl;
    
    // Accept loop
    while ((clientSocket = accept(listenSocket, (struct sockaddr *)&serverAddress, &size)) > 0) {
        cout << "Client connected!" << endl;
        // Communication with client...

   		isExit = false;
    	while (!isExit) {
			cout << endl;
        	cout << "Server: ";
        	cin.getline(buffer, BUF_SIZE);
        	send(clientSocket, buffer, BUF_SIZE, 0);
        	if (*buffer == '#') {
            	*buffer = '*'; // Cleanly mark end of communication intent
            	isExit = true;
            	continue; // Skip the next part if we're exiting
        	}

        	recv(clientSocket, buffer, BUF_SIZE, 0);
        	if (*buffer == '#')
            	isExit = true; // Prepare to exit if client sends '#'
        	else
            	cout << "Client: " << buffer << " ";
    	}
        
        // Close the client socket after handling communication
        close(clientSocket);
    }

    close(listenSocket);
    return EXIT_SUCCESS;
}
