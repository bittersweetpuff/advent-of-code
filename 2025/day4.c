/*
 * Advent of Code 2025: Day 4: Printing Department
 * https://adventofcode.com/2025/day/4
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_adjacency_matrix(int** matrix, int m_size)
{
    for(int i = 1; i < m_size-1; i += 1)
    {
        for(int j = 1; j < m_size-1; j += 1)
        {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }

}

void mark_adjacency(int** matrix, int row, int column)
{
    for(int i = row - 1; i <= row+1; i += 1)
    {
        for(int j = column - 1; j <= column+1; j += 1)
        {
            if(i != row || j != column)
            {
                matrix[i][j] += 1;
            }
        }
    }

}

int count_paper_rolls(char grid[200][200], int grid_size)
{
    printf("Counting paper rolls\n");
    int matrix_size = grid_size+2;
    /* Allocate  */
    int** adjacency_matrix;
    printf("Malloc matrix\n");
    adjacency_matrix = (int**)malloc(matrix_size * sizeof(int*));
    for(int i = 0; i < matrix_size; i += 1)
    {
        adjacency_matrix[i] = (int*)malloc(matrix_size * sizeof(int));
    }
    printf("Filling matrix\n");
    /* Fill matrix with zeros */
    for(int i = 0; i<matrix_size; i += 1)
        for(int j = 0; j<matrix_size; j += 1)
            adjacency_matrix[i][j] = 0;

    printf("Printing grid\n");
    for(int i = 0; i < grid_size; i += 1)
    {
        printf("%s", grid[i]);
    }


    /* Scan grid */
    for(int i = 0; i<grid_size; i += 1)
    {
        for(int j = 0; j<grid_size; j += 1)
        {
            if(grid[i][j] == '@')
            {
                mark_adjacency(adjacency_matrix, i+1, j+1);
            }
        }
    }

    printf("Printing matrix\n");
    print_adjacency_matrix(adjacency_matrix, matrix_size);

    int rolls_count = 0;
    /* Count paper rolls */
    for(int i = 0; i < grid_size; i += 1)
    {
        for(int j = 0; j < grid_size; j += 1)
        {
            if(grid[i][j] == '@')
            {
                if(adjacency_matrix[i+1][j+1] < 4)
                {
                    rolls_count += 1;
                    printf("X");
                }
                else
                {
                    printf("@");
                }
            }
            else
            {
                printf("*");
            }
        }
        printf("\n");
    }


    /* Free allocated memory */
    for (int i = 0; i < matrix_size; i++)
            free(adjacency_matrix[i]);
    free(adjacency_matrix);

    return rolls_count;
}


int main(int argc, char *argv[])
{
    /* Create pointer to the file */
    FILE *fptr;
    /*  Open a file in read mode */
    fptr = fopen("./inputs/day4.txt", "r");
    /*  Store the content of the file */
    char inputString[200];
    char grid[200][200];

    int row = 0;
    while(fgets(inputString, 200, fptr))
    {
        strcpy(grid[row], inputString);
        //printf("%s", grid[row]);
        row+=1;
    }
    int grid_size = row;
    fclose(fptr);

    int rolls_count = count_paper_rolls(grid, grid_size);

    printf("Number of paper rolls that can be removed: %d\n", rolls_count);


    return 0;
}
