#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int randChar = rand() %127 + 31;  //Random range from 31-126 (outside of boundaries of trigger characters by 1)
    return (char)randChar; 
}

char *inputString()
{
	int changeOdds = 10; //Here you can change the odds.  The closer to 0, the more likley the random character will be a r/e/s/t
    char* randString = (char *)malloc(6*sizeof(char));
    for(int i=0; i < 5; i++)
    {
    	int randCharPath = rand() % (changeOdds+5);

    	if(randCharPath==0) randString[i] = 'r';
    	if(randCharPath==1) randString[i] = 'e';
    	if(randCharPath==2) randString[i] = 's';
    	if(randCharPath==3) randString[i] = 't';
    	if(randCharPath > 3) randString[i] = (char)rand()% 123 + 97;

    }
	randString[5] = '\0';
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