/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * server.c
 * CS460 Homework 1
 *
 * Kelvin Rodriguez and Franklin Berry 9/17/15.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <pthread.h>
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * main()
 */

int main(int argc, char** argv) {
    int server_socket;                  // descriptor of server socket
    struct sockaddr_in server_address;  // naming the server's listening socket
    int* client_socket = (int*)malloc(sizeof(int));

    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // name the socket (verify the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients
    server_address.sin_port        = htons(PORT);       // port to listen on

    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address,
             sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // listen for client connections
    // (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) == -1) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    // server loop
    while (TRUE) {
        pthread_mutex_lock(&mutex);
        // accept connection to client
        if ((*client_socket = accept(server_socket, NULL, NULL)) == -1) {
            perror("Error accepting client");
        } else {
            printf("\nAccepted client\n");

            pthread_t a_thread;

            if (pthread_create(&a_thread, NULL, handle_client, (void*)client_socket) != 0) {
                perror("Thread creation failed");
                exit(EXIT_FAILURE);
            }
            //handle_client(*client_socket);
        }
    }  // end of server loop
}  // end of main


/**
 * @Author Kelvin Rodriuguez and Franklin Berry
 * @description function to handle the client and run the number guessing logic.
 * @input client socket file descriptor
 */
void *handle_client(void* client_socket) {
    int client = *(int*)client_socket;
    pthread_mutex_unlock(&mutex);
    int fence = MAX/2;
    int increment = MAX/2;
    int number = 0;

    size_t size;
    char output_string[255];
    char response[3];

    while (increment) {
        sprintf(output_string, "Is your number higher than %d?\n", fence);
        write(client, output_string, sizeof(char)*strlen(output_string));

        size = read(client, &response, sizeof(char)*3);
        //response[size] = '\0';

        if (response[0] == 'q')
            break;  // quit

        if (response[0] == 'y') {
            number += increment;
            increment /= 2;
            fence += increment;
        } else {
            increment /= 2;
            fence -= increment;
        }
    }  //End while loop

    number++;
    sprintf(output_string, "Is your number is %d?\n", number);
    write(client, output_string, sizeof(char)*strlen(output_string));

    // close the port ////////////////////////////////
    if (close(client) == -1) {
        perror("Error closing socket");
        exit(EXIT_FAILURE);
    } else {
        printf("\nClosed socket to client, exit");
    }

    pthread_exit("Thread closed");
    ///////////////////////////////////////////////////
}  // end of handle_client
