#include "variables.h"
#include "threads.h"

// thread 1
void *validate_thread1(void *args) 
{
    parameters *param = (parameters *)args;
    int start_row = param->start_row;
    int end_row = param->end_row;
    int num_valid = 0;

    // Validate rows
    for (int i = start_row; i <= end_row; i++) 
    {
        if (check_validity(Sol[i])) 
        {
            pthread_mutex_lock(&lock);
            validRow[i] = 1;
            Counter++;
            pthread_mutex_unlock(&lock);
        }
        sleep(1);  // Delay for synchronization issues observation
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
        }
        sleep(1);  // Delay for synchronization issues observation
    }

    pthread_cond_signal(&cond);
    return NULL;
}
