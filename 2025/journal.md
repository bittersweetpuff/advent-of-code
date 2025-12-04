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
```console

gcc day1.c -o main.out -lm
./main.out

```

## Day 2: Gift Shop

So when I looked at [Day 2](https://adventofcode.com/2025/day/2) I instantly felt like using C was a bad idea (lol). However the strength of this language is that others had similar issues for over 50 years, so there are already solutions for most of those common cases. Second thing: when I saw input data, I already knew how the second part of the puzzle would look like. Anyway, managed to solve fist puzzle before work (and fall in love with sscanf - another sign of how much I don't know C) and will try to solve second part in the afternoon.

And so I did as I said. To be honest while I was thinking to treat numbers here as strings (sorry, arrays of chars...) and check for repeat substrings, but no. I went with regular operations on numbers like a good Cookie I am. Overall, nice puzzle, liked it better then the first one, becouse it was more about solution itself and less about edge cases. Still, I get quite nervous when thinking about limits of data types, but there is nothing long long int can't solve. Anyway.
To run day 2 solutions again provide your input and run:
```console

gcc day2.c -o main.out -lm
./main.out

```
And lets hope day 3 won't crush me.


## Day 3: Lobby

...and it didnt. To be honest it was the easiest [puzzle](https://adventofcode.com/2025/day/3) out of them all so far, very school-like, with iterating over the array while changing the start and end of each iteration. It is also first time when I can say I'm feeling ok with how my solution look like. Also managed to do this without any includes beside <stdio.h>, but to be honest I have no idea where I could even use something here. Anyway, run it the same way as previous ones:
```console

gcc day3.c -o main.out -lm
./main.out

```

## Day 4: Printing Department

Oh boy... here we go. So this [day](https://adventofcode.com/2025/day/4) I decided, why not, why shouldnt I use *malloc*. In the end I'm kinda conflicted on my solution. I really like my dynamicly allocated adjacency matrix on one hand, and it really made it easy to solver second part of the puzzle. But I dislike the amount of "trust me bro" code with accessing arrays, mutable values and stuff. In general, I think this day was the most fun. How to run? We'll i don't need math.h this time so:
```console

gcc day4.c -o main.out
./main.out

```
