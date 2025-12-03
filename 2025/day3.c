/*
 * Advent of Code 2025: Day 3: Lobby
 * https://adventofcode.com/2025/day/3
 */
 #include <stdio.h>

 int get_max_joltage(char* bank)
 {
    printf("%s", bank);
    int first_battery = -1;
    int first_battery_index = -1;
    int second_battery = -1;
    /* Finding first battery */
    /* Last char before null sigh is newline, so I iterate to that */
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

    /* Finding second battery */
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
    int joltage = (first_battery * 10) + second_battery;
    printf("Joltage: %d", joltage);


    printf("\n");

    return joltage;
 }

 int main(int argc, char *argv[])
 {
     int joltage_sum = 0;
     /* Create pointer to the file */
     FILE *fptr;
     /*  Open a file in read mode */
     fptr = fopen("./inputs/day3.txt", "r");
     /*  Store the content of the file */
     char inputString[500];

     while(fgets(inputString, 500, fptr))
     {
         joltage_sum += get_max_joltage(inputString);
     }
     fclose(fptr);

     printf("Total output joltage is: %d\n", joltage_sum);

     return 0;
 }
