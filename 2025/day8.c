/*
 * Advent of Code 2025: Day 8: Playground
 * https://adventofcode.com/2025/day/8
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
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


 int comp(const void *a, const void *b) {
     return (*(int*)b - *(int*)a);
 }

 JunctionBox new_box(double x, double y, double z)
 {
     JunctionBox box;
     box.x = x;
     box.y = y;
     box.z = z;
     box.connection = -1;

     return box;
 }

 double get_distance(JunctionBox a, JunctionBox b)
 {
     double distance;
     double x_pow = pow(a.x-b.x, 2);
     double y_pow = pow(a.y-b.y, 2);
     double z_pow = pow(a.z-b.z, 2);

     distance = sqrt(x_pow + y_pow + z_pow);

     return distance;
 }

 void print_box_list()
 {
     for(int i = 0; i < box_count; i++)
     {
         JunctionBox box = box_list[i];
         printf("Box [%d]: x = %lf, y = %lf, z = %lf. Connection = %d\n", i, box.x, box.y, box.z, box.connection);
     }
 }

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
     //printf("Linking: %d, %d \n", c_a, c_b);
     link_boxes(&box_list[c_a], &box_list[c_b]);
     last_a = c_a;
     last_b = c_b;

     return closest;
 }

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
     printf("Biggest 3: %d, %d, %d\n", connections[0], connections[1], connections[2]);

     return result = connections[0] * connections[1] * connections[2];
 }

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
     print_box_list();
     printf("Last two: %d, %d\n", last_a, last_b);
     long long int result_2 = box_list[last_a].x * box_list[last_b].x;
     printf("Second puzzle solution: %lld\n", result_2);

     //print_distance_grid(box_count);
     //
     //print_distance_grid(box_count);

     return 0;
 }
