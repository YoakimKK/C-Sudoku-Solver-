// Sudoku maker and sovler, Assignment 1 Yoakim K.Koni

#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


int N; 

int **inputSudokuGrid(){

    printf("Enter the size of the sudoku grid: \n");
    if (scanf("%d", &N) != 1 || N <=0){
        printf("Invalid parameter");
        exit(1);
    }

    while (getchar() != '\n');

    printf("Grid Size: %d\n", N);

    //Dynamic memory allocation for the 2d array of grid
    //int **grid = (int **)malloc(N * sizeof(int *)); previous one
    int **grid = malloc(N * sizeof(int *));
    if (grid == NULL){
        printf("Memory Allocation Failed. \n");
        exit(1);
    }
    
    //allocating memory for rows and collumns
    for (int i = 0; i < N; i++){
        //grid[i] = (int *)malloc(N * sizeof(int)); 
        grid[i] = malloc(N * sizeof(int)); 
        if (grid[i] == NULL){
            printf("Memory allocation failed at %d \n", i);

            //freeing previous allocated memory (double check if this is suitable)
            for (int j = 0; j < i; j++){
                free(grid[j]);
            }
            free(grid);
            //exit(1);
        }
    }
    //Filling the sudoku grid with the users input
    printf("Enter the Sudoku grid values (use 0 for empty cells and input %d numbers seperated by space. \n", N);
        for (int i = 0; i < N; i++){
            printf("Enter row %d \n", i + 1);
            for (int j = 0; j < N; j++){
                if (scanf(" %d", &grid[i][j]) != 1){
                printf("Invalid parameter (Note that the size cannot exceed %d\n)", N);
            }
        }
    }

    return grid;
}


void printSudokuGrid(int **grid){
   
    for (int row = 0; row < N; row++){  
        for (int col = 0; col < N; col++){
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

int isValid(int **grid, int row, int col, int num){

    int subsize = sqrt(N);

    for (int i = 0; i < N; i++){
        if (grid[row][i] == num){
            return 0;
        }
    }
    for (int i = 0; i < N; i++){
        if (grid[i][col] == num){
            return 0;
        }
    }

    int startRow = row - row % subsize;
    int startCol = col - col % subsize;

    for (int i = 0; i < subsize; i++){
        for (int j = 0; j < subsize; j++){
            if (grid[i + startRow][j + startCol] == num)
            return 0;
        }
    }
    return 1;
}

int backtrack(int **grid, int row, int col){

    if (row == N - 1 && col == N){
        return 1;
    }

    if (col == N){
        row++;
        col = 0;
    }

    if (grid[row][col] != 0){
        return backtrack(grid, row, col + 1);
    }

    for (int num = 1; num <= N; num++) {
        if (isValid(grid, row, col, num) == 1){
            grid[row][col] = num; 

            if (backtrack(grid, row, col + 1) == 1)
                return 1;
        }
        grid[row][col] = 0; 
    }
    return 0;
}

int solveSudoku(int **grid){
    return backtrack(grid, 0 , 0);
}


void freeMemory(int **grid){
    for (int i = 0; i < N; i++){
        free(grid[i]);
    }
    free(grid);
}

void printMenu(){

    int choice;

    printf("\nAssignment 1 Sudoku Solver\n");
    printf("\n1. Input a Sudoku\n2. Solve the current grid\n3.Display the current grid\n4.Exit the program ");
    printf("\nPlease Select a choice:\n");
    scanf(" %d", &choice);

    printf("Your sekected choice %d", choice);

    switch(choice){
        case 1:
        int **grid = inputSudokuGrid();
        break;

        case 2: 
        if (solveSudoku(grid)){
            printf("\nSolved Sudoku\n");
            printSudokuGrid(grid);
            }
            else { 
              printf("\nNo solution exists for this sudoku\n");
            }
        break;
   
        case 3:
        printSudokuGrid(grid);
        break;

        case 4:
        exit(1);
        break;
    }



}


int main(){

    int choice;

    do {
        
        int **grid = inputSudokuGrid();

        printf("\nOrginal Grid\n");
        printSudokuGrid(grid);


        if (solveSudoku(grid)){
            printf("\nSolved Sudoku\n");
            printSudokuGrid(grid);
        }
        else { 
            printf("\nNo solution exists for this sudoku\n");
        }

        freeMemory(grid);
        
        printf("\n1. Try another puzzle\n2. Exit the program:");
        scanf(" %d", &choice);

        if (choice == 1){
            continue;   
        }
        else if (choice == 2){
            break;
        }
        else {
            printf("Invalid Choice");
        }
        
    } while (choice == 1); 

    printf("Exiting Program\n");
    return 0;
}