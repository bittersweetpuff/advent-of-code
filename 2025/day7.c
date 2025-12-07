/*
 * Advent of Code 2025: Day 7: Laboratories
 * https://adventofcode.com/2025/day/7
 */
 #include <stdio.h>
#include <string.h>

 void print_tachyon_manifold(char mainfold[200][500], int size)
 {
     for(int i = 0; i < size; i+=1)
     {
         printf("%s", mainfold[i]);
     }
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

 int main(int argc, char *arcv[])
 {
     char tachyon_manifold[200][500];
     int level_count = 0;

     /* Create pointer to the file */
     FILE *fptr;
     /*  Open a file in read mode */
     fptr = fopen("./inputs/day7.txt", "r");
     /*  Store the content of the file */
     char inputString[500];
     while(fgets(inputString, 500, fptr))
     {
         strcpy(tachyon_manifold[level_count], inputString);
         level_count += 1;
     }
     /* Close file */
     fclose(fptr);

     //print_tachyon_manifold(tachyon_manifold, level_count);
     int splits = process_and_count(tachyon_manifold, level_count, 1);
     printf("Number of times beam splits: %d\n", splits);
     return 0;
 }
