#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	
	//set min and max ASCII characters to generate
	int numberMin = 32;
	int numberMax = 127;
	
	//generate number between 32-127 and store to char variable
	char randomChar;
	randomChar = numberMin+(rand() % (numberMax-numberMin + 1 ));
	
    return randomChar;
}

char *inputString()
{
    // TODO: rewrite this function
	
	//set min and max ASCII characters to generate
	int numberMin = 97;
	int numberMax = 122;
	
	//create global variable string of length 6 to hold 'reset' plus null terminator
	static char randomString[6];
	
	//store terminator in last array element
	randomString[5] = '\0';
	
	//generate char between 97-122 
	for(int counter = 0; counter <=4; counter = counter + 1)
	{
		//loop through elements of array to build string
		randomString[counter] = numberMin+(rand() % (numberMax-numberMin + 1 ));	
	}
	
	//return string
    return randomString;
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
