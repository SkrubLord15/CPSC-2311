/**************************
*Justin Sabia                                 *
*CPSC 2310 Spring 23 *
*UserName: jsabia
#email: jsabia@clemson.edu                               *
*Instructor:  Dr. Yvon Feaster  *
*************************/

#include <stdio.h>
#include <assert.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    
    node_t* head = NULL;
    //node_t* temp = NULL;

    assert(argc == 3);

    FILE* input = fopen(argv[1], "r");
    assert(input != NULL);

    FILE* output = fopen(argv[2], "w");
    assert(output != NULL);

    //int sort_option = atoi(argv[3]);
    //assert(sort_option == 1 || sort_option == 2);

    createList(input, &head);

    /*
    //If 1 is selected the list will be sorted by the first name
    if (sort_option == 1) {
        sortList(&head, compare_by_firstname);
    }  
    //ele it will be sorted by the last name
    else if (sort_option == 2) {
        sortList(&head, compare_by_lastname);
    }
    */

    // Get list stats
    list_stats_t stats = getListStats(head);

    // Print list stats
    printStats(output, &stats);

    // Delete list
    deleteList(&head);

    fclose(input);
    fclose(output);

    return 0;
}

