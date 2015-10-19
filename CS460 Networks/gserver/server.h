//
//  server.h
//  CS460 Homework 1
//
//  Kelvin Rodriguez and Franklin Berry 9/17/15.
//

#ifndef CS460_Homework_1_server_h
#define CS460_Homework_1_server_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

pthread_mutex_t mutex;
/* Function prototypes */
void *server_menu(void* server_socket);
void *handle_client(void* client_socket);

/* Preprocessor directives */
#define SERVER_ADDR "127.0.0.1" // for client
#define PORT 23656  // port the server will listen on
#define MAX 1024

#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 40       // number of pending connections in the connection queue

#endif
