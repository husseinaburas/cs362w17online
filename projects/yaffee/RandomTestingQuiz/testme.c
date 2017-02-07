/*****************************************************************************************************************
 * Name: Emma Yaffe
 * Class: CS 362
 * Assignment: Random Testing Quiz
 * Description: Implemented two functions, inputChar() and inputString() to randomly test inputs until testme()
 * prints an error message
*****************************************************************************************************************/
 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/* uses ASCII decimal representations to return a random character
 * ' ' = 32, '(' = 40, ')' = 41, 'a' = 97, 'x' = 120, '{' = 123, '}' = 251
*/
char inputChar()
{
    int characters[] = {32, 40, 41, 91, 93, 97, 120, 123, 125};
    int randomChar = rand() % 9;
    return characters[randomChar];
}

/* uses ASCII decimal representations to return a random string made of the
 * the characters that create the word reset, followed by a null terminating character
 * 'r' = 114, 'e' = 101, 's' = 115, 't' = 116
*/
char *inputString()
{
   int i;
   int letters[] = {114, 101, 115, 116};
   int randomLetter;
   char *string = malloc(sizeof(char)*6);
   for(i = 0; i < 5; i++) {
      randomLetter = rand() % 4;
      string[i] = letters[randomLetter];
   }
   string[5] = '\0';
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
