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

 typedef struct
 {
     int no_of_columns;
     int no_of_lines;
     char char_lines[10][4000];
     char sign_line[2000];
 } CephalopodMatrix;


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

 void print_cephalopod_matrix(CephalopodMatrix matrix)
 {
     for(int i = 0; i<matrix.no_of_lines; i += 1)
     {
         printf("%s", matrix.char_lines[i]);
     }
     for(int i = 0; i<matrix.no_of_columns; i += 1)
     {
         printf("%c ", matrix.sign_line[i]);
     }
     printf("\n");
 }

 int get_equation_end(CephalopodMatrix matrix, int equation_start)
 {
     int end = 0;

     for(int i = equation_start; matrix.char_lines[0][i] != '\0'; i += 1)
     {
         int empty = 1;
         end = i;
         for(int j = 0; j < matrix.no_of_lines - 1; j += 1)
         {
             //printf("Char in %d line, %d columns: [%c]\n", j, i, matrix.char_lines[j][i]);
             if(matrix.char_lines[j][i] != ' ' && matrix.char_lines[j][i] != '\n')
             {
                 empty = 0;
             }
         }
         if(empty)
         {
             printf("END OF EQUATION!\n");
             return end;
         }
     }
     return end;
 }

 long long int evaluate_array(int *array, int size, char sign)
 {
     long long int result;
     if(sign == '+')
     {
         result = 0;
     }
     else
     {
         result = 1;
     }
     for(int i = 0; i<size; i += 1)
     {
         if(sign == '+')
         {
             result += array[i];
         }
         else
         {
             result *= array[i];
         }
     }

     return result;
 }

 long long int evaluate_column(OperationMatrix matrix, int column)
 {
     long long int result;
     char sign = matrix.sign_line[column];
     if(sign == '+')
     {
         result = 0;
     }
     else
     {
         result = 1;
     }
     for(int i = 0; i<matrix.no_of_lines; i += 1)
     {
         if(sign == '+')
         {
             result += matrix.number_lines[i][column];
         }
         else
         {
             if(matrix.number_lines[i][column] == 0)
             {
                 result = result;
             }
             else
             {
                 result *= matrix.number_lines[i][column];
             }
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

 long long int evaluate_cephalopod_matrix(CephalopodMatrix c_matrix)
 {
     long long int result = 0;

     int current_equation = 0;
     int equation_start = 0;
     int equation_end = 0;
     int equation_array[5];
     char cephalopod_number[10];
     while(current_equation < c_matrix.no_of_columns-1) {
         equation_end = get_equation_end(c_matrix, equation_start);
         printf("Equation from %d to %d\n", equation_start, equation_end);
         for(int i = equation_start; i< equation_end; i += 1)
         {
             for(int j = 0; j < c_matrix.no_of_lines-1; j += 1)
             {
                 cephalopod_number[j] = c_matrix.char_lines[j][i];
             }
             printf("C Number: %d\n", atoi(cephalopod_number));
             equation_array[i-equation_start] = atoi(cephalopod_number);
         }

         result += evaluate_array(equation_array, equation_end-equation_start, c_matrix.sign_line[current_equation]);
         equation_start = equation_end+1;
         current_equation += 1;
     }

     /* Yolo last equation */
     printf("LAST EQUATION!\n");
     for(int i = equation_start; i<equation_start + c_matrix.no_of_lines-1; i += 1)
     {
         for(int j = 0; j < c_matrix.no_of_lines-1; j += 1)
         {
             cephalopod_number[j] = c_matrix.char_lines[j][i];
         }
         printf("C Number: %d\n", atoi(cephalopod_number));
         equation_array[i-equation_start] = atoi(cephalopod_number);
     }
     result += evaluate_array(equation_array, c_matrix.no_of_lines-1, c_matrix.sign_line[current_equation]);



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
     CephalopodMatrix c_matrix;
     matrix.no_of_columns = 0;
     matrix.no_of_lines = 0;
     c_matrix.no_of_columns = 0;
     c_matrix.no_of_lines = 0;
     /* Get first line */
     fgets(inputString, 4000, fptr);
     strcpy(lastLine, inputString);
     while(fgets(inputString, 4000, fptr))
     {
         int count = 0;
         strcpy(c_matrix.char_lines[matrix.no_of_lines], lastLine);
         char * str_number = strtok(lastLine, " ");
         while( str_number != NULL )
         {
             int number = atoi(str_number);
             /* Put number in matrix */
             matrix.number_lines[matrix.no_of_lines][count] = number;
             str_number = strtok(NULL, " ");
             count += 1;
         }
         /* Store last line for operation */
         strcpy(lastLine, inputString);
         matrix.no_of_lines += 1;
     }
     strcpy(c_matrix.char_lines[matrix.no_of_lines], lastLine);
     c_matrix.no_of_lines = matrix.no_of_lines +1;
     /* Get signs */
     char * str_sign = strtok(lastLine, " ");
     while( str_sign != NULL )
     {
         char sign;
         sscanf(str_sign, "%c", &sign);
         matrix.sign_line[matrix.no_of_columns] = sign;
         c_matrix.sign_line[matrix.no_of_columns] = sign;
         matrix.no_of_columns += 1;
         str_sign = strtok(NULL, " ");
     }
     c_matrix.no_of_columns = matrix.no_of_columns;
     fclose(fptr);

     printf("Loaded matrix: \n");
     print_operation_matrix(matrix);

     long long int final_eval = evaluate_matrix(matrix);
     printf("Sum of all result is: %lld\n", final_eval);

     long long int cephalopod_final_eval = evaluate_cephalopod_matrix(c_matrix);
     printf("Sum of all result using celapholopod method: %lld\n", cephalopod_final_eval);


     return 0;
 }
