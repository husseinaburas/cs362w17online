#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	char charTargets[9] = // the target test case characters for the input character
	{
		'[','(','{',' ','a','x','}',')',']' // only the target characters
	};

	int choiceC = rand() % 9; // select a sudo random char from the char array

	return charTargets[choiceC];  // return the sudo random char
}

char *inputString()
{
	char stringTargets[5] = // the target test case characters for the string array
	{
		'r', 'e', 's', 't', '\0'  // only the target characters
	};

	int i = 0;
	int choiceS = 0;

	int length = (sizeof(char) * 5 ) + 1;  // set string length to 5 characters

	char *stringArr = malloc(length);  // allocate memory for array

	for (i = 0; i < 5; i++)  // iterate until string has 5x characters
	{
		choiceS = rand() % 5;  // select a sudo random int

		stringArr[i] = stringTargets[choiceS];  // initialize string char to choiceS
	}

	return stringArr;  // return the string
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
