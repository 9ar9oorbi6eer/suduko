#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "variables.h"
#include "threads.h"

// Main function
int main(int argc, char *argv[]) {
    
    pthread_t tid1;
    parameters param1 = {0, 2, 0, 2, 1};
    
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <sudoku_input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    readFromFile(argv[1]);  // Read the Sudoku grid from file

    pthread_create(&tid1, NULL, validate_thread1, &param1);
    pthread_join(tid1, NULL);

    // Read the Sudoku grid from the provided file
    readFromFile(argv[1]);


    printf("Thread ID-1: ");
        for (int i = 0; i < 3; i++) {
            if (validRow[i] && validSub[i]) {
                printf("row %d, sub-grid %d are valid\n", i+1, i+1);
            } else {
                printf("row %d, sub-grid %d are invalid\n", i+1, i+1);
            }
        }

        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&cond);

    return 0;
}


