# Advent of Code 2025

Since I usually missed [Advent of Code](https://adventofcode.com/) events or it felt I was to late I decided to give it a shot this year. I have a couple of goals:
* Solve all the puzzles (on time if possible).
* Use raw C without much external libraries.
* Try to keep code clean and easy to read.
* Journal my tries so I can look back on what I've done.

I'll try to give [Zed](https://zed.dev/) a shot as an editor + use old and loved [gcc](https://gcc.gnu.org/) as compiler.


## Day 1: Secret Entrance
[First puzzle](https://adventofcode.com/2025/day/1) looked like your standard programing task, load data and do something with it. I think I spend more time on writing code to load data from the file and split it into different variables than on solution itself. The problem appeared when I tried to solve the second puzzle. For whatever reason I couldn't figure out all the edge cases right (has it made past that 0 or not, how to we handle 100 step rotation that starts on 0, when to actually count what.) In the end, my first solution didn't worked, so I went back to my original puzzle 1 soultion, changed it to pass pointer to position and return number of times 0 was "dialed past". I wasn't sure of my solution (both solved example correctly) but it worked on the first time.
To run day 1 solution make sure your input data is in /inputs directory as day1.txt and run the following command:
``` shell

gcc day1.c -o main.out -lm
./main.out

```
