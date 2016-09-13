
#include <iostream>
#include <stdlib.h>     // malloc is defined in this library
#include <string.h>     // string operations are defined in this library
#include "ContactBook.h"



#define STACK_SIZE 20
int IDgenerator = 0;
int top = 0, IdStack[STACK_SIZE];
contact *head = NULL;

void push(int val, int* stackTop, int* stack)
{
    
    if(top < STACK_SIZE)
    {
       stack[*stackTop] = val;
       (*stackTop)++;
    }
    else
        printf("The Stack is Full!!!!!!!\n");
    
}

int pop(int* stackTop, int* stack)
{
    if (top > 0)
    {
        (*stackTop)--;
        return stack[top];
    }
    
    printf("Error: stack empty\n");
    return -1;
}


void menu()
{
    printf("\n\nMENU\n");
    printf("----\n");
    printf("i: Insert a new entry.\n");
    printf("d: Delete an entry.\n");
    printf("m: Modify an entry.\n");
    printf("s: Search by name for an entry.\n");
    printf("p: Print all entries.\n");
    printf("q: Quit the program.\n");
    printf("Please enter your choice (i, d, m, s, p, or q) --> ");
}

void branching(char c)
{
    switch(c) {
        case 'i':
            if(insert() != 0)
                printf("INSERTION OPERATION FAILED.\n");
            else
                printf("INSERTED NODE IN THE LIST SUCCESSFULLY.\n");
            break;
        case 'd':
            if(deletion() != 0)
                printf("DELETION OPERATION FAILED.\n");
            else
                printf("DELETED THE ABOVE NODE SUCCESSFULLY.\n");
            break;
        case 'm':
            if(modify() != 0)
                printf("MODIFY OPERATION FAILED.\n"); else
                    printf("MODIFIED THE ABOVE NODE SUCCESSFULLY.\n"); break;
        case 's':
            if(search_name() != 0)
                printf("SEARCH FAILED.\n");
            else
                printf("SEARCH FOR THE NODE SUCCESSFUL.\n"); break;
        case 'p':
            display_all();
            break;
        case 'q':
            save_file();
            break;
        default:
            printf("ERROR - Invalid input.\n");
            printf("Try again.....\n");
            break;
    }
}

int insert()
{
    struct contact *node;
    char sname[30];
    int index = 1;
    
    printf("\nInsertion module...............\n");
    printf("Enter the name of the person to be inserted: ");
    scanf("%s", sname);
    
    node = find_node(sname, &index); // find duplicates
    if(node != NULL)
    {
        printf("ERROR - Duplicate entry not allowed.\n");
        printf("A entry is found in the list at index %d.\n", index);
        display_node(node, index);
        return -1;
    }
    else
    {
        struct contact* nodePointer = head;
        node = (struct contact*) malloc(sizeof(struct contact));
        
        if(head == NULL)
        {
            head = node;
            node->next = NULL;
        }
        
        else if(strcmp(sname, nodePointer->name) < 0)
        {
            node->next = head;
            head = node;
        }
        
        else if (head->next != NULL)
        {
            while(nodePointer->next != NULL)
            {
                if(strcmp(sname, nodePointer->next->name) < 0)
                {
                    struct contact* temp = nodePointer->next;
                    nodePointer->next = node;
                    node->next = temp;
                    break;
                }
                nodePointer = nodePointer->next;
            }
        }
        
        else
        {
            while (nodePointer->next != NULL) {
                nodePointer = nodePointer->next;
            }
            
            nodePointer->next = node;
            node->next = NULL;
        }
        
        
        strcpy(node->name, sname);
        printf("Enter telephone number: ");
        scanf("%s", node->phone);
        printf("Enter address: ");
        scanf("%s", node->address);
        
        if(top < 1)
        {
            node->userID = IDgenerator;
            IDgenerator++;
        }
        else
            node->userID = pop(&top, IdStack);
        
        return 0;
    }
}

int deletion()
{
    char sname[30];
    struct contact *temp, *prev = nullptr;
    int index = 1;
    printf("\nDeletion module...............\n");
    printf("Please enter the name of the person to be deleted: ");
    scanf("%s", sname);
    temp = head;
    
    while (temp != NULL)
        if (strcmp(sname, temp->name) != 0) // case insensitive strcmp
        {
            prev = temp;
            temp = temp->next;
            index++;
        }
    
        else
        {
            printf("Person to be deleted is found at index %d.", index);
            display_node(temp, index);
            if(temp != head)
                prev->next = temp->next;
            else
                head = head->next;
            
            push(temp->userID, &top, IdStack);
            
            free(temp);
            return 0;
        }
    
    printf("The person with name '%s' does not exist.\n", sname);
    return -1; }


int modify()
{
    struct contact *node;
    char sname[30];
    int index = 1;
    
    printf("\nModification module...............\n");
    printf("Enter the name whose record is to be modified in the\n");
    printf("database: ");
    scanf("%s", sname);
    node = find_node(sname, &index);
    if(node != NULL) {
        printf("Person to be modified is found at index %d.", index);
        display_node(node, index);
        printf("\nEnter the new telephone number of this person: ");
        scanf("%s", node->phone);
        printf("Enter the new address of this person: ");
        scanf("%s", node->address);
        return 0;
    }
    else {
        printf("The person with name '%s' does not exist \n", sname);
        printf("database.\n");
        return -1;
    }
}

int search_name()
{
    struct contact *node;
    char sname[30];
    int index = 1;
    printf("\nSearch_name module...............\n");
    printf("Please enter the name to be searched in the database: ");
    scanf("%s", sname);
    node = find_node(sname, &index);
    
    if(node != NULL)
    {
        printf("Person searched is found at index %d.", index);
        display_node(node, index);
        return 0;
    }
    else
    {
        printf("The person '%s' does not exist.\n", sname);
        return -1;
    }
    
}

void display_all()
{
    struct contact *node;
    int counter = 0;
    printf("\nDisplay module...............");
    node = head;
    while(node != NULL) {
        display_node(node, ++counter);
        node = node->next;
    }
    printf("\nNo more records.\n");
}

void load_file()
{
    FILE *file_descriptor;
    struct contact *node, *temp = nullptr;
    char str[30];
    file_descriptor = fopen(file_name, "r");
    
    
    if(file_descriptor != NULL)
    {
        while(fread(str, 30, 1, file_descriptor) == 1) {
            node = (struct contact*) malloc(sizeof(struct contact));
            strcpy(node->name, str);
            fread(node->phone, 20, 1, file_descriptor);
            fread(node->address, 50, 1, file_descriptor);
            fread(&node->userID, sizeof(int), 1, file_descriptor);
            if(head != NULL)
                temp->next = node;
            else
                head = node;
            node->next = NULL;
            temp = node;
        }
        
        fclose(file_descriptor);
    }
}

void save_file() {
    FILE *file_descriptor;
    struct contact *node;
    file_descriptor = fopen(file_name, "w");
    if(file_descriptor != NULL)
    {
        node = head;
        while(node != NULL)
        {
            fwrite(node->name, 30, 1, file_descriptor);
            fwrite(node->phone, 20, 1, file_descriptor);
            fwrite(node->address, 50, 1, file_descriptor);
            fwrite(&node->userID, sizeof(int), 1, file_descriptor);
            node = node->next;
        }
    }
    else
    {
        printf("\nERROR - Could not open file for saving data !\n");
        getchar();
        exit(-1);
    }
}

struct contact* find_node(char *str, int *position)
{
    struct contact *temp = head;
    while (temp != NULL) {
        if (strcmp(str, temp->name) != 0) // case insensitive strcmp
        {
            temp = temp->next;
            (*position)++;
        }
        else
            return temp;
    }
    return NULL;
}

void display_node(struct contact *node, int index)
{
    printf("\nRECORD %d:\n", index);
    printf("\t\tName:\t\t%s\n", node->name);
    printf("\t\tTelephone:\t%s\n", node->phone);
    printf("\t\tAddress:\t%s\n", node->address);
    printf("\t\tID:\t%d\n", node->userID);
}










