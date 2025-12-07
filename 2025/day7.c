/*
 * Advent of Code 2025: Day 7: Laboratories
 * https://adventofcode.com/2025/day/7
 */
 #include <stdio.h>
 #include <string.h>

 /* Global Variables lets goooo! */
 char tachyon_manifold[200][500];
 char quantum_tachyon_manifold[200][500];
 int level_count = 0;

 void print_tachyon_manifold(char mainfold[200][500], int size)
 {
     for(int i = 0; i < size; i+=1)
     {
         printf("%s", mainfold[i]);
     }
 }

 void print_timeline_matrix(int matrix[200][500], int rows, int cols)
 {
     for(int i = 0; i<rows; i+=1)
     {
         for (int j = 0; j < rows; j+= 1)
         {
             printf(" %d", matrix[i][j]);
         }
         printf("\n");
     }
 }

 long int get_timelines(long int timeline_matrix[200][500], int row, int column)
 {
     long int result;
     if(row == level_count - 1)
     {
         timeline_matrix[row][column] = 1;
         return 1;
     }
     if(timeline_matrix[row][column] != 0)
     {
         return timeline_matrix[row][column];
     }
     if(quantum_tachyon_manifold[row+1][column] == '.')
     {
         result = get_timelines(timeline_matrix, row+1, column);
     }
     if(quantum_tachyon_manifold[row+1][column] == '^')
     {
         result = get_timelines(timeline_matrix, row+1, column-1) + get_timelines(timeline_matrix, row+1, column+1);
     }
     timeline_matrix[row][column] = result;
     return result;

 }

 int process_and_count(char mainfold[200][500], int size, int print)
 {
     int splits = 0;
     for(int level = 0; level + 1 < size; level += 1)
     {
         for(int i = 0; mainfold[level][i] != '\n'; i +=1)
         {
             char symbol = mainfold[level][i];
             if(symbol == 'S' || symbol == '|')
             {
                 char symbol_bellow = mainfold[level+1][i];
                 if(symbol_bellow == '^')
                 {
                     /* Split */
                     mainfold[level+1][i-1] = '|';
                     mainfold[level+1][i+1] = '|';
                     splits += 1;
                 }
                 else
                 {
                     mainfold[level+1][i] = '|';
                 }
             }
         }
         if(print)
         {
             print_tachyon_manifold(mainfold, size);
         }
     }
     return splits;
 }

 long int qunatum_process_and_count()
 {
     long int timelines = 0;
     long int timeline_matrix[200][500];
     /* Zero the matrix */
     for(int i = 0; i < 200; i += 1)
         for(int j = 0; j < 500; j++)
             timeline_matrix[i][j] = 0;

     int r = 0;
     int c = 0;
     for(int i = 0; quantum_tachyon_manifold[r][i] != '\n'; i += 1)
     {
         if(quantum_tachyon_manifold[r][i] == 'S')
         {
             c = i;
         }
     }

     timelines = get_timelines(timeline_matrix, r, c);

     return timelines;
 }

 int main(int argc, char *arcv[])
 {
     /* Create pointer to the file */
     FILE *fptr;
     /*  Open a file in read mode */
     fptr = fopen("./inputs/day7.txt", "r");
     /*  Store the content of the file */
     char inputString[500];
     while(fgets(inputString, 500, fptr))
     {
         strcpy(tachyon_manifold[level_count], inputString);
         strcpy(quantum_tachyon_manifold[level_count], inputString);
         level_count += 1;
     }
     /* Close file */
     fclose(fptr);

     //print_tachyon_manifold(tachyon_manifold, level_count);
     int splits = process_and_count(tachyon_manifold, level_count, 0);
     long int timelines = qunatum_process_and_count();
     printf("Number of times beam splits: %d\n", splits);
     printf("Number of timelines created: %ld\n", timelines);
     return 0;
 }
