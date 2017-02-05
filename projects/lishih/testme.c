#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX_LENGTH 6
char inputChar()
{
    // TODO: rewrite this function

    int randNum;
    //random int
    randNum  = rand() % 26;
    // add 97 to randNum to lowercase letter
    randNum = randNum + 97;
    //convert randNum to type char
    char randChar = (char) randNum;
    return randChar;
}

char *inputString()
{
    // TODO: rewrite this function
    int i;
    // input array of size 5
    int array[5] = {'r', 'e', 's', 't', '\0'};

    // allocation array memory
    char *randString =(char*) malloc (sizeof(char)* MAX_LENGTH);

    for(i = 0; i <MAX_LENGTH; i++){
        randString[i] = array [rand()%5];
    }

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
