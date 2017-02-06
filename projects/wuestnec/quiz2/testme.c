/*
Chris Wuestner
CS 362 Software Engineering II
Random Testing Quiz 2
2/5/2017
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	char randomChar = ' ' + (random() % 94);
    return randomChar;
}

char *inputString()
{
    // TODO: rewrite this function
	int i;
	// Randomly generate strings containing between 4 and 6 chars (plus '\0')
	int length = rand() % 3 + 4;
	char randLetter;
	// Randomly choose from available chars
	char letters[4] = {'e', 'r', 's', 't'};
	// Allocate space for 5 chars + null terminator
	char* randomString = malloc((length + 1) * sizeof(char));
	if(randomString != NULL){
		for(i = 0; i < length; i++){
			randLetter = letters[rand() % 4];
			randomString[i] = randLetter;
		}
		randomString[length] = '\0';
	}
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
