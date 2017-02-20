// Erin Rosenbaum
// cs_362 Winter_2017
// February 5, 2017
// quiz 2 - testme.c

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function

    // create a character array with all required inputs
    char my_array[] = "[]{}() ax";

    // randomly generate an integer from 0 through 8, representing
    // the indeces of the character array
    int rand_num = rand() % 9;

    // return the random character
    char rand_char = my_array[rand_num];
    return rand_char;
}

char *inputString()
{
    // TODO: rewrite this function

    // create a character array with all required inputs
    char my_array[] = "\0reset";

    // create space in memory for random character array
    char* result = malloc(6 * sizeof(char));

    // create a resulting charter array of length 6 composed of random chars from input array
    int i;
    for (i=0; i<6; i++){
        int rand_num = rand() % 6;
        char rand_char = my_array[rand_num];
        result[i] = rand_char;
    }

    return result;
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