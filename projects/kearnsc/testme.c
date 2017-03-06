/********************************************************************************************
*  Chris Kearns, kearnsc@oregonstate.edu, CS325-400-W17, Quiz 2.
*  Implements a random tester for the function testme() in testme.c that is capable
*  of printing the error message.  Functions inputChar() and inputString() are implemented
*  to produce random values. The development steps of the random testing methods used and how
*  they force the error message to print is contained in randomstring.c. Program testme.c
*  and randomstring.c are contained within directory:
*  https://github.com/aburasali/cs362w17online/tree/master/projects/kearnsc.
*  Compile: gcc testme.c -o testme -g -Wall
********************************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/* Returns a random char converted from the decimal representation of
*  "[" == 91, "]" == 93, "(" == 40, ")" == 41, "{" == 123,
*  "}" == 125,	' ' == 32, "a" == 97, "x" == 120,
*  "r" == 114, "e" == 101, "s" == 115, "t" == 116
*  from ASCII Table at http://www.asciitable.com/	*/
char inputChar() {
	int result[] = { 91, 93, 40, 41, 123, 125, 32, 97, 120, 114, 101, 115, 116 };
	return result[rand() % 13];
}

/* Returns a random c-string of length 5 + last char == '\0'. */
char *inputString() {
	int i;
	char *string = malloc(sizeof(char) * 6);
	if (string == NULL) {
		printf("Call to malloc failed!\n");
		exit(1);
	}
	for (i = 0; i < 5; i++) {
		string[i] = inputChar();
	}
	string[5] = '\0'; // Last char defaults to '\0'.
	return string;
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
			&& state == 9) {
				printf("error ");
				free(s);	// Memory management.
				exit(200);
		}
		free(s);	// Memory management.
	}
}


int main(int argc, char *argv[]) {
	srand(time(NULL));
	testme();
	return 0;
}