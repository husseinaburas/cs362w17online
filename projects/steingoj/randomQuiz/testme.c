#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include<stdio.h>

char inputChar()
{
	int randomnumber;
	char *string = "aerstx[]{}() ";

	randomnumber = rand() % strlen(string);

    return string[randomnumber];
}

char *inputString()
{
	//Max length for a string in the test is 5
	int i = 0;
	int length = 5;
	char *s = malloc(sizeof(char) * (length + 1));
	int contained = 0;
	char c = "";

	for (i; i < length; i++) {
		//Check if the char is already contained in the string
		contained = 0;

		//For getting unique chars
		while (contained == 0) {
			c = inputChar();
			if (c == 'r' || c == 'e' || c == 's' || c == 't') {
				contained = 1;
			}
		}
		s[i] = c;
	}
	//Add the final char
	s[length] = '\0';

	printf("%s\n", s);
	return s;
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
	inputString();
    testme();
	getchar();
    return 0;
}
