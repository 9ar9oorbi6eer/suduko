#include "variables.h"
#include "threads.h"

// THIS C FILE CONTIANS ALL THREADS FROM 1 - 4


// thread 1
void *validate_thread1(void *args) 
{
    parameters *param = (parameters *)args;
    int start_row = param->start_row;
    int end_row = param->end_row;
    int delay = param->delay;

    

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
          
        }
 
        sleep(delay);  // Include delay after validating each sub-grid
 
    }

    
    return NULL;
}

void *validate_thread2(void *args) 
{
    parameters *param = (parameters *)args;
    int start_row = param->start_row;
    int end_row = param->end_row;
    int delay = param->delay;

    
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
 
        sleep(delay);
 
    }

    // Validate sub-grids
    for (int sub = 3; sub < 6; sub++) 
    {
        int subGrid[GRID_SIZE];
        int idx = 0;
        int i; //remove this
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
 
        sleep(delay);
 
    }

   
    return NULL;
}
// thread 3
void *validate_thread3(void *args)
{
    parameters *param = (parameters *)args;
    int start_row = param->start_row;
    int end_row = param->end_row;
    int delay = param->delay;

    // Validate rows 7, 8, and 9
    for (int i = start_row; i <= end_row; i++) 
    {
        if (check_validity(Sol[i])) 
        {
            pthread_mutex_lock(&lock);
            validRow[i] = 1;
            Counter++;
            pthread_mutex_unlock(&lock);
        
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
          
        }

        sleep(delay);  // Include delay after validating each sub-grid

    }


    return NULL;
}

void *validate_thread4(void *args) 
{
    parameters *param = (parameters *)args;
    int delay = param->delay;


    // Validate columns
    for (int i = 0; i < GRID_SIZE; i++) 
    {
        int column[GRID_SIZE];
        for (int j = 0; j < GRID_SIZE; j++) 
        {
            column[j] = Sol[j][i];
        }

        if (check_validity(column)) 
        {
            pthread_mutex_lock(&lock);
            validCol[i] = 1;
            Counter++;
            pthread_mutex_unlock(&lock);
           
        }
        

        sleep(delay);  // Include delay after validating each column

    }

    return NULL;
}

