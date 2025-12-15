/*
 * Advent of Code 2025: Day 2: Gift Shop
 * https://adventofcode.com/2025/day/2
 */
 #include <math.h>
 #include <stdio.h>
 #include <string.h>

 /*
  * Checks if the number consists of multiple patterns (for puzzle 2)
  */
 int check_pattern_repeat(long int pattern, long int number, int pattern_lenght)
 {
     long int multi_pattern = pattern;
     while (multi_pattern<=number)
     {
         if (multi_pattern == number)
         {
             return 1;
         }
         /* Takes check pattern (example "12"), multiplies it by length (1200) and adds (1212) */
         multi_pattern = (multi_pattern*(long)pow(10, pattern_lenght)) + pattern;
     }
     return 0;
 }

 /*
  * Checks if ID is valid based on Puzzle 1. Calculates length of the number and compares
  * result of multiplication with modulo.
  */
 int check_id_validity(long int id)
 {
     int length = 1;
     while(id%(long)pow(10, length) != id)
         length+=1;
     /* Early return for uneven number of digits */
     if(length%2 == 1)
         return 1;
     long int left, right;
     /* Cast on float is ugly but supresses warnings so why not */
     left = id/(long)pow(10, (float)length/2);
     right = id%(long)pow(10, (float)length/2);
     if(left == right)
     {
         return 0;
     }
     else
     {
         return 1;
     }
 }

 /*
  * Checks if ID is valid based on Puzzle 2
  */
 int check_id_validity_part2(long int id)
 {
     int length = 1;
     while(id%(long)pow(10, length) != id)
         length+=1;
     for(int pattern_lenght = 1; pattern_lenght<=length/2; pattern_lenght += 1)
     {
         long int pattern = id/(long)pow(10, length-pattern_lenght);
         if(check_pattern_repeat(pattern, id, pattern_lenght))
         {
             return 0;
         }
     }
     return 1;
 }


 /*
  * Takes start and stop of the range + method (1 or 2 based on puzzle, yeah i could use some multiple returns)
  * and returns sum of all invalid IDs in that range
  */
 long long int scan_range(long int start, long int stop, int method)
 {
     long long int sum = 0;
     long long int sum2 = 0;
     for (long int i = start; i <= stop; i += 1)
     {
         /* add ID if invalid */
         if(!check_id_validity(i))
         {
             sum += i;
         }
         if(!check_id_validity_part2(i))
         {
             sum2 += i;
         }
     }
     if (method == 1)
     {
         return sum;
     }
     else
     {
         return sum2;
     }
 }


 int main(int argc, char *argv[])
 {

     long long int sumOfInvalids1 = 0;
     long long int sumOfInvalids2 = 0;
     /* Create pointer to the file */
     FILE *fptr;
     /*  Open a file in read mode */
     fptr = fopen("./inputs/day2.txt", "r");
     /*  Store the content of the file */
     char inputString[1000];
     fgets(inputString, 1000, fptr);
     /* Close the file */
     fclose(fptr);
     /* Split on comas  */
     char * range = strtok(inputString, ",");
     while( range != NULL ) {
           long int start, stop;
           /* Yeah i love the sscanf */
           if (sscanf(range, "%ld-%ld", &start, &stop))
           {
               sumOfInvalids1 += scan_range(start, stop, 1);
               sumOfInvalids2 += scan_range(start, stop, 2);
           }
           /* I hate this way of splitting but seems to be the way to go */
           range = strtok(NULL, ",");
    }
     /* Prints with results */
     printf("The sum of all invalid IDs (first method) is: %lld\n", sumOfInvalids1);
     printf("The sum of all invalid IDs (second method) is: %lld\n", sumOfInvalids2);
     return 0;
 }
