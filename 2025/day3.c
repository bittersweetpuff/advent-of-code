/*
 * Advent of Code 2025: Day 3: Lobby
 * https://adventofcode.com/2025/day/3
 */
 #include <stdio.h>

 long int get_max_joltage(char* bank, int batteries_needed)
 /*
  * Function takes a string of batteries (bank) and number of batteries needed
  */
 {
    long int joltage = 0;
    int max_joltage_battery = -1;
    int last_bettery_index = -1;

    /* Finding batteries */
    for(int j = 1; j <= batteries_needed; j+=1)
    {
        /* Last char before null sign is newline, so I iterate to that */
        for(int i = last_bettery_index+1; bank[i + (batteries_needed - j)] != '\n'; i += 1)
        {
            /* Char to int conversion */
            int current_battery = bank[i] - '0';
            if(current_battery>max_joltage_battery)
            {
                max_joltage_battery = current_battery;
                last_bettery_index = i;
            }
        }
        joltage = (joltage * 10) + max_joltage_battery;
        max_joltage_battery = -1;
    }

    return joltage;
 }

 int main(int argc, char *argv[])
 {
     long int joltage_sum_1 = 0;
     long int joltage_sum_2 = 0;
     /* Create pointer to the file */
     FILE *fptr;
     /*  Open a file in read mode */
     fptr = fopen("./inputs/day3.txt", "r");
     /*  Store the content of the file */
     char inputString[500];

     while(fgets(inputString, 500, fptr))
     {
         joltage_sum_1 += get_max_joltage(inputString, 2);
         joltage_sum_2 += get_max_joltage(inputString, 12);
     }
     fclose(fptr);

     printf("Total output joltage for 2 batteries is is: %ld\n", joltage_sum_1);
     printf("Total output joltage for 12 batteries is is: %ld\n", joltage_sum_2);

     return 0;
 }
