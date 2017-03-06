#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <assert.h>

char inputChar()
{
    // TODO: rewrite this function
	char randNum = (rand()%95)+32; //get random chars between 32 and 126
	
	//confirm random number matches all possible keyboar characters
    assert(randNum > 31 && randNum < 127);	
	
	return randNum;
}

char *inputString()
{
    // TODO: rewrite this function
	int a;
	
	char arr[5] = {'r', 'e', 's', 't', '\0'}; //these are the letters the tester function will look for
	
	//allocate memory
	char *randomstring = (char*) malloc(sizeof(char)* 6);
	
	//loop through array of randomchars and store the contents in randomstring
	for(a=0; a<6; a++){
		randomstring[a] = arr[rand()%5];
	}
	
	
    return randomstring;
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