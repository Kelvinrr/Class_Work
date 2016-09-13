/*
 * uclient.c - A simple UDP client
 * usage: udpclient <host> <port>
 */

#include "upd_packet.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSIZE 1024

int main(int argc, char **argv) {
    int sockfd;
    long n;
    socklen_t serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char buf[BUFSIZE];
    service_packet packet;

    /* check command line arguments */
    if (argc < 4) {
        printf("usage: %s [hostname] [port] [service] [Parameter]\n", argv[0]);
        printf("-t --TIME\t\t\tGet server time");
        printf("-e --ECHO [STRING]\t\t\tEcho String");
        printf("-d --DNS  [URL]\t\t\tDo a DNS lookpup of URL");
        exit(0);
    }

    // create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    // get the server's DNS entry
    hostname = argv[1];
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    // create the server's internet address
    int portno = atoi(argv[2]);

    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    // get the service request from main's arguement vector
    if (strcmp(argv[3], "--DNS") == 0 | strcmp(argv[3], "-d") == 0) {           // if DNS lookup request
        packet.cmd = CMD_DNS;
        packet.argc = argc - 4;
        init_packet_arg(&packet, argv, 4, argc);
    } else if (strcmp(argv[3], "--ECHO") == 0 | strcmp(argv[3], "-e") == 0) {   // if echo request
        packet.cmd = CMD_ECHO;
        packet.argc = argc - 4;
        init_packet_arg(&packet, argv, 4, argc);
    } else if (strcmp(argv[3], "--TIME") == 0 | strcmp(argv[3], "-t") == 0) {   // if server time request
        packet.cmd = CMD_TIME;
    } else {
        printf("Passed incorrect Parameter for service call: %s\n", argv[3]);
        exit(0);
    }

    // send the message to the server
    serverlen = sizeof(serveraddr);
    n = sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr*)&serveraddr, serverlen);
    if (n <= 0)
        error("ERROR in sendto\n");

    // print the server's reply
    n = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&serveraddr, &serverlen);
    if (n <= 0)
        error("ERROR in recvfrom\n");
    printf("Server message: %s\n", buf);
    return 0;
}
