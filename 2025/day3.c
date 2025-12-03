/*
 * Advent of Code 2025: Day 3: Lobby
 * https://adventofcode.com/2025/day/3
 */
 #include <stdio.h>

 long int get_max_joltage(char* bank, int batteries_needed)
 {
    printf("%s", bank);
    long int joltage = 0;
    int max_joltage_battery = -1;
    int last_bettery_index = -1;
    /* Finding first battery */
    /* Last char before null sigh is newline, so I iterate to that */

    for(int j = 1; j <= batteries_needed; j+=1)
    {
        for(int i = last_bettery_index+1; bank[i + (batteries_needed - j)] != '\n'; i += 1)
        {
            int current_battery = bank[i] - '0';
            if(current_battery>max_joltage_battery)
            {
                max_joltage_battery = current_battery;
                last_bettery_index = i;
            }
        }
        printf("Max Battery [%d]: %d\n", j, max_joltage_battery);
        joltage = (joltage * 10) + max_joltage_battery;
        max_joltage_battery = -1;
    }
    /*

    for(int i = 0; bank[i+1] != '\n'; i+=1)
    {
        int current_battery = bank[i] - '0';
        if(current_battery>first_battery)
        {
            first_battery = current_battery;
            first_battery_index = i;
        }

        printf("%d ", current_battery);
    }
    printf("\nFirst Battery: %d\n", first_battery);


    for(int i = first_battery_index+1; bank[i]!='\n'; i += 1 )
    {
        int current_battery = bank[i] - '0';
        if(current_battery>second_battery)
        {
            second_battery = current_battery;
        }

        printf("%d ", current_battery);
    }
    printf("\nSecond Battery: %d\n", second_battery);
    */
    printf("Joltage: %ld", joltage);



    printf("\n");

    return joltage;
 }

 int main(int argc, char *argv[])
 {
     long int joltage_sum = 0;
     /* Create pointer to the file */
     FILE *fptr;
     /*  Open a file in read mode */
     fptr = fopen("./inputs/day3.txt", "r");
     /*  Store the content of the file */
     char inputString[500];

     while(fgets(inputString, 500, fptr))
     {
         joltage_sum += get_max_joltage(inputString, 12);
     }
     fclose(fptr);

     printf("Total output joltage is: %ld\n", joltage_sum);

     return 0;
 }
