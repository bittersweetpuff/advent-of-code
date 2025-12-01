#include <math.h>
#include <stdio.h>

int turn_dial(int position, char direction, int steps){
    if(direction != 'L' && direction != 'R')
        return -1;

    int directed_steps, new_position;

    // Reduce full rotations of dial
    if(steps > 99)
        directed_steps = steps%100;
    else
        directed_steps = steps;

    // Apply direction
    if(direction == 'L')
        directed_steps = directed_steps * -1;

    // Handle moving between 99 and 0
    if(position+directed_steps < 0)
        new_position = 100 + (position+directed_steps);
    else
        new_position = position + directed_steps;

    // Modulo for position > 99
    if(new_position > 99)
        new_position = new_position%100;

    return new_position;
}

char get_rotation(char* input){
    return input[0];
}

int get_steps(char* input){
    int size = 0;
    int steps = 0;
    while(input[size] != '\0')
        size += 1;
    // Sets the count of the digits in the number base on null character. -1 for null character and -1 for 'L' and 'R'
    size -= 2;
    int exponent = 0;
    while(size > 0){
        int digit = input[size] - '0';
        //printf("tab[%d] = %d\n", size, digit);
        steps += digit * (int)pow(10, exponent);
        exponent += 1;
        size -= 1;
    }
    return steps;

}


int main(){
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("./inputs/day1.txt", "r");

    // Store the content of the file
    char myString[100];

    int steps;
    char direction;
    int initial_position = 50;
    int pos = initial_position;
    int zero_count = 0;
    while(fgets(myString, 100, fptr)) {
        steps = get_steps(myString);
        direction = get_rotation(myString);
        pos = turn_dial(pos, direction, steps);
        if(pos == 0)
            zero_count += 1;
    }

    // Close the file
    fclose(fptr);

    printf("The dial stopped on 0 %d times, so the password is: %d\n", zero_count, zero_count);

    //pos = turn_dial(pos, 'L', 68);
    //printf("%d\n", pos);
    return 1;
}
