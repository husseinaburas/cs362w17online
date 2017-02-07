#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// rand() % (max_number + 1 - minimum_number) + minimum_number

char inputChar() {
  char availChars[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
	char randomChar;
	int randomInt = 0;
	//  Generate random integer from 0-8
	randomInt = rand() % (8 + 1 - 0) + 0;
	randomChar = availChars[randomInt];
    return randomChar;
}

char *inputString() {
	//  Generate a random lowercase letter using the ASCII integer
	//  ASCII 97 to 122 = a to z
	int randomInt = 0;
	int stringLen = 5;
	char *randString = malloc((stringLen + 1)*sizeof(char));
	for (int i = 0; i < stringLen; i++) {

		randomInt = rand() % (122 + 1 - 97) + 97;
		randString[i] = randomInt;
	}
	// Append the /0 to the end of the randString[5]
	randString[stringLen] = '\0';

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
