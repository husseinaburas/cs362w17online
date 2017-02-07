// randomstring.c
// 
// Allan Reitan
// Oregon State University - CS 362 W2017
// 
// RandomTestQuiz
// Purpose: generating a random test sequencer for a sample file provided.
// 
// Provided sample file given was a titled testme.c and contained the following:
// 
/* BEGIN Code Sample
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    return ' ';
}

char *inputString()
{
    // TODO: rewrite this function
    return "";
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
END CODE Sample */

/* BEGIN Discussion of testing
First glance immediately observed a routing that would require a random char input.
Also the need to be able to generate random strings, not sure if there were requirements for practical strings.

Looking at the code at a very high level when certain characters are input it increments a State variable, until it reaches
a value of 9.  At that point it stops incrementing and looks for the random string to be exactly the word, "reset".

So at a minimum the Random string function needs to return an array of size 6 (5 chars and a /0).
However, the likely probability that random string is going to produce exactly the word "reset" in order is not very likely.

Some thoughts are that a random generator could be used as "roll of the dice", and then use a switch statement to prepopulate the response.
This would allow for one of the events to come out with the word, "reset".  
Should there be other words to try out then the switch could be adapted for this consideration.

Found a random character generation discussion in C online at: http://stackoverflow.com/questions/19724346/generate-random-characters-in-c
So it was adapted to allow for a range of ASCII Chars from 32 - 126 to take in All Alphas and Grammatical elements that the code could allow for.

Used GDB for some basic debugging and to find a pointer NULL reference.

END Discussion of testing */