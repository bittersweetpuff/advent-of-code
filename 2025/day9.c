/*
 * Advent of Code 2025: Day 9: Movie Theater
 * https://adventofcode.com/2025/day/9
 */
 #include <stdio.h>
 #include <stdlib.h>

 typedef struct
 {
    int start_x, start_y, end_x, end_y;
 } Wall;

 /* Globals here we go */
 /* List of all corners */
 int corners[1000][2] = {0};
 Wall vertial_walls[500];
 Wall horizontal_walls[500];
 /* Count of corners */
 int corners_count = 0;
 int vertical_count = 0;
 int horizontal_count = 0;
 int x_limit = 0;
 int y_limit = 0;


 /*
  * Standard max function for long int, returns bigger value
  */
int max(int a, int b)
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

 /*
  * Standard min function for long int, returns smaller value
  */
 int min(int a, int b)
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

 Wall new_wall(int ax, int ay, int bx, int by)
 {
     Wall n_wall;
     n_wall.start_x = min(ax, bx);
     n_wall.start_y = min(ay, by);
     n_wall.end_x = max(ax, bx);
     n_wall.end_y = max(ay, by);
     //printf("New wall from between (%d,%d) and (%d,%d)\n", ax, ay, bx, by);
     //printf("Limits are (%d,%d) and (%d,%d)\n", n_wall.start_x, n_wall.start_y, n_wall.end_x, n_wall.end_y);
     return n_wall;
 }

 long long int calculate_area(int xa, int ya, int xb, int yb)
 {
     long long int area;
     long long int x = abs(xa - xb)+1;
     long long int y = abs(ya - yb)+1;
     area = x*y;
     return area;
 }

 long long int get_biggest_area()
 {
     long long int biggest = 0;
     for(int a = 0; a < corners_count - 1; a += 1)
     {
         for(int b = a + 1; b < corners_count; b += 1)
         {
             int xa = corners[a][0];
             int ya = corners[a][1];
             int xb = corners[b][0];
             int yb = corners[b][1];
             long long int area = calculate_area(xa, ya, xb, yb);
             //printf("Area between (%d,%d) and (%d,%d) = %ld\n", xa, ya, xb, yb, area);
             if(area >= biggest)
             {
                 printf("New biggest area between (%d,%d) and (%d,%d) = %lld\n", xa, ya, xb, yb, area);
                 biggest = area;
             }
         }
     }
     return biggest;
 }

 void add_new_wall(Wall new_wall)
 {
     if(new_wall.end_x == new_wall.start_x)
     {
         vertial_walls[vertical_count] = new_wall;
         vertical_count += 1;
     }
     else
     {
         horizontal_walls[horizontal_count] = new_wall;
         horizontal_count += 1;
     }
 }

 void fill_walls_array()
 {
     for(int i = 0; i < corners_count-1; i += 1)
     {
         add_new_wall(new_wall(corners[i][0], corners[i][1], corners[i+1][0], corners[i+1][1]));
     }
     /* Wrap list */
     add_new_wall(new_wall(corners[corners_count-1][0], corners[corners_count-1][1], corners[0][0], corners[0][1]));
 }

 int point_on_wall(Wall checked_wall, int x, int y, int horizontal)
 {
     if(horizontal)
     {
         if(y == checked_wall.end_y && (x >= checked_wall.start_x && x <= checked_wall.end_x))
         {
             return 1;
         }
         else
         {
             return 0;
         }
     }
     else
     {
         if(x == checked_wall.end_x && (y >= checked_wall.start_y && y <= checked_wall.end_y))
         {
             return 1;
         }
         else
         {
             return 0;
         }
     }
 }

 int point_on_any_vertical_wall(int x, int y)
 {
     int on_wall = 0;
     for(int i = 0; i < vertical_count; i+=1)
     {
        if(point_on_wall(vertial_walls[i], x, y, 0))
         {
             on_wall = 1;
             return on_wall;
         }
     }
     return on_wall;
 }

 int wall_intersect(Wall vertical, Wall horizontal)
 {
     // vertical: x = vertical.start_x
     // horizontal: y = horizontal.start_y

     int vx = vertical.start_x;
     int hy = horizontal.start_y;

     // Check if vertical X lies inside horizontal segment
     if (vx < horizontal.start_x || vx > horizontal.end_x)
         return 0;

     // Check if horizontal Y lies inside vertical segment
     if (hy < vertical.start_y || hy > vertical.end_y)
         return 0;

     return 1;
 }

 int check_if_point_inside(int x, int y)
 {
     int valid = 1;
     int intersects = 0;
     /* X axis: vertical walls */
     for(int i = x+1; i<x_limit+1; i+=1)
     {
         if(point_on_any_vertical_wall(i, y))
         {
             intersects += 1;
         }
     }
     if(intersects%2 == 0)
     {
         return 0;
     }
     else
     {
         return 1;
     }
 }

 int is_valid_box(int min_x, int min_y, int max_x, int max_y)
 {
     int valid = 1;
     Wall h1 = new_wall(min_x+1, min_y+1, max_x-1, min_y+1);
     Wall h2 = new_wall(min_x+1, max_y-1, max_x-1, max_y-1);
     Wall v1 = new_wall(min_x+1, min_y+1, min_x+1, max_y-1);
     Wall v2 = new_wall(max_x-1, min_y+1, max_x-1, max_y-1);
     for (int i = 0; i < horizontal_count; i++)
     {
         if(wall_intersect(v1, horizontal_walls[i]) || wall_intersect(v2, horizontal_walls[i]))
         {
             return 0;
         }
     }
     for (int i = 0; i < vertical_count; i++)
     {
         if(wall_intersect(vertial_walls[i], h1) || wall_intersect(vertial_walls[i], h2))
         {
             return 0;
         }
     }
     return valid;
 }

 long long int get_biggest_valid_area()
 {

     long long int biggest = 0;
     long int counter = 1;
     for(int a = 0; a < corners_count - 1; a += 1)
     {
         for(int b = a + 1; b < corners_count; b += 1)
         {
             printf("New check [%ld]\n", counter);
             int xa = corners[a][0];
             int ya = corners[a][1];
             int xb = corners[b][0];
             int yb = corners[b][1];
             long long int area = calculate_area(xa, ya, xb, yb);
             //printf("Area between (%d,%d) and (%d,%d) = %ld\n", xa, ya, xb, yb, area);
             if(area >= biggest)
             {
                 printf("Checking new potential biggest\n");
                 if(is_valid_box(min(xa, xb), min(ya, yb), max(xa, xb), max(ya, yb)))
                 {
                     printf("New biggest area between (%d,%d) and (%d,%d) = %lld\n", xa, ya, xb, yb, area);
                     biggest = area;
                 }
                 else
                 {
                     printf("Nope\n");
                 }
             }
             counter += 1;
         }

     }
     return biggest;
 }

 int main(int argc, char *argv[])
 {
     /* Create pointer to the file */
     FILE *fptr;
     /*  Open a file in read mode */
     fptr = fopen("./inputs/day9.txt", "r");
     /*  Store the content of the file */
     char inputString[500];

     while (fgets(inputString, 500, fptr))
     {
         int x, y;
         sscanf(inputString, "%d,%d", &x, &y);
         corners[corners_count][0] = x;
         corners[corners_count][1] = y;
         printf("scanned: %d, %d\n", x, y);
         corners_count += 1;
         if(x > x_limit)
         {
             x_limit = x;
         }
         if(y > y_limit)
         {
             y_limit = y;
         }
     }
     fclose(fptr);
     fill_walls_array();

     long long int biggest_area_possible = get_biggest_area();
     printf("limits: %d, %d\n", x_limit, y_limit);
     printf("Horizontals and Verticals: %d, %d\n", horizontal_count, vertical_count);
     printf("Point inside: %d\n", check_if_point_inside(2, 3));
     long long int biggest_valid_area_possible = get_biggest_valid_area();
     printf("The biggest possble area is: %lld\n", biggest_area_possible);
     printf("The biggest valid possble area is: %lld\n", biggest_valid_area_possible);
     return 0;
 }
