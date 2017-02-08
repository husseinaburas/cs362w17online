#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


//randomly generate characters between " " (ASCII 32) and "~" (ASCII 126)
char inputChar()
{
    // TODO: rewrite this function
	int min=32;
	int max=126;
	
	char randChar = (rand() % (max-min+1)) + min;
    return randChar;
    
   
}

//randomly generate characters between "a" (ASCII 97) and "z" (ASCII 122) into an array of strings with last char = "\0"

char *inputString()
{
    // TODO: rewrite this function
	int i;
	int min=97;
	int max=122;
	
	static char string[6];
    
    for (i = 0; i < 5; i++) {
		string[i] = (rand() % (max-min+1)) + min;
    }
    
	string[5] = '\0'; 
    return string;
	
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
