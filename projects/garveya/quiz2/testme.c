#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//for the maximum char size
#include <limits.h>

//create global variable to store return value from inputString
//because we cannot use malloc(), since testme() never frees the
//memory, causing a memory leak
#define INPUT_STRING_BUFFER_LENGTH 256
char inputStringBuffer[INPUT_STRING_BUFFER_LENGTH];

char inputChar()
{
    //use the maximum and minimum values of chars
    //to find the total range
    int charRange = CHAR_MAX - CHAR_MIN;
    //use mod to make sure random number is within range
    //add minimum character to make sure random number
    //is within minimum character value
    return (rand() % charRange) + CHAR_MIN;
}

char *inputString()
{
    //have to use global variable here and not malloc, since
    //testme doesn't free pointer
    //clear data from string buffer
    memset(inputStringBuffer, '\0', INPUT_STRING_BUFFER_LENGTH);
    //select a random string length within size of buffer - 1
    //need last character in buffer to be null char
    int randomLength = rand() % (INPUT_STRING_BUFFER_LENGTH - 1);
    //return reset if length is 0, because otherwise
    //testme will never exit
    if(randomLength == 0){
      return "reset";
    }
    //fill buffer up with random characters up to the random length
    //by using random char function
    int i;
    for(i = 0; i < randomLength; ++i){
      inputStringBuffer[i] = inputChar();
    }
    return inputStringBuffer;
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