#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


// so a sub grid is just the small box that the 9 numbers will be placed, so in each suduku we have\
9 sub grids.

// thread 1 checks the first 3 sub grids(1,2,3), and the first 3 rows(1,2,3)
// thread 2 checks the subgrid 4, 5 , 6 and the rows 4, 5, 6
// thread 3 checks the subgrid 7, 8, 9, and the rows 7, 8, 9
// thread 4 does all 9 columns

////////////////////////////////////////////////////////////////////////////
// data structures///

// sol = array that will store suduku grid
// row, col and sub arrays will track the validation status of each row, column and sub grid
// counter = will count the number of valid rows, columns and sub grids

/////////////////////////////////////////////////////////////////////////////
// threads///
// each thread will validate its assigned section of suduku grid:
// check if each row, column or sub grid contains all digits from 1 to 9
// update the corresponding index in row,col, or sub to 1 if the section is valid

// you need to handle synchronisation using mutex lock

// TO FURTHER EXPLAIN row array will validate rows 1 to 9, if its valid then its set to 1 and if its invalid then its 0 same thing with the columns

///// HOW TO RUN : mssv solution delay where solution is the file that contains the sudoku soultion to be validated, and delay is an integer with a vaue between 1 and 10
#define GRID_SIZE 9

int Sol[GRID_SIZE][GRID_SIZE];
int validRow[GRID_SIZE];
int validCol[GRID_SIZE];
int validSub[GRID_SIZE];
int Counter = 0;



//thread parameter structure
typedef struct {
    int start_row;
    int end_row;
    int start_col;
    int end_col;
    int thread_num;
} parameters;





// reading from the sodoku file
void readFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (fscanf(file, "%d", &Sol[i][j]) != 1) {
                fprintf(stderr, "Error reading Sudoku grid from file\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);
}

// Main function
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <sudoku_input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Read the Sudoku grid from the provided file
    readFromFile(argv[1]);

    // // Print the Sudoku grid to verify correct reading (for debugging)
    // printf("Sudoku Grid:\n");
    // for (int i = 0; i < 9; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         printf("%d ", Sol[i][j]);
    //     }
    //     printf("\n");
    // }
}




