#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // ASCII chars range from 32-126
    // generate values from 0-94 and add 32
    time_t t;
    int n; // ASCII value to be used

    // initialize random number generator
    srand((unsigned) time(&t));

    // generate random number
    n = rand() % 95 + 32;

    return (char)n;
}

char *inputString()
{
    // generate string of random length (0-64)
    int n; // length of string
    char *s; // the string

    n = rand() % 6 + 1; // length at least 1; max 6

    s = malloc(sizeof (char) * n);

    int i; // iterator
    for (i=0; i < n; i++){
      s[i] = inputChar();
      // sleep(1); // wait so that we can get different chars in the string
    }

    return s;
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
