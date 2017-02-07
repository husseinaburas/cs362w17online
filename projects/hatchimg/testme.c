#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    char x;
	
	x = (rand() % 125) + 32;
    return x;
}

char *inputString()
{
	char *theString = (char*) malloc(sizeof(char) * 6);
	int randArray[6];
	randArray[0] = 0;
	randArray[1] = 114;
	randArray[2] = 101;
	randArray[3] = 115;
	randArray[4] = 116;
	randArray[5] = 0;
	
	//populate the string with random values from choices of r, e, s, t, and /0
	int i;
    for(i = 0; i < 6; i++){
		
		int randPick;
		randPick = randArray[(rand() % 5) + 1];
		theString[i] = randPick; 
		
	}
    return theString;
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
