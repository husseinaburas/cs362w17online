#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char inputChar(int st)
{
	int toCast;

	if(st == 9){
		//lowercase only, ASCII 97(dec) to 122(dec)
		toCast = (rand() % 26) + 97;
		if(toCast > 122){
    		printf("Number out of range, High\n");
    		exit (1);
    	}
    	if(toCast < 97){
    		printf("Number out of range, Low\n");
    		exit (1);
    	}	
	}
	else{
		//all chars from ASCII 32(dec) to 126(dec)
		toCast = (rand() % 95) + 32;
    	if(toCast > 126){
    		printf("Number out of range, High\n");
    		exit (1);
    	}
    	if(toCast < 32){
    		printf("Number out of range, Low\n");
    		exit (1);
    	}
	}

    
    return (char) toCast;
}

char *inputString(int st)
{
	int i;
	int buildLength;
	char* word;

	if(st == 9){
		//if state is 9 then only build 5 char strings
		buildLength = 5;
	}
	else{
		//length of string to build, 1 to 10 charachters
    	buildLength = (rand() % 11) + 1;	
	}
	word = malloc(buildLength + 1);

	for(i=0; i<buildLength; i=i+1){
		word[i]=inputChar(st);
	} 
	word[buildLength]='\0';

    return word;
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
    c = inputChar(state);
    s = inputString(state);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
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
      free(s);
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
