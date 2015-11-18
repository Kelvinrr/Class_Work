/*
   main.c
   sClient

   Created by Kelvin Rodriguez on 11/9/15.
   Copyright © 2015 Kelvin.rodriguez. All rights reserved.
*/

#include "upd_packet.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>


/* This is a main method */
int main(int argc, const char * argv[]) {
    int sockfd;                     // socket
    socklen_t clientlen;            // byte size of client's address
    struct sockaddr_in serveraddr;  // server's address
    struct sockaddr_in clientaddr;  // client address to connect to
    struct hostent *hostp;          // client host info
    char buffer[BUFFER_SIZE];       // Buffer for in/out messages
    service_packet packet;          // Packet received
    char *hostaddrp;                // dotted decimal host addr string

    // Print usage if there are not enough arguements
    if (argc < 2) {
        printf("Usage: userver [port number]\n");
        exit(0);
    }
    
    printf("Initializing server...\n");
    
    /* Initialize the server ------------------------------------ */ {
        // assign the port number
        int portno = atoi(argv[1]);  // set port number
        
        // Open the socket
        if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            printf("Error opening socket, exiting...");
            exit(-1);
        }

        // set the server address structure
        bzero((char *) &serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons((unsigned short)portno);

        // bind the port to address
        if (bind(sockfd, (struct sockaddr *) &serveraddr,
                 sizeof(serveraddr)) < 0) {
            printf("ERROR binding binfing port, exiting...\n");
            exit(-1);
        }
    }
    // ---------------------------------------------------------------

    printf("Server has started...\n\n");
    clientlen = sizeof(clientaddr);
    // Main server loop ----------------------------------------------
    while (true) {
        
        // receive data from client
        if(recvfrom(sockfd, &packet, sizeof(packet), 0,
             (struct sockaddr*) &clientaddr, &clientlen) < 0)
                 printf("Error recieving  data from client.");

        // get host address
        if((hostp = gethostbyaddr(
                    (const char *)&clientaddr.sin_addr.s_addr,
                    sizeof(clientaddr.sin_addr.s_addr), AF_INET)) == NULL) {
            printf("ERROR on gethostbyaddr\n");
            break;
        }
        
        // get client address
        if((hostaddrp = inet_ntoa(clientaddr.sin_addr)) == NULL)
            printf("ERROR on inet_ntoa\n");

        // determin who sent the datagram
        printf("Received datagram from %s (%s)\n", hostp->h_name, hostaddrp);
        printf("server received %lu bytes\n", sizeof(packet));
        print_pkt(packet);
        
        /* Start to handle the client request ------------------------- */ {
            // Echo message back to host ==============================
            if (packet.cmd == CMD_ECHO) {
                sprintf(buffer, "%s\n", packet.arg.str);
            }  // end of echo
            
            // do a DNS lookup ========================================
            else if (packet.cmd == CMD_DNS) {
                local_persist struct hostent *he;
                he = gethostbyname(packet.arg.str);
                if(he == NULL)
                    sprintf(buffer, "%s cannot be resolved to an address.\n",
                            packet.arg.str);
                else
                    sprintf(buffer, "%s resolved to %s\n", packet.arg.str,
                        inet_ntoa(*(struct in_addr *)he->h_addr_list[0]));
            }  // end of echo
            
            // send server time in HH:MM ===============================
            else if (packet.cmd == CMD_TIME) {
                time_t raw_time;
                time(&raw_time);
                struct tm *tm_local_time = localtime(&raw_time);
                
                sprintf(buffer,
                        "The time is %d:%d\n",
                        tm_local_time->tm_hour,
                        tm_local_time->tm_min);
            }  // end of sedning server time
            
            printf("Sending to client: %s\n\n", buffer);
            if (sendto(sockfd, buffer, strlen(buffer), 0,
                       (struct sockaddr *) &clientaddr, clientlen) < 0)
                printf("Error sending data.\n");
        }  // end of handling client request
    }
    // --------------------------------------------------------------

    return 0;
}
