#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // TODO: rewrite this function
  int r = (rand() % 95) + 32; // generate a random ASCII value from 32-126
    // printable characters only (omits control characters)
  return r; // return random ASCII value as char
}

char *inputString()
{
    // TODO: rewrite this function
  int i, r;
  char *randomStr = malloc(sizeof(char) * 6); // includes null char
  // generate a string of 5 random lowercase letters
  for (i = 0; i < 5; i++) {
    r = rand() % 26;
    // add 97 to random number (0-25) to get an ASCII value from 97-122, which
    // corresponds to letters from lowercase letters a-z
    randomStr[i] = 97 + r;
  }
  return randomStr;
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
