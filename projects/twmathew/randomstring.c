#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/*
Thomas Mathew
CS 362
This file describes my thought process for Quiz #2

Description: Implement a random tester for the function testme() in testme.c that is capable of printing the error message. 
You should implement inputChar() and inputString() to produce random values. Write up the development of your random tester and how it finds the error message as randomstring.c. 
Submit testme.c and randomstring.c under your onid directory in class github. (under your onid directory and not under dominion directory). 
The randomstring.c is a text file that outlines how you developed your solution and how it works!
*/


/*
The inputChar() function simply needs to return a random character.
The testme() function will only take action when inputChar() returns one of 8 values: the lowercase characters "a" and "x", and also these six characters: [ ( { } ) ]
There are 127 characters in the ASCII table. We could include all 127, or only include #'s 40 through 127, as the parnetheses characters are the lowest values, at #40 and #41.
Or, we could be even more picky and do #'s 40, 41, and 91 through 125, which would include the needed values, along with all other lowercase letters and a few stragglers.

In order to get inputChar working, I made a file called charTester.cpp. At first, the test was just resulting in the same character over and over. 
I hypothesized that the problem was that the program was running too fast, and so srand(time) was getting the same result over and over.
To fix this, the sleep function was used to "pause" the program. However, I realized that this would make testing a large volume very slow.
So I dug deeper and realized that the actual problem was that I has the seed, srand() inside the inputChar function, and thus seeding was occuring on each loop
Instead I moved it to main(), so that seeding only occured once, before the loop. I also realized that in the actual testme.c, the seeding is done in the main, so that takes care of that.

*/


/*
With the inputString function, I first tried to use the inputChar function to fill the string, aka array of characters
However I ran into some problems so I decided to just directly randomize the string instead
I decided to restrict the domain to lowercase letters, since the trigger result is "reset"
I had some problems using a char pointer, so I switched to an array of characters.
*/

/*
The next step was to implement both functions into testme.c. The inputChar() function worked pretty well, but the test was not progressing past 'state = 3'
So, I realized that the problem was that I forgot the "space" character, at ASC number 32. Without this character, state 4 can't be reached. So to fix this, I increased the range to 32 through 127

There was some strange behavior with inputString() as well. I decided for simplicity to force the array to be 5 characters long, and force the "6th" character to be NULL.
Otherwise, the number of tests needed to eventually get "reset" would be essentially infinite.
On a similar note, I was finding that even a fixed string of length 5 was taking many, many interations to reach "reset" (More than 300,000 iterations)
Even fixing the first character to "r" resulted in more than 300,000 iterations.
Once I fixed the first two characters to "re", testme.c typically reached "reset" in ~11,000 to ~17,000 iterations

*/





int main(int argc, char *argv[])
{
    return 0;
}
