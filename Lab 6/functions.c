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

/*Gets the stats from the .csv file
//It will compare all users to find the oldest and youngest
and update the count of how many users have a birthday on a certain month*/ 
list_stats_t getListStats(node_t *head) {
    list_stats_t stats = {NULL, NULL, {0}};
    node_t *curr = head;

    if (head == NULL) {
        return stats;
    }

    // Set oldestPerson and youngestPerson to the first person in the list
    stats.oldestPerson = curr;
    stats.youngestPerson = curr;

    while (curr != NULL) {
        // Check if curr node's birthday is earlier than oldestPerson's birthday
        if (strcmp(curr->bday.year, stats.oldestPerson->bday.year) < 0 ||
            (strcmp(curr->bday.year, stats.oldestPerson->bday.year) == 0 &&
             strcmp(curr->bday.month, stats.oldestPerson->bday.month) < 0) ||
            (strcmp(curr->bday.year, stats.oldestPerson->bday.year) == 0 &&
             strcmp(curr->bday.month, stats.oldestPerson->bday.month) == 0 &&
             strcmp(curr->bday.day, stats.oldestPerson->bday.day) < 0)) {
            stats.oldestPerson = curr;
        }

        // Check if curr node's birthday is later than youngestPerson's birthday
        if (strcmp(curr->bday.year, stats.youngestPerson->bday.year) > 0 ||
            (strcmp(curr->bday.year, stats.youngestPerson->bday.year) == 0 &&
             strcmp(curr->bday.month, stats.youngestPerson->bday.month) > 0) ||
            (strcmp(curr->bday.year, stats.youngestPerson->bday.year) == 0 &&
             strcmp(curr->bday.month, stats.youngestPerson->bday.month) == 0 &&
             strcmp(curr->bday.day, stats.youngestPerson->bday.day) > 0)) {
            stats.youngestPerson = curr;
        }

        // Update birthday count for month
        if (strcmp(curr->bday.month, "January") == 0) {
            stats.birthdaysInMonth[0]++;
        } else if (strcmp(curr->bday.month, "February") == 0) {
            stats.birthdaysInMonth[1]++;
        } else if (strcmp(curr->bday.month, "March") == 0) {
            stats.birthdaysInMonth[2]++;
        } else if (strcmp(curr->bday.month, "April") == 0) {
            stats.birthdaysInMonth[3]++;
        } else if (strcmp(curr->bday.month, "May") == 0) {
            stats.birthdaysInMonth[4]++;
        } else if (strcmp(curr->bday.month, "June") == 0) {
            stats.birthdaysInMonth[5]++;
        } else if (strcmp(curr->bday.month, "July") == 0) {
            stats.birthdaysInMonth[6]++;
        } else if (strcmp(curr->bday.month, "August") == 0) {
            stats.birthdaysInMonth[7]++;
        } else if (strcmp(curr->bday.month, "September") == 0) {
            stats.birthdaysInMonth[8]++;
        } else if (strcmp(curr->bday.month, "October") == 0) {
            stats.birthdaysInMonth[9]++;
        } else if (strcmp(curr->bday.month, "November") == 0) {
            stats.birthdaysInMonth[10]++;
        } else if (strcmp(curr->bday.month, "December") == 0) {
            stats.birthdaysInMonth[11]++;
        }
        curr = curr->next;
    }
    return stats;
}

/*Print the stats of the youngest and oldest person in the list
and print out the number of users per month*/
void printStats(FILE* outputFile, list_stats_t* stats) {
    // check if the list is empty
    if (stats->oldestPerson == NULL && stats->youngestPerson) {
        fprintf(outputFile, "None\n\n");
        return;
    }

    //Print border
    printBorder(outputFile);
    // print oldest person information
    fprintf(outputFile, "List Statistics:\n");
    fprintf(outputFile, "----------Oldest Person----------\n");
    fprintf(outputFile, "Name:\t%s %s\n", stats->oldestPerson->firstName, stats->oldestPerson->lastName);
    fprintf(outputFile, "Date of Birth:\t%s %s, %s\n", stats->oldestPerson->bday.month, stats->oldestPerson->bday.day, stats->oldestPerson->bday.year);
    fprintf(outputFile, "Major:\t%s\n", stats->oldestPerson->major);
    fprintf(outputFile, "Year:\t%s\n", stats->oldestPerson->classStanding);

    // print youngest person information
    fprintf(outputFile, "----------Youngest Person----------\n");
    fprintf(outputFile, "Name:\t%s %s\n", stats->youngestPerson->firstName, stats->youngestPerson->lastName);
    fprintf(outputFile, "Date of Birth:\t%s %s, %s\n", stats->youngestPerson->bday.month, stats->youngestPerson->bday.day, stats->youngestPerson->bday.year);
    fprintf(outputFile, "Major:\t%s\n", stats->youngestPerson->major);
    fprintf(outputFile, "Year:\t%s\n", stats->youngestPerson->classStanding);

    // print birthday counts
    fprintf(outputFile, "----------Birthday Counts----------\n");
    fprintf(outputFile, "January: %d\n", stats->birthdaysInMonth[0]);
    fprintf(outputFile, "February: %d\n", stats->birthdaysInMonth[1]);
    fprintf(outputFile, "March: %d\n", stats->birthdaysInMonth[2]);
    fprintf(outputFile, "April: %d\n", stats->birthdaysInMonth[3]);
    fprintf(outputFile, "May: %d\n", stats->birthdaysInMonth[4]);
    fprintf(outputFile, "June: %d\n", stats->birthdaysInMonth[5]);
    fprintf(outputFile, "July: %d\n", stats->birthdaysInMonth[6]);
    fprintf(outputFile, "August: %d\n", stats->birthdaysInMonth[7]);
    fprintf(outputFile, "September: %d\n", stats->birthdaysInMonth[8]);
    fprintf(outputFile, "October: %d\n", stats->birthdaysInMonth[9]);
    fprintf(outputFile, "November: %d\n", stats->birthdaysInMonth[10]);
    fprintf(outputFile, "December: %d\n", stats->birthdaysInMonth[11]);

    //Print boarder
    printBorder(outputFile);
}

