/****************************************************************************************************
*                 2024 All copyrights reserved (A Real Time Chat Application)
*      Author      : Tarun Tej Barrenkala
*      FILENAME    : client.cpp
*      DESCRIPTION : This file consists of client functions - socket(), connect(), close()
*****************************************************************************************************/
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define BUF_SIZE 1024
#define PORT_NO 1500

using namespace std;

int main()
{
    // Variables Initialization
    int client;
    bool isExit = false;
    char buffer[BUF_SIZE];
    const char* ip = "127.0.0.1";
    sockaddr_in serverAddress;

    /* ------------ Establishing Socket Connection ------------
       ------------ socket() function ------------ */
    client = socket(AF_INET, SOCK_STREAM, 0);
    cout << "************ WELCOME TO REAL-TIME CHAT CLIENT ************" << endl << endl;
    if (client < 0) {
        cout << "=> Failed to establish the socket....." << endl;
        perror("Error: ");
	return EXIT_FAILURE;
    }

    cout << "=> Socket server has been successfully created....." << endl;

    // Defining the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT_NO);
    inet_pton(AF_INET, ip, &(serverAddress.sin_addr));	// Convert IP string to network byte order and set it to sockaddr_in structure.

    /* ------------ Connecting the Socket ------------
       ------------ connect() function ------------ */
    if (connect(client, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        cout << "=> Failed to connect the socket" << endl;
	perror("Error: ");
	return EXIT_FAILURE;
    } 
    else {
	cout << "=> Connection to the server port number: " << PORT_NO << endl;
        cout << "=> Awaiting confirmation from the server....." << endl; // line 38
        recv(client, buffer, BUF_SIZE, 0);
        cout << "=> Connection confirmed, you are good to go.....";
        cout << "\n\n=> Enter # to end the connection\n\n";
    }
    // Once it reaches here the client can send a message first
    do {
        cout << "Client: ";
        cin.getline(buffer, BUF_SIZE);

	// Validating the connection before sending the data
	if (send(client, buffer, BUF_SIZE, 0) < 0) {
    	    cout << "Failed to send the message....." << endl;
	    perror("Error: ");
            break;
	}

        if (*buffer == '#')
            isExit = true;

        recv(client, buffer, BUF_SIZE, 0);
        cout << "Server: " << buffer << " ";
        if (*buffer == '#')
            isExit = true;
        cout << endl;        
    } while(!isExit);

    cout << "\n=> Connection has been terminated" << endl;
    cout << "GOODBYE!....." << endl;
    close(client);
    return EXIT_SUCCESS;
}
