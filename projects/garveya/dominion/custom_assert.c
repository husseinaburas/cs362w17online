#include <stdio.h>
#include <stdlib.h>

//color output based on:
//http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//prints error message if test fails
//otherwise prints that test passed
//if shouldExit is not 0, will exit program after test fails
void custom_assert(int test, char *testName, double lineNumber, int shouldExit){
	if(!test){
		printf(ANSI_COLOR_RED "%s FAILED at line %.0f!\n" ANSI_COLOR_RESET, testName, lineNumber);
		if(shouldExit){
			exit(1);
		}
	}
	else{
		printf(ANSI_COLOR_GREEN "%s PASSED at line %.0f!\n" ANSI_COLOR_RESET, testName, lineNumber);
	}
}