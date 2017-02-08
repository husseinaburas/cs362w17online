#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  int tempNum = (rand() % 34) + 97;  

  if(tempNum == (29+97))
    tempNum = 40;
  if(tempNum == (30+97))
    tempNum = 41;
  if(tempNum == (31+97))
    tempNum = 91;
  if(tempNum == (32+97))
    tempNum = 93;
  if(tempNum == (33+97))
    tempNum = 32;

  return tempNum;
}

char *inputString()
{
  char *tempS = malloc(7*sizeof(char));
  for(int i = 0; i < 5; ++i){
    tempS[i] = inputChar();
  }
  tempS[5] = '\0';
  return tempS;
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
      exit(200);
    }
    
    free(s);

    //if(c == ')'){
    //  printf("Found the right paren!\n");
    //  exit(201);
    //}

//    if(tcCount > 100000){
//      printf("exited due to count\n");
//      exit(202);
//    }
  }
}


int main(int argc, char *argv[])
{
  srand(time(NULL));
  testme();
  return 0;
}
