#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // TODO: rewrite this function

  //Returns a random printable ASCII character
  //ASCII printable characters range from 32 to 127
  return (char) (32 + (rand() % 96));
}

char *inputString()
{
  // TODO: rewrite this function

  //For simplification purposes, string length is hard coded to 5 (plus the '\0')
  //See writeString.c for more details
  int strLen = 5;
  //Length of string is increased by 1 to account for the extra '\0'
  char *newStr = malloc( (strLen + 1) * sizeof(char) );

  int i;
  for (i = 0; i < strLen;  i++)
  {
    newStr[i] = inputChar();

  } 

  //Remember to terminate string 
  newStr[strLen] = '\0';

  return newStr;

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
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
