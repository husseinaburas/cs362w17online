#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // generates 0 through 125 ascii
  // changes range to 32 - 125, starting with ' '
  int randNum;
  while (randNum < 32) {
    randNum = rand() % 126;
  }
    return (char)randNum;
}

char *inputString()
{
  char *inputString = malloc(sizeof(char));
  for (int i = 0; i < 5; i++) {
    // generates 0 through 122 ascii
    // changes range to 97 - 122, which is 'a' to 'z'
    int randNum = 0;
    while (randNum != 101 && randNum != 114 &&
       randNum != 115 && randNum != 116) {
      randNum = rand() % 123;
    }
    inputString[i] = (char)randNum;
  }
  inputString[5] = '\0';
  return inputString;
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
      printf("error \n");
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
