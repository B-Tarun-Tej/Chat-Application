#**********************************************************************************************************
#                 2024 All copyrights reserved (A Real Time Chat Application)
#      Author      : Tarun Tej Barrenkala
#      FILENAME    : makefile
#      DESCRIPTION : This is a makefile for compilation
#**********************************************************************************************************

CC = g++
CFLAGS = #-Wall -Wextra

all: server client

server: server.cpp
	$(CC) $(CFLAGS) -o server server.cpp

client: client.cpp
	$(CC) $(CFLAGS) -o client client.cpp

.PHONY: clean run_server run_client

run_server: server
	./server

run_client: client
	./client

clean:
	rm -f server client
