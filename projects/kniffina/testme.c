#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>


//returns a character that is one of the values present in the testme function. This is done by
//  creating an array with the values in ASCII format, and chosen by random (out of 13, 0-12) .
//  The value of the character is then returned. codes are from http://www.ascii-code.com/
char inputChar() {
	int returnChar[] = { 91, 93, 40, 41, 123, 125, 32, 97, 120, 114, 101, 115, 116 };

	int randomVariable = rand() % 13;
	return returnChar[randomVariable];
}

//inputString function creates memory for a string of length 6 and then puts in random characters
//  These characters are inputted from the inputChar function which returns 1 or 13 random characters.
char *inputString()
{
	int i;
	char *returnString = malloc(sizeof(char) * 6); //create memory for string
	
	//make sure malloc worked properly
	assert(returnString != NULL);
	
	//randomly assign a character to returnString
	for (i = 0; i < 5; i++) {
		//int randomNumber = randArray[(rand() % 5) + 1];			
		returnString[i] = inputChar();
	}
	//set last element to escape
	returnString[5] = '\0';

	return returnString;
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
			&& state == 9) {
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