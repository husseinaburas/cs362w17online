#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//int counter = -1;
char inputChar()
{
    // TODO: rewrite this function

  //Direct route just to make sure that it is possible to get to the error msg. 
  //char errorString[] = "[({ ax})]";
  //counter++;
  //return errorString[counter];

  //Returns a random character within the printable character range.
  char randChar = (char)((rand() % (128 - 32)) + 32);
  return randChar;

}

char *inputString()
{
    // TODO: rewrite this function
  int randStringLength = 6; 
  char* randString = (char* )malloc(sizeof(char) * randStringLength); //char array for the string we'll return
  
  int i; //loop counter
  for (i = 0; i < randStringLength - 1; i++){
    randString[i] = (char)((rand() % (122 - 97)) + 97);
  }

  //close off out character array to be a valid string
  randString[randStringLength - 1] = '\0';

  return randString;
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
