#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  // Limit domain of random numbers to those that affect state
  char options[9] = { '[', '{', ' ', 'a', 'x', ']', ')', '}', '('  };
  // select a random index in array from 0 to 8
  int char_index = rand() % 9;

  // return random char from options
  return options[char_index];
  
}

char *inputString()
{
  // string lench is 6
  int length = 6,
      i,
      char_index;
  // Allocate space for the string
  char *string = malloc( length  * sizeof(char) ),

  // char options for the string
       str_options[5] = {'\0', 'r', 's', 't', 'e' };

  for (i = 0; i < length;  i++)
  {
    // randomly index str_options to build string
    char_index = rand() % 5;
    string[i] = str_options[char_index];

  } 

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
