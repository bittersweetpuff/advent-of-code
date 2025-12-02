/*
 * Advent of Code 2025: Day 2: Gift Shop
 * https://adventofcode.com/2025/day/2
 */
 #include <math.h>
 #include <stdio.h>
 #include <string.h>


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

 long long int scan_range(long int start, long int stop)
 {
     long long int sum = 0;
     for (long int i = start; i <= stop; i += 1)
     {
         /* add ID if invalid */
         if(!check_id_validity(i))
         {
             //printf("%ld\n", i);
             sum += i;
         }
     }
     return sum;
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
               sumOfInvalids += scan_range(start, stop);
           }
           range = strtok(NULL, ",");
    }
     printf("The sum of all invalid IDs is: %lld\n", sumOfInvalids);
     return 0;
 }
