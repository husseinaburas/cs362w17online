#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char randChar();
int getRandIntLowHigh (int low, int high);

// *********************
// getRandIntLowHigh - selects an int between low and high inclusive
// input: low and high int
// return: integer
// *********************
int getRandIntLowHigh (int low, int high) {
	int randInt = (rand()%(high-low))+low+1;
	return randInt;
}

// *********************
// randChar - selects a random 8 bit char
// input: none
// return: char ranging from 0000 0000 to 1111 1111
// Note this is the same as inputChar() but decided to implement this separately
// this allows us easy options to test different algorithms later and not couple code.
// *********************
char randChar () {
	// char values can be 8 bits, range from 0 to 255
	int lowRange = 0;
	int highRange = 255;
	char randChar = getRandIntLowHigh (lowRange, highRange);
	return randChar;
}

// *********************
// inputChar - selects a random 8 bit char
// input: none
// return: char ranging from 0000 0000 to 1111 1111
// Note this is the same as randChar() but decided to implement this separately
// this allows us easy options to test different algorithms later and not couple code.
// *********************
char inputChar()
{
	// char values can be 8 bits, range from 0 to 255
	int lowRange = 0;
	int highRange = 255;
	char randChar = getRandIntLowHigh (lowRange, highRange);
	return randChar;
}

// *********************
// inputString - creates random string
// input: none
// return: c string with a set # of characters, randomly selected based on testing scenarios
// *********************
char *inputString()
{
	int maxCharsInString = 40; // must be greater than 5
	// allocate memory for string + 1 for null character at end of string
	char *randString = (char*) malloc(maxCharsInString * sizeof(char) + 1);

	// get a random # between 1 and 100 to distribute random test cases
	int randCaseDistribution = getRandIntLowHigh (1, 100);
	int testCase = 0; // default test case is zero

	if (randCaseDistribution == 100) {
		testCase = 6;  // allocate 1% of trials to test case 6
	} else if ((randCaseDistribution >= 1) && (randCaseDistribution <= 16)){
		testCase = 5; // allocate 16% of trials to test case 5
	} else if ((randCaseDistribution >=17) && (randCaseDistribution <= 32)){
		testCase = 4; // allocate 16% of trials to test case 4
	} else if ((randCaseDistribution >=33) && (randCaseDistribution <= 48)){
		testCase = 3; // allocate 16% of trials to test case 3
	} else if ((randCaseDistribution >=49) && (randCaseDistribution <= 64)){
		testCase = 2; // allocate 16% of trials to test case 2
	} else if ((randCaseDistribution >=65) && (randCaseDistribution <= 80)){
		testCase = 1; // allocate 16% of trials to test case 1
	} else if ((randCaseDistribution >=81) && (randCaseDistribution <= 99)){
		testCase = 0; // allocate the remaining % of trials to test case 0
	}
	//printf ("testCase = %d\n", testCase);

	switch (testCase) {
		case 0 :
			// Case 0: fill all positions with random characters
			for (int i = 0; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 1:
			// Case 1: fill first position with 'r' and the rest with random characters
			randString[0] = 'r';
			for (int i = 1; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 2:
			// Case 2: fill first 2 with 'r', 'e' and the rest with random characters
			randString[0] = 'r';
			randString[1] = 'e';
			for (int i = 2; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 3:
			// Case 3: fill first 3 with 'r', 'e', 's' and the rest with random characters
			randString[0] = 'r';
			randString[1] = 'e';
			randString[2] = 's';
			for (int i = 3; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 4:
			// Case 4: fill first 4 with 'r', 'e', 's', 'e' and the rest with random characters
			randString[0] = 'r';
			randString[1] = 'e';
			randString[2] = 's';
			randString[3] = 'e';
			for (int i = 4; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 5:
			// Case 5: fill first 5 with 'r', 'e', 's', 'e', 't' and the rest with random characters
			randString[0] = 'r';
			randString[1] = 'e';
			randString[2] = 's';
			randString[3] = 'e';
			randString[4] = 't';
			for (int i = 5; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 6:
			// Case 6: fill first 6 with 'r', 'e', 's', 'e', 't', '\0' and the rest random characters
			randString[0] = 'r';
			randString[1] = 'e';
			randString[2] = 's';
			randString[3] = 'e';
			randString[4] = 't';
			randString[5] = '\0';
			for (int i = 6; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
	}
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
		  printf("error [DONE]");
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
