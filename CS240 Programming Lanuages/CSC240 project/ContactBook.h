//
//  ContactBook.h
//  CSC240 project
//
//  Created by Kelvin Rodriguez on 10/23/14.
//  Copyright (c) 2014 Kelvin.rodriguez. All rights reserved.
//

#ifndef __CSC240_project__ContactBook__
#define __CSC240_project__ContactBook__

#include <iostream>
#include <stdlib.h>  // malloc is defined in this library
#include <string.h> // string operations are defined in this library

struct contact
{
    char name[30];
    char phone[20];
    char address[50];
    int userID;
    
    struct contact *next;
};

extern char *file_name; // Use a string for file name

// forward declaration
void menu();                // The method prints out a menu list to user
void branching(char c);     // Pass in the character c and use a switch statement to idenifty what what to print to the user
struct contact* find_node(char *str, int *position);
void display_node(struct contact *node, int index);
int deletion();             // Ask the user to delete the name of the person they want to delete.
int modify();               // Print the database to the user and ask the user to insert the name they want to modifty.
int search_name();
void display_all();
void load_file();
void save_file();
int insert();   // Ask the user to insert name of the person and check for duplicates.
                // If there are duplicates throw an error; if there are none check if there is enough memory.
                // After it's successful copy the name into the node.
                // Ask them the telephone number and address and put it into the node.

#endif