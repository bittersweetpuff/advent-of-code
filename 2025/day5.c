/*
 * Advent of Code 2025: Day 5: Cafeteria
 * https://adventofcode.com/2025/day/5
 */
 #include <stdio.h>

 typedef struct
 {
     long int start;
     long int stop;

 } Range;

 typedef struct
 {
     int size;
     /* 250 is more then needed for puzzle input */
     Range list[250];
 } RangeList;


 void print_ranges(RangeList ranges)
 {
     for(int i = 0; i < ranges.size; i += 1)
     {
         printf("Range %d: %ld-%ld\n", i, ranges.list[i].start, ranges.list[i].stop);
     }
 }

 Range new_range(long int r_start, long int r_stop)
 {
     Range new_range;
     new_range.start = r_start;
     new_range.stop = r_stop;
     return new_range;
 }


 int id_in_range(long int id, Range checked_range)
 {
     if(id >= checked_range.start && id <= checked_range.stop)
     {
         //printf("\n%ld in range %ld-%ld\n", id, checked_range.start, checked_range.stop);
         return 1;
     }
     else
         return 0;
 }


 int id_in_any_range(long int id, RangeList all_ranges)
 {
     int inside = 0;
     for(int i = 0; i < all_ranges.size; i += 1)
     {
         if(id_in_range(id, all_ranges.list[i]))
             inside = 1;
     }

     return inside;
 }


int main(int argc, char *argv[])
{

    /* Create pointer to the file */
    FILE *fptr;
    /*  Open a file in read mode */
    fptr = fopen("./inputs/day5.txt", "r");
    /*  Store the content of the file */
    char inputString[100];
    fgets(inputString, 100, fptr);

    long int range_start, range_stop;
    long int current_item;
    RangeList ranges;

    /* Scan ranges */
    ranges.size = 0;
    while(sscanf(inputString, "%ld-%ld", &range_start, &range_stop) == 2)
    {
        printf("Range: %ld-%ld\n", range_start, range_stop);
        ranges.list[ranges.size] = new_range(range_start, range_stop);
        ranges.size += 1;
        fgets(inputString, 100, fptr);
    }

    print_ranges(ranges);

    /* Skip blank line and get items till the end of file */
    int fresh_count = 0;
    while (fgets(inputString, 100, fptr))
    {
        sscanf(inputString, "%ld", &current_item);
        printf("Item to scan: %ld", current_item);
        if(id_in_any_range(current_item, ranges))
        {
            fresh_count += 1;
            printf(" *FRESH*\n");
        }
        else
        {
            printf("\n");
        }
        //fgets(inputString, 100, fptr);
    }
    fclose(fptr);
    printf("Number of fresh items: %d\n", fresh_count);

    return 0;
}
