/*
   main.c
   sClient

   Created by Kelvin Rodriguez on 11/9/15.
   Copyright © 2015 Kelvin.rodriguez. All rights reserved.
*/

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

#define gloabal_variable static
#define internal static
#define local_persist static

#define true 1
#define false !true

external uint8_t BUFFER_SIZE = 255;

gloabal_variable uint8_t CMD_ECHO = 0;
gloabal_variable uint8_t CMD_DNS  = 1;
gloabal_variable uint8_t CMD_TIME = 2;

// Struct for UDP Packets holding the commands
typedef struct serv_pkt {
    uint8_t cmd;
    size_t argc;
    char** argv;
} service_packet;

/* Fuction to print out a packet on receive */
internal void print_pkt(service_packet packet) {
    printf("Cmd: %s Args: ", (packet.cmd == 0) ? "ECHO" :
                             (packet.cmd == 1) ? "DNS"  :
                             (packet.cmd == 2) ? "TIME" :
                                                 "N/A");
    // print the arguments
    for (int i = 0; i < packet.argc; i++)
        printf("%s ", packet[i]);
    printf("\n");
}

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
    int n;                          // message byte size

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
            printf("ERROR binding binfing port, exiting...");
            exit(-1);
        }
    }
    // ---------------------------------------------------------------

    printf("Server has started...\n");
    
    // Main server loop ----------------------------------------------
    while (true) {
        
        // receive data from client
        // bzero(buffer, BUFFER_SIZE);
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
        
        // Do the service that was received asked of from the client
        if (packet.cmd == CMD_ECHO) {         // Echo message back to host
            for (int i = 0; i < packet.argc; i++) {
                printf("Echoing : %s\n", packet.argv[i]);
                if (sendto(sockfd, packet.argv[i], strlen(packet.argv[i]), 0,
                    (struct sockaddr *) &clientaddr, clientlen) < 0)
                        printf("Error seninding data.\n");
            }
        } else if (packet.cmd == CMD_DNS) {   // Do a DNS lookup
            for (int i = 0; i < packet.argc; i++) {
                getaddrinfo(const char *node,     // e.g. "www.example.com" or IP
                            const char *service,  // e.g. "http" or port number
                            const struct addrinfo *hints,
                            struct addrinfo **res);
            }
            
            if (sendto(sockfd, packet.argv[i], strlen(packet.argv[i]), 0,
                       (struct sockaddr *) &clientaddr, clientlen) < 0)
                printf("Error seninding data.\n");
        } else if (packet.cmd == CMD_TIME) {  // Send server time
            
        }
    }
    // --------------------------------------------------------------

    return 0;
}
