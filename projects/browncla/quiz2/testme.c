#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_LENGTH 6

//Getting valid character, ASCII values between 32 and 126.
char inputChar()
{
    
  char randomLetter = (rand() % 95) + 32; //random number between 32 and 126
  assert(randomLetter > 31 && randomLetter < 127); //checking its valid
  return randomLetter; //returning the character
}

//Getting a 6 letter string made up of the characters r, e, s, t, /0
char *inputString()
{
  int i, randNum;
  char * inString = (char *)malloc((MAX_LENGTH) * sizeof(char));
  char letters[5] = {'r', 'e', 's', 't', '\0'}; //array of letters that we want
  for (i = 0; i < MAX_LENGTH; i++){
    randNum = rand() % 5; //getting a random letter from letters array
    memcpy(&inString[i], &letters[randNum], 1);
  }
  return inString;
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

    if (c == '[' && state == 0) 
      state = 1;
    if (c == '(' && state == 1) 
      state = 2;
    if (c == '{' && state == 2) 
      state = 3;
    if (c == ' '&& state == 3) 
      state = 4;
    if (c == 'a' && state == 4) 
      state = 5;
    if (c == 'x' && state == 5) 
      state = 6;
    if (c == '}' && state == 6) 
      state = 7;
    if (c == ')' && state == 7) 
      state = 8;
    if (c == ']' && state == 8) 
      state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      free(s);
      exit(200);
    }
    free(s);
  }


}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}