/*
 * Advent of Code 2025: Day 8: Playground
 * https://adventofcode.com/2025/day/8
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Struct representing a JunctionBox
 */
 typedef struct
 {
     double x;
     double y;
     double z;
     int connection;
 } JunctionBox;

 /* Globals */
 double distance_grid[1000][1000] = {0.0};
 JunctionBox box_list[1000];
 int box_count = 0;
 int connection_count = 0;
 /* For puzzle 2 */
 int last_a, last_b;


 /*
  * Totaly stolen comp function for quick sort
  */
 int comp(const void *a, const void *b)
 {
     return (*(int*)b - *(int*)a);
 }

 /*
  * JunctionBox builder
  */
 JunctionBox new_box(double x, double y, double z)
 {
     JunctionBox box;
     box.x = x;
     box.y = y;
     box.z = z;
     box.connection = -1;

     return box;
 }

 /*
  * Function returns distance between two boxes
  */
 double get_distance(JunctionBox a, JunctionBox b)
 {
     double distance;
     double x_pow = pow(a.x-b.x, 2);
     double y_pow = pow(a.y-b.y, 2);
     double z_pow = pow(a.z-b.z, 2);

     distance = sqrt(x_pow + y_pow + z_pow);

     return distance;
 }

 /*
  * Used for debug. Prints list of all junction boxes
  */
 void print_box_list()
 {
     for(int i = 0; i < box_count; i++)
     {
         JunctionBox box = box_list[i];
         printf("Box [%d]: x = %lf, y = %lf, z = %lf. Connection = %d\n", i, box.x, box.y, box.z, box.connection);
     }
 }

 /*
  * Used for debug. Prints the distance grid
  */
 void print_distance_grid(int limit)
 {
     for(int i = 0; i < limit; i += 1)
     {
         for(int j = 0; j < limit; j += 1)
         {
             printf("%lf ", distance_grid[i][j]);
         }
         printf("\n");
     }
 }

 /*
  * Calculates all distances between boxes and saves them in grid
  */
 void populate_distance_grid()
 {
     for(int a = 0; a < box_count - 1; a += 1)
     {
         for(int b = a + 1; b < box_count; b += 1)
         {
             distance_grid[a][b] = get_distance(box_list[a], box_list[b]);
         }
     }
 }

 /*
  * Links two boxes. If they are both disconected it creates new connection.
  * If one of them is connectes it adds that connection to another
  * If both are connected merges both connections into one and updates all related boxes
  */
 void link_boxes(JunctionBox *a, JunctionBox *b)
 {
     if(a->connection == -1 && b->connection == -1)
     {
         a->connection = b->connection = connection_count;
         connection_count += 1;
     }
     else if(a->connection == -1)
     {
         a->connection = b->connection;
     }
     else if(b->connection == -1)
     {
         b->connection = a->connection;
     }
     else
     {
         int b_con = b->connection;
         b->connection = a->connection;
         for(int i = 0; i<box_count; i += 1)
         {
             if(box_list[i].connection == b_con)
             {
                 box_list[i].connection = a->connection;
             }
         }
     }
 }

 /*
  * Finds 2 closest boxes that are further away from each other than previous distance and links them.
  * Returns the distance between them so it can be run in loop.
  */
 double link_closest_boxes(double prev_lowest)
 {
     double closest = 99999999.0;
     int c_a, c_b;
     for(int i = 0; i < box_count; i += 1)
     {
         for(int j = 0; j < box_count; j += 1)
         {
             if(distance_grid[i][j] < closest && distance_grid[i][j] > prev_lowest)
             {
                 closest = distance_grid[i][j];
                 c_a = i;
                 c_b = j;
             }
         }
     }
     link_boxes(&box_list[c_a], &box_list[c_b]);
     last_a = c_a;
     last_b = c_b;

     return closest;
 }

 /*
  * Puzzle 1
  * Counts all boxes in each connection and returns the multiplication of counts of 3 biggest connections
  */
 long long int get_biggest_connection_multi()
 {
     long long int result = 1;
     int connections[1000] = {0};
     for(int i = 0; i < box_count; i += 1)
     {
         if(box_list[i].connection != -1)
         {
             connections[box_list[i].connection] += 1;
         }
     }
     qsort(connections, 1000, sizeof(int), comp);
     return result = connections[0] * connections[1] * connections[2];
 }

 /*
  * Checks if all boxes are connected. Used as loop condition for puzzle 2.
  */
 int check_if_one_connection()
 {
     if(box_list[0].connection == -1)
     {
         return 0;
     }
     int test_connection = box_list[0].connection;
     for(int i = 1; i<box_count; i += 1)
     {
         if(box_list[i].connection != test_connection)
         {
             return 0;
         }
     }
     return 1;
 }


 int main(int argc, char *argv[])
 {
     /* Create pointer to the file */
     FILE *fptr;
     /*  Open a file in read mode */
     fptr = fopen("./inputs/day8.txt", "r");
     /*  Store the content of the file */
     char inputString[500];

     while (fgets(inputString, 500, fptr))
     {
         double x, y, z;
         sscanf(inputString, "%lf,%lf,%lf", &x, &y, &z);
         box_list[box_count] = new_box(x, y, z);
         box_count += 1;
     }
     /* Close the file */
     fclose(fptr);

     populate_distance_grid();
     double last = 1.0;
     for(int i = 0; i<1000; i++)
     {
         last = link_closest_boxes(last);
     }
     long long int result_1 = get_biggest_connection_multi();
     printf("First puzzle solution: %lld\n", result_1);
     while(!check_if_one_connection())
     {
         last = link_closest_boxes(last);
     }
     long long int result_2 = box_list[last_a].x * box_list[last_b].x;
     printf("Second puzzle solution: %lld\n", result_2);
     return 0;
 }
