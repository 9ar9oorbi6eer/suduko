#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "variables.h"
#include "threads.h"

int main(int argc, char *argv[]) {
    pthread_t tid1, tid2, tid3, tid4;
    int delay;
    int total_valid = 0;  // Counter for total valid rows, columns, and sub-grids
    char *status_messages[4];  // Messages to store validation status for each thread

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <sudoku_input_file> <delay>\n", argv[0]);
        return EXIT_FAILURE;
    }

    delay = atoi(argv[2]);
    printf("Delay set to: %d seconds]\n", delay);

    // Allocate initial memory for status messages
    for (int i = 0; i < 4; i++) {
        status_messages[i] = malloc(50); // Initial allocation
        if (status_messages[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for status_messages[%d]\n", i);
            exit(EXIT_FAILURE);
        }
        sprintf(status_messages[i], "Thread ID-%d: valid", i+1); // Initialize messages as valid
    }

    parameters param1 = {0, 2, delay};
    parameters param2 = {3, 5, delay};
    parameters param3 = {6, 8, delay};
    parameters param4 = {0, 8, delay};  // Columns 1-9

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    readFromFile(argv[1]);  // Implement this function to read the Sudoku grid from file

    pthread_create(&tid1, NULL, validate_thread1, &param1);
    pthread_create(&tid2, NULL, validate_thread2, &param2);
    pthread_create(&tid3, NULL, validate_thread3, &param3);
    pthread_create(&tid4, NULL, validate_thread4, &param4);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    sleep(delay);

    // Collecting results from threads
    total_valid = Counter;

    // Check for any invalid rows, columns, or sub-grids
    for (int i = 0; i < 9; i++) {
        if (!validRow[i]) {
            char *temp = realloc(status_messages[i / 3], strlen(status_messages[i / 3]) + 50);
            if (temp == NULL) {
                fprintf(stderr, "Failed to realloc memory for row %d\n", i);
                continue;
            }
            status_messages[i / 3] = temp;
            sprintf(status_messages[i / 3], "%s, row %d is invalid", status_messages[i / 3], i + 1);
        }
        if (!validCol[i]) {
            char *temp = realloc(status_messages[3], strlen(status_messages[3]) + 50);
            if (temp == NULL) {
                fprintf(stderr, "Failed to realloc memory for column %d\n", i);
                continue;
            }
            status_messages[3] = temp;
            sprintf(status_messages[3], "%s, column %d is invalid", status_messages[3], i + 1);
        }
        if (!validSub[i]) {
            char *temp = realloc(status_messages[i / 3], strlen(status_messages[i / 3]) + 50);
            if (temp == NULL) {
                fprintf(stderr, "Failed to realloc memory for sub-grid %d\n", i);
                continue;
            }
            status_messages[i / 3] = temp;
            sprintf(status_messages[i / 3], "%s, sub-grid %d is invalid", status_messages[i / 3], i + 1);
        }
    }

    // Print the results
    for (int i = 0; i < 4; i++) {
        printf("%s\n", status_messages[i]);
    }
    printf("There are %d valid sub-grids, and thus the solution is %s.\n",
           total_valid, (total_valid == 27 ? "valid" : "invalid"));

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    // Free allocated memory
    for (int i = 0; i < 4; i++) {
        free(status_messages[i]);
    }

    return 0;
}






// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>
// #include "variables.h"
// #include "threads.h"

// int main(int argc, char *argv[]) {
//     pthread_t tid1, tid2, tid3, tid4;
//     int delay;
//     int total_valid = 0;  // Counter for total valid rows, columns, and sub-grids
//     char *status_messages[4];  // Messages to store validation status for each thread

//     if (argc < 3) {
//         fprintf(stderr, "Usage: %s <sudoku_input_file> <delay>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

//     delay = atoi(argv[2]);
//     // also this is for debugging may have to remove later
//     printf("Delay set to: %d seconds]\n", delay);

//     parameters param1 = {0, 2, delay};
//     parameters param2 = {3, 5, delay};
//     parameters param3 = {6, 8, delay};
//     parameters param4 = {0, 8, delay};  // Columns 1-9

//     pthread_mutex_init(&lock, NULL);
//     pthread_cond_init(&cond, NULL);

//     readFromFile(argv[1]);  // Implement this function to read the Sudoku grid from file

//     pthread_create(&tid1, NULL, validate_thread1, &param1);
//     pthread_create(&tid2, NULL, validate_thread2, &param2);
//     pthread_create(&tid3, NULL, validate_thread3, &param3);
//     pthread_create(&tid4, NULL, validate_thread4, &param4);

//     pthread_join(tid1, NULL);
//     pthread_join(tid2, NULL);
//     pthread_join(tid3, NULL);
//     pthread_join(tid4, NULL);

//     // may remove this i added this, and it worked for the delay, but check again IMPORTANT
//     sleep(delay);

//     // Collecting results from threads
//     total_valid = Counter;  // Assuming Counter is incremented by each thread correctly

//     // Initialize messages as valid
//     status_messages[0] = "Thread ID-1: valid";
//     status_messages[1] = "Thread ID-2: valid";
//     status_messages[2] = "Thread ID-3: valid";
//     status_messages[3] = "Thread ID-4: valid";

//     // Check for any invalid rows, columns, or sub-grids
//     for (int i = 0; i < 9; i++) {
//         if (!validRow[i]) {
//             status_messages[i / 3] = (char*) realloc(status_messages[i / 3], 
//                                 strlen(status_messages[i / 3]) + 50);
//             sprintf(status_messages[i / 3], "%s, row %d is invalid", status_messages[i / 3], i + 1);
//         }
//         if (!validCol[i]) {
//             status_messages[3] = (char*) realloc(status_messages[3], 
//                                 strlen(status_messages[3]) + 50);
//             sprintf(status_messages[3], "%s, column %d is invalid", status_messages[3], i + 1);
//         }
//         if (!validSub[i]) {
//             status_messages[i / 3] = (char*) realloc(status_messages[i / 3], 
//                                 strlen(status_messages[i / 3]) + 50);
//             sprintf(status_messages[i / 3], "%s, sub-grid %d is invalid", status_messages[i / 3], i + 1);
//         }
//     }

//     // Print the results
//     for (int i = 0; i < 4; i++) {
//         printf("%s\n", status_messages[i]);
//     }
//     printf("There are %d valid sub-grids, and thus the solution is %s.\n",
//            total_valid, (total_valid == 27 ? "valid" : "invalid"));

//     pthread_mutex_destroy(&lock);
//     pthread_cond_destroy(&cond);

//     return 0;
// }






// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <pthread.h>
// // #include <unistd.h>
// // #include "variables.h"
// // #include "threads.h"

// // int main(int argc, char *argv[]) {
// //     pthread_t tid1, tid2, tid3, tid4;  // Adding thread identifier for Thread 4
// //     int delay;

// //     if (argc < 3) {
// //         fprintf(stderr, "Usage: %s <sudoku_input_file> <delay>\n", argv[0]);
// //         return EXIT_FAILURE;
// //     }

// //     delay = atoi(argv[2]); // Convert the delay input from string to integer

// //     parameters param1 = {0, 2, delay};  // Parameters for Thread 1
// //     parameters param2 = {3, 5, delay};  // Parameters for Thread 2
// //     parameters param3 = {6, 8, delay};  // Parameters for Thread 3
// //     parameters param4 = {0, 8, delay};  // Parameters for Thread 4 (all columns)

// //     pthread_mutex_init(&lock, NULL);
// //     pthread_cond_init(&cond, NULL);

// //     readFromFile(argv[1]);  // Read the Sudoku grid from file

// //     pthread_create(&tid1, NULL, validate_thread1, &param1);
// //     pthread_create(&tid2, NULL, validate_thread2, &param2);
// //     pthread_create(&tid3, NULL, validate_thread3, &param3);
// //     pthread_create(&tid4, NULL, validate_thread4, &param4);  // Create Thread 4

// //     pthread_join(tid1, NULL);
// //     pthread_join(tid2, NULL);
// //     pthread_join(tid3, NULL);
// //     pthread_join(tid4, NULL);  // Ensure main waits for Thread 4 to complete

// //     pthread_mutex_destroy(&lock);
// //     pthread_cond_destroy(&cond);

// //     return 0;
// // }