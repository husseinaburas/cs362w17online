#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/*
* Name: Grace Thompson
* CS 362 Random Testing Quiz 2
*/

char inputChar()
{
    //make array of possible char inputs
    char arr[10] = {'[', ']', '(', ')', '{', '}', ' ', 'a', 'x', 't'}; //with one extra character not involved in testme()
    //return one randomly selected character from array.
    return arr[rand() % 10];
}

char *inputString()
{
    //create a string made of randomly ordered r, e, s, e, t, \0
    char *str;
    //allocate memory for string
    str = (char *) malloc(6); //enough for six characters
    //set all indices to zero for initialization
    int i;
    for (i = 0; i < 6; i++) {
      str[i] = 0;
    }
    char options[6] = {'r', 'e', 's', 'e', 't', '\0'};
    //iterate through options, placing in different string positions
    int optionsIdx = 0;
    int idx = -1; //initialize to an invalid value
    while (optionsIdx < 6) {
      //get a random index between 0 and 5
      idx = rand() % 6;
      if (str[idx] == 0) {
        //if position of index is empty, place char
        str[idx] = options[optionsIdx];
        optionsIdx++; //move to next character
      }
    }

    return str;
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
    free(s); //free allocated memory
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
