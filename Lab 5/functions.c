/**************************
*Justin Sabia                                 *
*CPSC 2310 Spring 23 *
*UserName: jsabia
#email: jsabia@clemson.edu                               *
*Instructor:  Dr. Yvon Feaster  *
*************************/

#include "functions.h"

//Function to add nodes to the list
void add(node_t** node, node_t** head) {

    if(*head == NULL) {
        *head = *node;
    }
    else {
        node_t* new = *head;

        while (!(new -> next == NULL)) {
            new = new -> next;
        }
        new -> next = *node;
    }
}

//Use scanset to read in data from the CSV file
node_t* readNodeInfo(FILE* input) {
    node_t* node1 = (node_t*)malloc(sizeof(node_t));
    //Check that all 7 items for the person are read in correctly 
    if (fscanf(input, "%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^\n]\n", 
               node1->lastName, node1->firstName, node1->bday.month, node1->bday.day, 
               node1->bday.year, node1->major, node1->classStanding) != 7) {
        // Not all fields were successfully read
        free(node1);
        return NULL;
    }

    if (!checkInvalidDate(node1)) {
        // Invalid date
        free(node1);
        return NULL;
    }

    return node1;
}

//Create the list by adding nodes to it
node_t* createList(FILE* input, node_t** list) {

    while(!feof(input)) {

        node_t* node = NULL;
        node = readNodeInfo(input);
        add(&node, list);
    }

    return *list;
}

//Print out the list based on the data stored in previous functions
void printList(FILE* output, node_t* list) {

    node_t* node = list;

    //If there are no nodes in the list it will return an error
    if (list == NULL) {
        fprintf(stderr, "List is empty.\n");
        exit(1);
    }

    printBorder(output);
    fprintf(output, "\nList Info:\n");

    while (node != NULL) {
        fprintf(output, "Name:\t%s %s\n", node -> firstName, node -> lastName);
        fprintf(output, "Date of Birth:\t%s %s, %s\n", node -> bday.month, node -> bday.day, node -> bday.year);
        fprintf(output, "Major:\t%s\n", node -> major);
        fprintf(output, "Year:\t%s\n", node -> classStanding);
        fprintf(output, "\n");
        
        node = node -> next;
    }

    printBorder(output);
}

//Print boarder at the top and bottom of the output file
void printBorder(FILE* out) {

    int i = 0;

    for(i = 0; i < 80; i++)
        fprintf(out,"*");
    
    fprintf(out, "\n");
}

//Delete the list, releasing any stored memory
//this ensures no memory leaks
void deleteList(node_t** node) {

    node_t* temp = *node;
    node_t* next = NULL;

    while(temp != NULL) {

        next = temp -> next;
        free(temp);
        temp = next;
    }
}

//User to sort users by their first name
int compare_by_lastname(node_t* a, node_t* b) {
    return strcmp(a -> lastName, b -> lastName);
}

//User to sort users by their first name
int compare_by_firstname(node_t* a, node_t* b) {
    return strcmp(a -> firstName, b -> firstName);
}

//sortList will use a bubble sort function to sort through
//the list comparing and replacing nodes using a function pointer to
//compare_by_firstname and compare_by_lastname that will be implemented
//in driver.c
void sortList(node_t** head, int (*comp)(node_t*, node_t*)) {

    if (*head == NULL || (*head) -> next == NULL) {
        return;
    }

    node_t *prev, *curr, *next;
    int swap;

    do {
        swap = 0;
        prev = NULL;
        curr = *head;
        while (curr -> next != NULL) {
            next = curr -> next;
            if (comp(curr, next) > 0) {
                swap = 1;
                curr -> next = next -> next;
                next -> next = curr;
                if (prev == NULL) {
                    *head = next;
                }
                else {
                    prev -> next = next;
                }
                prev = next;
            }
            else {
                prev = curr;
                curr = next;
            }
        }
    }
    while (swap);

}

#include "functions.h"

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//Check for valid dates
//Function will determine how many days are in a typical month as well
//as odd months
//function will account for leap leap years to determine how many days are in the month
bool checkInvalidDate(node_t *node) {

    int day = atoi(node->bday.day);
    int year = atoi(node->bday.year);

    // Check if the year is a leap year
    bool isLeapYear = false;

    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                isLeapYear = true;
            }
        }

        else {
            isLeapYear = true;
        }
    }

    // Check if the day is valid for the given month
    int month = atoi(node->bday.month);
    int maxDays;

    switch (month) {
        case 2:
            maxDays = isLeapYear ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            maxDays = 30;
            break;
        default:
            maxDays = 31;
        break;
    }

    if (day < 1 || day > maxDays) {
        return false;
    }

    return true;
}

