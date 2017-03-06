//Chris Brackett
//bracketc@oregonstate.edu
//CS362 - Random Testing Quiz 2
// 1/30/2017

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //get random ASCII character from 32 (space) to 126 (~)
    char randomChar = rand() % (127-32) + 32;
    return randomChar;
}

char *inputString()
{
    static char string[6]; //5 chars plus terminating null
    int i = 0;
    for (i = 0; i < 5; i++) //create string of random characters (a-z)
    {
        string[i] = rand() % (123-97) + 97;
    }
    string[5] = '\0'; //add terminating null to end of string
    return string;
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
