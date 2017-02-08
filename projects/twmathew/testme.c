#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/*
Thomas Mathew
CS 362
Quiz 2

Description: Implement a random tester for the function testme() in testme.c that is capable of printing the error message. 
You should implement inputChar() and inputString() to produce random values. Write up the development of your random tester and how it finds the error message as randomstring.c. 
Submit testme.c and randomstring.c under your onid directory in class github. (under your onid directory and not under dominion directory). 
The randomstring.c is a text file that outlines how you developed your solution and how it works!
*/

char inputChar()
{
    // TODO: rewrite this function

    char newChar;

    //Set newChar equal to a number between 0 and 127. This will automatically give it the character's value at the corresponding ASCII value
    //This range covers all the "trigger" characters for testme(), and many others as well. 
    newChar = (rand() % 127);

    return newChar;

}

char *inputString()
{
    // TODO: rewrite this function

	//This function needs to create a random string.
	//In order for testme() to be triggered, the string must precisely be: "reset"

	char strChar;
	char myString[10];

	int i = 0;

	//We will force the string to be precisely length = 5. 
	//If the length of the string was random, we would run a huge, almost infinite number of tests before "reset" occurred.
	for (i; i < 5; i++)
	{
		strChar = (97 + (rand() % 25));
		myString[i] = strChar;
	}

	//These are the values needed to arrive at "reset". 
	//You can comment or un-comment any or all of these lines to force some or all of these variables, in order to change the number of iterations needed
	//Here I force the first two characters to be "re". This reduces the number of iterations needed from > 300,000 to  < 20,000.
	myString[0] = 114;		//r
	myString[1] = 101;		//e
	//myString[2] = 115;	//s
	//myString[3] = 101;	//e
	//myString[4] = 116;	//t

	//Force the 6th character to be NULL
	myString[5] = NULL;

	return myString;

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
