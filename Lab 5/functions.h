/**************************
*Justin Sabia                                 *
*CPSC 2310 Spring 23 *
*UserName: jsabia
#email: jsabia@clemson.edu                               *
*Instructor:  Dr. Yvon Feaster  *
*************************/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//add birthday struct here
typedef struct birthday {
    
    char month[20];
    char day[3];
    char year[4];

} birthday_t;


//add node_t struct here (this struct will represent a node in the
//linked list)
typedef struct node_t {
    
    char firstName[50];
    char lastName[50];
    char major[50];
    char classStanding[50];
    struct node_t *next;
    birthday_t bday;

} node_t;

//New node for storing stats 
typedef struct list_stats_t {

    node_t* oldestPerson;
    node_t* youngestPerson;
    int birthdaysInMonth[12];

} list_stats_t;



//implement these:
void add(node_t **node, node_t **head);
node_t* readNodeInfo(FILE* input);
node_t* createList(FILE*, node_t**);
void printList(FILE*, node_t*);
void printBorder(FILE*);
void deleteList(node_t**);
//New functions
int compare_by_lastname(node_t *a, node_t *b);
int compare_by_firstname(node_t *a, node_t *b);
bool checkInvalidDate(node_t *node);
int daysInMonth(int month, int year);
void swapNode(node_t **a, node_t **b);
void sortList(node_t **head, int (*comp)(node_t *, node_t *));

#endif