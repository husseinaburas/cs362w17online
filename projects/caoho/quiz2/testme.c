/*
 * testme.c
 *
 *  Created on: Feb 5, 2017
 *  Author: caoho
 *	course: CS 362 Software Engineering II
 *	Random Testing Quiz 2
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar() {
	char spaceCharCode = 32; // min space
	char maxCode = 126;//max ~
	 return (char)((rand() % (maxCode - spaceCharCode)) + spaceCharCode);
}

char *inputString() {
	int reset = 0;
	int randomStrLength = 6;
	char* strValue = malloc(sizeof(char) * randomStrLength);
	reset = rand() % 1000;
	if (reset == 1) {
		strValue = "reset";
	} else {
		int i;
		for (i = 0; i < randomStrLength; i++) {
			strValue[i] = inputChar();
		}
	}
	return strValue;
}

void testme() {
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;
	while (1) {
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s,
				state);

		if (c == '[' && state == 0)
			state = 1;
		if (c == '(' && state == 1)
			state = 2;
		if (c == '{' && state == 2)
			state = 3;
		if (c == ' ' && state == 3)
			state = 4;
		if (c == 'a' && state == 4)
			state = 5;
		if (c == 'x' && state == 5)
			state = 6;
		if (c == '}' && state == 6)
			state = 7;
		if (c == ')' && state == 7)
			state = 8;
		if (c == ']' && state == 8)
			state = 9;
		if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e'
				&& s[4] == 't' && s[5] == '\0' && state == 9) {
			printf("error ");
			free(s);
			exit(200);
		}
		free(s);
	}
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	testme();
	return 0;
}
