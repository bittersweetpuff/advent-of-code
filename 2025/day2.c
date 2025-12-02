/*
 * Advent of Code 2025: Day 2: Gift Shop
 * https://adventofcode.com/2025/day/2
 */
 #include <math.h>
 #include <stdio.h>
 #include <string.h>


 int check_pattern_repeat(long int pattern, long int number, int pattern_lenght)
 {
     long int multi_pattern = pattern;
     while (multi_pattern<=number)
     {
         //printf("%ld\n", multi_pattern);
         if (multi_pattern == number)
         {
             return 1;
         }
         multi_pattern = (multi_pattern*(long)pow(10, pattern_lenght)) + pattern;
     }

     return 0;
 }

 int check_id_validity(long int id)
 {
     int length = 1;
     while(id%(long)pow(10, length) != id)
         length+=1;

     /* Early return for uneven number of digits */
     if(length%2 == 1)
         return 1;

     long int left, right;
     left = id/(long)pow(10, length/2);
     right = id%(long)pow(10, length/2);

     if(left == right)
     {
         return 0;
     }
     else
     {
         return 1;
     }
 }

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
             printf("MULTIPATERN: %ld\n", id);
             return 0;
         }


     }

     return 1;

 }


 long long int scan_range(long int start, long int stop, int method)
 {
     long long int sum = 0;
     long long int sum2 = 0;
     for (long int i = start; i <= stop; i += 1)
     {
         //printf("Checking: %ld\n", i);
         /* add ID if invalid */
         if(!check_id_validity(i))
         {
             //printf("%ld\n", i);
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


 int main(int argc, char *argv[]){

     long long int sumOfInvalids = 0;

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
           //printf( "%s\n", range ); //printing each token

           long int start, stop;
           if (sscanf(range, "%ld-%ld", &start, &stop))
           {
               //printf("%ld-%ld\n", start, stop);
               sumOfInvalids += scan_range(start, stop, 2);
           }
           range = strtok(NULL, ",");
    }
     printf("The sum of all invalid IDs (second method) is: %lld\n", sumOfInvalids);
     return 0;
 }
