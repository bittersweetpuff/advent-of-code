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

/*
 * Function takes the same input as turn_dial() but instead returns number of times 0 has been touched.
 */
int count_clicks(int position, char direction, int steps){
    int clicks = 0;
    if(direction != 'L' && direction != 'R')
        return -1;

    int directed_steps, new_position;

    // Reduce full rotations of dial and count every full rotation
    if(steps > 99){
        //("Steps > 99");
        clicks += steps/100;
        directed_steps = steps%100;
        if(position == 0){
            //printf("but starts on 0\n");
            clicks -= 1;
        }
    }
    else
        directed_steps = steps;

    // Apply direction
    if(direction == 'L')
        directed_steps = directed_steps * -1;

    // Handle moving between 99 and 0
    if(position+directed_steps < 0){

        new_position = 100 + (position+directed_steps);
        if (position != 0){
            //printf("position less than 0 and start != 0\n");
            clicks += 1;
        }
    }
    else if(position + directed_steps > 99){
        new_position = position + directed_steps;
        new_position = new_position%100;
        if (position != 0 && new_position != 0){
            //printf("position greater than 100 and start != 0\n");
            clicks += 1;
        }
    }
    else{
        new_position = position + directed_steps;
    }


    if(new_position == 0){
        //printf("Ends on 0\n");
        clicks += 1;
    }

    return clicks;
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
    int click_count = 0;
    while(fgets(myString, 100, fptr)) {
        steps = get_steps(myString);
        direction = get_rotation(myString);
        click_count += count_clicks(pos, direction, steps);
        pos = turn_dial(pos, direction, steps);
        if(pos == 0)
            zero_count += 1;
    }
    // Close the file
    fclose(fptr);
    printf("The dial stopped on 0 %d times, so the password is: %d\n", zero_count, zero_count);
    printf("However based on password method 0x434C49434B the number of times zero was clicked was: %d\n", click_count);

    return 1;
}
