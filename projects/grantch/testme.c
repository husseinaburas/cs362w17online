#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    //by Christopher Grant
    char *charList = " []{}()ax"; //char array to pick values from
    int randListPos = 0; //for rand() var.
    randListPos = rand() % 9; //set var to a rand in between 0...8
    return charList[randListPos];
}

char *inputString()
{
    // TODO: rewrite this function
    //by Christopher Grant
    int i; //for for-loops
    char *charList = "erst"; //char array to pick values from
    int randListPos = 0;
    randListPos = rand() % 4;
    char *tempString = malloc(sizeof(char)*6); //malloc char array size 6
    //this for-loop places a char from inputChar in 0-4;
    for(i = 0; i < 5; i++){
        randListPos = rand() % 4; //for rand() var.
        tempString[i] = charList[randListPos]; //set var to a rand in between 0...3
    }
    tempString[5] = '\0'; //[5] is set to null term.
    return tempString; //return string pointer
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
