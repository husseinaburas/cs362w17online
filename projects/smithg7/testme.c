#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //Generate a random integer between 32 & 126 (ASCII values)
    //Cast that to a character and return that.
    int newC = 32+rand()%94;
    char newChar = (char)newC;

    return newChar;
}

char *inputString()
{
    //Create a string of random length
    //fill in that string with random characters
    int randStringLength = 6; //rand()%10; //Limiting the random string to at most 10 characters.
    char *newString = malloc(sizeof(char)*randStringLength);
    int i = 0;
    for (i = 0; i < randStringLength-1; i++)
    {
      int newC = 97+rand()%26;
      newString[i] = (char)newC;
    }
    newString[randStringLength-1] = '\0'; //NULL terminator

    return newString;
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

    //Looking for characters in this order: [({ ax})] and then the string 'reset\0'
    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
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

    //added a counter exit @ 24,000,000 to prevent an infinite while loop.
    //if(tcCount == 24000000) exit(100);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
