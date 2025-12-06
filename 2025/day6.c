/*
 * Advent of Code 2025: Day 6: Trash Compactor
 * https://adventofcode.com/2025/day/6
 */
 #include <stdio.h>
#include <stdlib.h>
 #include <string.h>

 typedef struct
 {
     int no_of_columns;
     int no_of_lines;
     int number_lines[10][2000];
     char sign_line[2000];
 } OperationMatrix;


 void print_operation_matrix(OperationMatrix matrix)
 {
     for(int i = 0; i<matrix.no_of_lines; i += 1)
     {
         for(int j = 0; j<matrix.no_of_columns; j += 1)
         {
             printf("%d ", matrix.number_lines[i][j]);
         }
         printf("\n");
     }
     for(int i = 0; i<matrix.no_of_columns; i += 1)
     {
         printf("%c ", matrix.sign_line[i]);
     }
     printf("\n");
 }

 long long int evaluate_column(OperationMatrix matrix, int column)
 {
     long long int result;
     char sigh = matrix.sign_line[column];
     if(sigh == '+')
     {
         result = 0;
     }
     else
     {
         result = 1;
     }
     for(int i = 0; i<matrix.no_of_lines; i += 1)
     {
         if(sigh == '+')
         {
             result += matrix.number_lines[i][column];
         }
         else
         {
             result *= matrix.number_lines[i][column];
         }
     }

     return result;
 }

 long long int evaluate_matrix(OperationMatrix matrix)
 {
     long long int result = 0;
     for(int i = 0; i<matrix.no_of_columns; i += 1)
     {
         result += evaluate_column(matrix, i);
     }
     return result;
 }

 int main(int argc, char *argv[])
 {
     /* Create pointer to the file */
     FILE *fptr;
     /*  Open a file in read mode */
     fptr = fopen("./inputs/day6.txt", "r");
     /*  Store the content of the file. Bigger buffer this time */
     char inputString[4000];
     char lastLine[4000];
     OperationMatrix matrix;
     matrix.no_of_columns = 0;
     matrix.no_of_lines = 0;
     /* Get first line */
     fgets(inputString, 4000, fptr);
     strcpy(lastLine, inputString);
     while(fgets(inputString, 4000, fptr))
     {
         printf("Line %d: %s", matrix.no_of_lines, lastLine);
         printf("Scanning line...\n");
         int count = 0;
         char * str_number = strtok(lastLine, " ");
         while( str_number != NULL )
         {
             int number = atoi(str_number);
             printf("Scanned number: %d\n", number);
             /* Put number in matrix */
             matrix.number_lines[matrix.no_of_lines][count] = number;
             str_number = strtok(NULL, " ");
             count += 1;
         }
         /* Store last line for operation */
         strcpy(lastLine, inputString);
         matrix.no_of_lines += 1;
     }

     /* Get signs */
     char * str_sign = strtok(lastLine, " ");
     while( str_sign != NULL )
     {
         char sign;
         sscanf(str_sign, "%c", &sign);
         printf("Scanned sign: %c\n", sign);
         matrix.sign_line[matrix.no_of_columns] = sign;
         matrix.no_of_columns += 1;
         str_sign = strtok(NULL, " ");
     }

     printf("Loaded matrix: \n");
     print_operation_matrix(matrix);

     long long int final_eval = evaluate_matrix(matrix);
     printf("Sum of all result is: %lld\n", final_eval);


     fclose(fptr);
     return 0;
 }
