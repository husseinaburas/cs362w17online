#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define CHARSET_SIZE 128
#define ALPHA_SIZE 26

char inputChar()
{
    int n = (rand() % (CHARSET_SIZE-33))+32;
    return (char)n;
}

static char *randString(char *str, size_t size)
{
    size_t i;
    int k;
    const char vowels[] = "aeiou";

    if (size) {
        --size;
        for (i = 0; i < size; i++)
        {
            if (i == 0 || (i%2 == 0))
                str[i] = (rand() % (ALPHA_SIZE))+97;
            else
                str[i] = vowels[(rand() % 5)];
        }
        str[size] = '\0';
    }

    return str;
}

char *inputString()
{
    // Long way, no oracle
    //int size = (rand() % 10) + 3; // Ensure char count is > 2 and < 12

    int size = 6;
    char *s = malloc(size+1);
    if (s)
        randString(s, size);

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
