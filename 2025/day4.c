/*
 * Advent of Code 2025: Day 4: Printing Department
 * https://adventofcode.com/2025/day/4
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_adjacency_matrix(int** matrix, int m_size)
/*
 * Prints adjacency matrix (used mostly for debug + it looks cool for actual puzzle)
 */
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
/*
 * Increments all adjancent cells. Moved to separate function for clarity
 */
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

void reset_adjacency_matrix(int** matrix, int matrix_size)
/*
 * Sets all values in adjacency matrix to 0.
 * Moved to separate function for clarity,
 * and I thought I may need to reset it more often.
 */
{
    for(int i = 0; i<matrix_size; i += 1)
        for(int j = 0; j<matrix_size; j += 1)
            matrix[i][j] = 0;
}

int remove_paper_rolls(char grid[200][200], int grid_size, int print_matrix)
/*
 * Functions find paper rolls (@) with less than 4 other paper rolls next to them,
 * changes original grid by swaping removed rolls for empty spaces (.) and returns
 * number of removed paper rolls. Can print adjacency matrix if print_matrix > 0.
 */
{
    /* Allocate  */
    int** adjacency_matrix;
    int matrix_size = grid_size+2;
    adjacency_matrix = (int**)malloc(matrix_size * sizeof(int*));
    for(int i = 0; i < matrix_size; i += 1)
    {
        adjacency_matrix[i] = (int*)malloc(matrix_size * sizeof(int));
    }

    /* Fill matrix with zeros */
    reset_adjacency_matrix(adjacency_matrix, matrix_size);

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

    /* Optional print for adjacency matrix */
    if(print_matrix)
    {
        printf("\n### Adjacency matrix ###\n\n");
        print_adjacency_matrix(adjacency_matrix, matrix_size);
    }

    /* Count paper rolls and print grid with rolls for removal marked */
    int rolls_count = 0;
    printf("\n### Paper Rolls ###\n\n");
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
                    grid[i][j] = '.';
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
    printf("\n");


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
    fptr = fopen("./inputs/day4-test.txt", "r");
    /*  Store the content of the file */
    char inputString[200];
    char grid[200][200];

    int row = 0;
    while(fgets(inputString, 200, fptr))
    {
        strcpy(grid[row], inputString);
        /* Grids are square */
        row+=1;
    }
    int grid_size = row;
    fclose(fptr);
    int step = 1;
    printf("||| ITERATION %d |||\n", step);
    /* Inital papre rolls removal (part 1) */
    int rolls_count = remove_paper_rolls(grid, grid_size, 1);
    int rolls_sum = rolls_count;
    int rolls_first = rolls_count;
    /* Rest of iterations (part 2) */
    while(rolls_count>0)
    {
        step += 1;
        printf("||| ITERATION %d |||\n", step);
        rolls_count = remove_paper_rolls(grid, grid_size, 1);
        rolls_sum += rolls_count;
    }
    printf("Number of paper rolls that can be removed in first iteration: %d\n", rolls_first);
    printf("Number of paper rolls that can be removed: %d\n", rolls_sum);
    return 0;
}
