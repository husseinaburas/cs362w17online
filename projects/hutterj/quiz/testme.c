#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/*
Name: Jon Hutter, hutterj
Date: 2017/02/05
testme.c
*/

char inputChar()
{
	// TODO: rewrite this function
	char randchar = ' ';

	// assumption: only printable characters (from 32 space to 126 ~) 
	randchar = (rand() % 95) + 32;
	
    return randchar;
}

char *inputString()
{
    // TODO: rewrite this function
	int randStringLen, i;

	// assumption: characters of length 0-9 chars
	randStringLen = rand() % 10;
	char randChar;
	char* randString;
	
	randString = (char *) malloc (sizeof(char) * randStringLen);
	
	for (i = 0; i < randStringLen-1; i++){
		randString[i] = inputChar();
	}
	
	randString[randStringLen-1] = '\0';
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
