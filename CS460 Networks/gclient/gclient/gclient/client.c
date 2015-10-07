//
//  main.c
//  gclient
//
//  Created by Kelvin Rodriguez and on Franklin Berry
//  Copyright (c) 2015 Kelvin Rodriguez All rights reserved.
//
//  Description:
//      A simple client that will interpret messgaes from and send messages
//      to our mutli-threaded server
//

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <math.h>

size_t BUFFER_SIZE = 256;
size_t NUM_CONEECTIONS = 10;
size_t MAX = 1024;

#define true 1
#define false !true

// main, the only funtion in the program
int main(int argc, char *argv[]) {
    // declare some stuff //
    int    host_sock;
    int    portno;
    int    num_to_guess;
    int    serv_guess = 0;
    time_t curr_time;
    size_t serv_mess_len;
    char   serv_message[BUFFER_SIZE];
    
    struct sockaddr_in serv_addr;

    if (argc < 3) {
        printf("Usage: gclient [Host Address] [Port Number]");
        return 1;
    }
    
    // initialize some of that stuff //
    memset(&serv_addr,   '0', sizeof(serv_addr));
    memset(serv_message, '0', sizeof(serv_message));
    portno               = atoi(argv[2]);
    host_sock            = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(portno);
    
    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
    
    // Print Server Connection Info //
    printf("Client Address: %s\n", argv[1]);
    printf("Port Number: %d\n\n" , portno);
    
    // Connect //
    if (connect(host_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) >= 0) {
        printf("Connected...\n\n");
    } else {
        printf("Failed to connect.");
        return 1;
    }
    
    // Generate a number for the server to guess //
    srand((unsigned) time(&curr_time));
    num_to_guess = rand()%1024+1;
    printf("Number server has to guess: %d\n\n", num_to_guess);
    
    int guess_count = 0;
    // Server Loop ////////////////////////////////////
    while ((serv_mess_len = read(host_sock, serv_message, sizeof(serv_message)-1)) > 0) {
        serv_message[serv_mess_len] = 0;
        printf("Server - %s", serv_message);
        
        /* Parse User Server Message */ {
            int last_space_index = 0;
            int question_mark_index = 0;
            
            // find the index of last space and the punctuation mark (e.g. '?') //
            for (int i = 0; i < strlen(serv_message); i++) {
                if (serv_message[i] == ' ')
                    last_space_index = i;
                else if (serv_message[i] == '?')
                    question_mark_index = i;
            }
            
            memcpy(serv_message, &serv_message[last_space_index], 4 );
            serv_guess = atoi(serv_message);
            
            if (num_to_guess > serv_guess) {
                write(host_sock, "y", sizeof(char));
                printf("Client - y\n");
            } else if(guess_count < floor(log(MAX)/log(2))) {
                write(host_sock, "n", sizeof(char));
                printf("Client - n\n");
            }
            
            guess_count++;
        }
    }
    ///////////////////////////////////////////////////
    if(num_to_guess == serv_guess) {
        printf("\nServer's guess: %d\n", serv_guess);
        printf("Client's number: %d\n", num_to_guess);
        printf("\nYES, THE SERVER IS CORRECT!!!");
    }
    
    close(host_sock);
    return 0;
}