#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "variables.h"
#include "threads.h"

//  THIS C FILE CONTAINS THE MAIN FUNCTION

int main(int argc, char *argv[]) 
{
    pthread_t tid1, tid2, tid3, tid4; // thread identifiers
    int delay;
    int total_valid = 0;  // Counter for total valid rows, columns, and sub-grids
    char *stat_messages[4];  // validation status for each thread

    if (argc < 3 || argc > 3) // command line args, if its less than 3 then its invalid and i
    {
        fprintf(stderr, "Usage: %s <sudoku_input_file> <delay>\n", argv[0]); // the correct input
        return 1;
    }

    
    delay = atoi(argv[2]); // used to delay the program
    if (delay > 10)
    {
        fprintf(stderr,"delay cant be larger than 10\n");
        return 1;
    }
    printf("Delay set to: %d seconds]\n", delay);

    // Allocate initial memory for status messages
    for (int i = 0; i < 4; i++) 
    {
        stat_messages[i] = malloc(50); // Initial allocation
        if (stat_messages[i] == NULL) 
        {
            fprintf(stderr, "Failed to allocate memory for stat_messages[%d]\n", i);
            return 1;
        }
        sprintf(stat_messages[i], "Thread ID-%d: valid", i+1); // Initialize messages as valid
    }

    parameters param1 = {0, 2, delay}; // for thread 1
    parameters param2 = {3, 5, delay}; // for thread 2
    parameters param3 = {6, 8, delay}; // for thread 3
    parameters param4 = {0, 8, delay}; // for thread 4

    pthread_mutex_init(&lock, NULL); // for synchronisation
    pthread_cond_init(&cond, NULL); // may remove this read more about it IMPORTANT

    readFromFile(argv[1]);  // read suduku grid from file


    // expplanation of the code below:
    // first arg is a pointer to a pthread variable where the thread ID will be stored
    // second arg specifies thraed attributes, NULL is used for default attributes
    // the third arg is a pointer to the function that the thread will execute such as thread 1, 2, 3 or 4
    // the fourth arg is a pointer for the data that needs to be passed to the thread function which are the parameters
    pthread_create(&tid1, NULL, validate_thread1, &param1); // create the first thread, 
    pthread_create(&tid2, NULL, validate_thread2, &param2); // create the second thread
    pthread_create(&tid3, NULL, validate_thread3, &param3); // create the third thread
    pthread_create(&tid4, NULL, validate_thread4, &param4); // create the fourth thread

    // explanation of the code: we are just joining the threads
    pthread_join(tid1, NULL); 
    pthread_join(tid2, NULL); 
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    // using a delay for the program
    sleep(delay);

    // Collecting results from threads
    total_valid = Counter;

    // the lines below are used to print out when the suduku is valid or invalid
    // Check for any invalid rows, columns, or sub-grids
    // this loop interates over each index i from 0 to 8
    for (int i = 0; i < 9; i++) 
    {
    if (!validRow[i]) 
    {
        char *temp = realloc(stat_messages[i / 3], strlen(stat_messages[i / 3]) + 50);
        if (temp != NULL) 
        {
            stat_messages[i / 3] = temp;
            sprintf(stat_messages[i / 3], "%s, row %d is invalid", stat_messages[i / 3], i + 1);
        } else 
        {
            fprintf(stderr, "Failed to realloc memory for row %d\n", i);
        }
    }
    if (!validCol[i]) 
    {
        char *temp = realloc(stat_messages[3], strlen(stat_messages[3]) + 50);
        if (temp != NULL) 
        {
            stat_messages[3] = temp;
            sprintf(stat_messages[3], "%s, column %d is invalid", stat_messages[3], i + 1);
        } else 
        {
            fprintf(stderr, "Failed to realloc memory for column %d\n", i);
        }
    }
    if (!validSub[i]) 
    {
        char *temp = realloc(stat_messages[i / 3], strlen(stat_messages[i / 3]) + 50);
        if (temp != NULL) 
        {
            stat_messages[i / 3] = temp;
            sprintf(stat_messages[i / 3], "%s, sub-grid %d is invalid", stat_messages[i / 3], i + 1);
        } else 
        {
            fprintf(stderr, "Failed to realloc memory for sub-grid %d\n", i);
        }
    }
}


    // Print the results
    for (int i = 0; i < 4; i++) {
    printf("%s\n", stat_messages[i]);
    }
    char *validity = "invalid";
    if (total_valid == 27) {
        validity = "valid";
    }
    printf("There are %d valid sub-grids, and thus the solution is %s.\n", total_valid, validity);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    // Free allocated memory
    for (int i = 0; i < 4; i++) 
    {
        free(stat_messages[i]);
    }

    return 0;
}




