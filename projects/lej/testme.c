#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/* James Le
   CS 362 - Quiz 2
   1/31/2017
   To run on flip:
   gcc testme.c -o test -g -Wall
   ./test
*/

// generate random characters from ASCII 
// http://en.cppreference.com/w/cpp/language/ascii
char inputChar()
{
    // TODO: rewrite this function
    int min = 32;
    int max = 126;

    // generate random char from 32(space) ASCII decimal values to 126(~)
    char randCh = rand() % (max-min) + min;

    return randCh;
}

// create string from random chars 
char *inputString()
{
    // TODO: rewrite this function
	char *randStr = malloc(6 * sizeof(char));
	int i = 0;

	char randCh[] = {'r', 'e', 's', 't', '\0'};

	// loop 6 times to generate a string from random chars 
	// 'r', 'e', 's', 't', with terminating null
	for (i = 0; i < 6; i++){
		randStr[i] = randCh[rand() % 5];
	}

    return randStr;
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
      free(s); // free up memory
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