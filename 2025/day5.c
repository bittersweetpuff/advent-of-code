/*
 * Advent of Code 2025: Day 5: Cafeteria
 * https://adventofcode.com/2025/day/5
 */
 #include <stdio.h>

 long int max(long int a, long int b)
 {
     if(a >= b)
     {
         return a;
     }
     else
     {
         return b;
     }
 }

 long int min(long int a, long int b)
 {
     if(a <= b)
     {
         return a;
     }
     else
     {
         return b;
     }
 }

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

 int check_range_overlap(Range a, Range b)
 {
    if((a.start >= b.start && a.start <= b.stop) || (b.start >= a.start && b.start <= a.stop))
    {
        return 1;
    }
    else
    {
        return 0;
    }
 }

 Range merge_ranges(Range a, Range b)
 {
     long int merged_start = min(a.start, b.start);
     long int merged_stop = max(a.stop, b.stop);
     Range merged_range = new_range(merged_start, merged_stop);

     return merged_range;
 }

 int flatten_range_list(RangeList* range_list)
 {
     int flattened = 0;
     /* Return 0 if there is only one range remaining */
     if(range_list->size <= 1)
     {
         return flattened;
     }
     int current = 0;

     while (current < range_list->size)
     {
         int compared = current + 1;
         while (compared < range_list->size)
         {
             if(check_range_overlap(range_list->list[current], range_list->list[compared]))
             {
                 flattened = 1;
                 range_list->list[current] = merge_ranges(range_list->list[current], range_list->list[compared]);
                 for(int i = compared; i < range_list->size-1; i += 1)
                 {
                     range_list->list[i] = range_list->list[i+1];
                 }
                 range_list->size -= 1;
             }
             else
             {
                 compared += 1;
             }
         }
         current += 1;
     }

     return flattened;
 }

 long int count_range_lists_covered(RangeList ranges)
 {
     long int count = 0;
     for(int i = 0; i<ranges.size; i += 1)
     {
         /* Add 1 for single element ranges */
         count += (ranges.list[i].stop - ranges.list[i].start) + 1;
     }

     return count;
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
    }
    /* Close file */
    fclose(fptr);

    /* Puzzle 1 solution */
    printf("Number of fresh items: %d\n", fresh_count);

    /* Flattening ranges */
    int flattened = 0;
    do
    {
        flattened = flatten_range_list(&ranges);

    }
    while(flattened == 1);

    printf("Flattened ranges:\n");
    print_ranges(ranges);


    printf("Count of numbers covered by all ranges equals %ld\n", count_range_lists_covered(ranges));

    return 0;
}
