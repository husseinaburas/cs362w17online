#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

using namespace std;

char inputChar()
{
      char cha = rand() % 94 + 32;

    return cha;
}

char *inputString()
{
    char* t =new char[5];
    t[0] = rand() % 94 + 32;
    t[1] = rand() % 94 + 32;
    t[2] = rand() % 94 + 32;
    t[3] = rand() % 94 + 32;
    t[4] = rand() % 94 + 32;
    return t;
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
    s = "reset";
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
