#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "variables.h"
#include "threads.h"

int main(int argc, char *argv[]) {
    pthread_t tid1, tid2;
    int delay;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <sudoku_input_file> <delay>\n", argv[0]);
        return EXIT_FAILURE;
    }

    delay = atoi(argv[2]); // Convert the delay input from string to integer

    parameters param1 = {0, 2, delay};
    parameters param2 = {3, 5, delay};

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    readFromFile(argv[1]);  // Read the Sudoku grid from file

    pthread_create(&tid1, NULL, validate_thread1, &param1);
    pthread_create(&tid2, NULL, validate_thread2, &param2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}

