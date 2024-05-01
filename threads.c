#include "variables.h"
#include "threads.h"


// thread 1
void *validate_thread1(void *args) 
{
    parameters *param = (parameters *)args;
    int start_row = param->start_row;
    int end_row = param->end_row;
    int delay = param->delay;

    printf("Thread 1 started\n"); // Print at the start of thread

    // Validate rows
    for (int i = start_row; i <= end_row; i++) 
    {
        if (check_validity(Sol[i])) 
        {
            pthread_mutex_lock(&lock);
            validRow[i] = 1;
            Counter++;
            pthread_mutex_unlock(&lock);
            printf("Thread 1 validating row %d: valid\n", i + 1);
        }
        else 
        {
            printf("Thread 1 validating row %d: invalid\n", i + 1);
        }
        sleep(delay);  // Include delay after validating each row
    }

    // Validate sub-grids 1, 2, 3
    for (int sub = 0; sub < 3; sub++) 
    {
        int subGrid[GRID_SIZE];
        int idx = 0;
        for (int i = sub / 3 * 3; i < sub / 3 * 3 + 3; i++) 
        {
            for (int j = sub % 3 * 3; j < sub % 3 * 3 + 3; j++) 
            {
                subGrid[idx++] = Sol[i][j];
            }
        }
        if (check_validity(subGrid)) 
        {
            pthread_mutex_lock(&lock);
            validSub[sub] = 1;
            Counter++;
            pthread_mutex_unlock(&lock);
            printf("Thread 1 validating sub-grid %d: valid\n", sub + 1);
        }
        else 
        {
            printf("Thread 1 validating sub-grid %d: invalid\n", sub + 1);
        }
        sleep(delay);  // Include delay after validating each sub-grid
    }

    printf("Thread 1 completed\n"); // Print at the end of thread
    return NULL;
}

void *validate_thread2(void *args) 
{
    parameters *param = (parameters *)args;
    int start_row = param->start_row;
    int end_row = param->end_row;
    int delay = param->delay;

    printf("Thread 2 started\n"); // Print at the start of thread

    // Validate rows
    for (int i = start_row; i <= end_row; i++) 
    {
        if (check_validity(Sol[i])) 
        {
            pthread_mutex_lock(&lock);
            validRow[i] = 1;
            Counter++;
            pthread_mutex_unlock(&lock);
            printf("Thread 2 validating row %d: valid\n", i + 1);
        }
        else 
        {
            printf("Thread 2 validating row %d: invalid\n", i + 1);
        }
        sleep(delay);
    }

    // Validate sub-grids
    for (int sub = 3; sub < 6; sub++) 
    {
        int subGrid[GRID_SIZE];
        int idx = 0;
        for (int i = sub / 3 * 3; i < sub / 3 * 3 + 3; i++) 
        {
            for (int j = sub % 3 * 3; j < sub % 3 * 3 + 3; j++) 
            {
                subGrid[idx++] = Sol[i][j];
            }
        }
        if (check_validity(subGrid)) 
        {
            pthread_mutex_lock(&lock);
            validSub[sub] = 1;
            Counter++;
            pthread_mutex_unlock(&lock);
            printf("Thread 2 validating sub-grid %d: valid\n", sub + 1);
        }
        else 
        {
            printf("Thread 2 validating sub-grid %d: invalid\n", sub + 1);
        }
        sleep(delay);
    }

    printf("Thread 2 completed\n"); // Print at the end of thread
    return NULL;
}
// thread 3
void *validate_thread3(void *args)
{
    parameters *param = (parameters *)args;
    int start_row = param->start_row;
    int end_row = param->end_row;
    int delay = param->delay;

    printf("Thread 3 started\n"); // Print at the start of thread

    // Validate rows 7, 8, and 9
    for (int i = start_row; i <= end_row; i++) 
    {
        if (check_validity(Sol[i])) 
        {
            pthread_mutex_lock(&lock);
            validRow[i] = 1;
            Counter++;
            pthread_mutex_unlock(&lock);
            printf("Thread 3 validating row %d: valid\n", i + 1);
        }
        else 
        {
            printf("Thread 3 validating row %d: invalid\n", i + 1);
        }
        sleep(delay);  // Include delay after validating each row
    }

    // Validate sub-grids 7, 8, and 9
    for (int sub = 6; sub < 9; sub++) 
    {
        int subGrid[GRID_SIZE];
        int idx = 0;
        for (int i = sub / 3 * 3; i < sub / 3 * 3 + 3; i++) 
        {
            for (int j = sub % 3 * 3; j < sub % 3 * 3 + 3; j++) 
            {
                subGrid[idx++] = Sol[i][j];
            }
        }
        if (check_validity(subGrid)) 
        {
            pthread_mutex_lock(&lock);
            validSub[sub] = 1;
            Counter++;
            pthread_mutex_unlock(&lock);
            printf("Thread 3 validating sub-grid %d: valid\n", sub + 1);
        }
        else 
        {
            printf("Thread 3 validating sub-grid %d: invalid\n", sub + 1);
        }
        sleep(delay);  // Include delay after validating each sub-grid
    }

    printf("Thread 3 completed\n"); // Print at the end of thread
    return NULL;
}


// // thread 1
// void *validate_thread1(void *args) 
// {
//     parameters *param = (parameters *)args;
//     int start_row = param->start_row;
//     int end_row = param->end_row;
//     int delay = param->delay;

//     // Validate rows
//     for (int i = start_row; i <= end_row; i++) 
//     {
//         if (check_validity(Sol[i])) 
//         {
//             pthread_mutex_lock(&lock);
//             validRow[i] = 1;
//             Counter++;
//             pthread_mutex_unlock(&lock);
//         }
//         sleep(delay);  // Include delay after validating each row
//     }

//     // Validate sub-grids 1, 2, 3
//     for (int sub = 0; sub < 3; sub++) 
//     {
//         int subGrid[GRID_SIZE];
//         int idx = 0;
//         for (int i = sub / 3 * 3; i < sub / 3 * 3 + 3; i++) 
//         {
//             for (int j = sub % 3 * 3; j < sub % 3 * 3 + 3; j++) 
//             {
//                 subGrid[idx++] = Sol[i][j];
//             }
//         }
//         if (check_validity(subGrid)) 
//         {
//             pthread_mutex_lock(&lock);
//             validSub[sub] = 1;
//             Counter++;
//             pthread_mutex_unlock(&lock);
//         }
//         sleep(delay);  // Include delay after validating each sub-grid
//     }

//     return NULL;
// }



// void *validate_thread2(void *args) 
// {
//     parameters *param = (parameters *)args;
//     int start_row = param->start_row;
//     int end_row = param->end_row;
//     int delay = param->delay; // Make sure delay is included in your parameters struct

//     // Validate rows
//     for (int i = start_row; i <= end_row; i++) 
//     {
//         if (check_validity(Sol[i])) 
//         {
//             pthread_mutex_lock(&lock);
//             validRow[i] = 1;
//             Counter++;
//             pthread_mutex_unlock(&lock);
//         }
//         sleep(delay);  
//     }

//     // Validate sub-grids
//     for (int sub = 3; sub < 6; sub++) 
//     {
//         int subGrid[GRID_SIZE];
//         int idx = 0;
//         for (int i = sub / 3 * 3; i < sub / 3 * 3 + 3; i++) 
//         {
//             for (int j = sub % 3 * 3; j < sub % 3 * 3 + 3; j++) 
//             {
//                 subGrid[idx++] = Sol[i][j];
//             }
//         }
//         if (check_validity(subGrid)) 
//         {
//             pthread_mutex_lock(&lock);
//             validSub[sub] = 1;
//             Counter++;
//             pthread_mutex_unlock(&lock);
//         }
//         sleep(delay);  
//     }

//     return NULL;
// }
