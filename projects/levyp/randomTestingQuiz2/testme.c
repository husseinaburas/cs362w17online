#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
 
char inputChar()
{
  //char possibleVals[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
  char possibleVals[33] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'y', 'z'};
  int randIndex = rand()%33;
  return possibleVals[randIndex];
}

char *inputString()
{
  char possibleValues[6] = {'r', 'e', 's', 'e', 't', '\0'};
  // Note - when expanding to this many possibilities the program doesn't ever finish.
  //char possibleValues[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
  char *randomString = malloc (sizeof (char) * 6);
  int i = 0;
  for(i = 0; i < 6; i++) {
    randomString[i] = possibleValues[rand()%6];
  }
  return randomString;
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