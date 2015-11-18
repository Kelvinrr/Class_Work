//
//  upd_structures.h
//  sClient
//
//  Created by Kelvin Rodriguez on 11/12/15.
//  Copyright © 2015 Kelvin.rodriguez. All rights reserved.
//

#ifndef upd_structures_h
#define upd_structures_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define gloabal_variable static
#define internal         static
#define local_persist    static

#define true 1
#define false !true

gloabal_variable  uint8_t BUFFER_SIZE = 255;

gloabal_variable uint8_t CMD_ECHO = 0;
gloabal_variable uint8_t CMD_DNS  = 1;
gloabal_variable uint8_t CMD_TIME = 2;

/**
 *  struct packet_arg ----------------
 *  @description:
 *      sruct for holding strings be-
 *      -ing sent over a socket.
 */
typedef struct s_str {
    uint8_t len;
    char str[128];
} __attribute__((packed)) packet_arg;

/**
 *  struct service_packet ------------
 *  @description:
 *      struct that holds the packet 
 *      information to be sent over a
 *      socket.
 */
typedef struct serv_pkt {
    uint8_t cmd;
    size_t argc;
    
    packet_arg arg;
} __attribute__((packed)) service_packet;

/**
 * init_packet_args() ---------------------------------------------------
 * @description:
 *      Function used to initialize a packet struct with sizes and
 *      arguement list to send to the server 
 */
void init_packet_arg(service_packet* dest_pkt, char** args,
                      size_t start, size_t end) {
    //dest_pkt->arg = malloc(sizeof(packet_args) * (end-start));
    dest_pkt->argc = end-start;
    strcpy(dest_pkt->arg.str, args[start]);
    dest_pkt->arg.len = strlen(args[start]);
}

/*  print_pkt() ---------------------------------------------------------
 *  @Desciption:
 *      Fuction to print out a packet data
 *  @params service_packet the pack to be printed out to standard 
 *          output. 
 */
void print_pkt(service_packet packet) {
    printf("Cmd: %s Args: ", (packet.cmd == 0) ? "ECHO" :
           (packet.cmd == 1) ? "DNS"  :
           (packet.cmd == 2) ? "TIME" :
           "N/A");
    // print the arguments
    //for (int i = 0; i < packet.argc; i++)
    printf("%s ", packet.arg.str);
    printf("\n");
}

/**
 * error() --------------------------------------------------------------
 * @description:
 *      for doing errors
 */
void error(char *msg) {
    perror(msg);
    exit(0);
}


#endif /* upd_structures_h */
