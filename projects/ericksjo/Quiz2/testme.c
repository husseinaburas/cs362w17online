#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	//Returns a random ASCII char from 32-126, or space to ~
	return rand() % (127 - 32) + 32;
}

char *inputString()
{
	//Creates a random number from 1-100k
	int randNum = rand() % 100001;
	//Creating a string with "reset " to use if randNum == 10, this speeds up the program a bit
	char resetStr[6] = "reset ";
	//String with the 6 characters, space needed for "reset "
	static char randStr[6];

	//If randNum ended up being 10 (1/100k chance), then just set randStr == "reset "
	//This saves some time and still lets thr program iterate through/test a reasonable number of random strings
	if (randNum == 10)
	{
		for (int j = 0; j < 5; j++)
		{
			randStr[j] = resetStr[j];
		}
	}
	//If randNum isn't 10, generate a random string
	else
	{
		for (int i = 0; i < 5; i++)
		{
			//randStr will be generated with characters from A-z
			randStr[i] = ((rand() % (123 - 41)) + 41);
		}
		randStr[5] = '\0';
	}

	return randStr;
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