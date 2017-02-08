#ifndef DOM_TESTS_H
#define DOM_TESTS_H

#include <stdio.h>

void assertTrue(int assertion, char* text, int actual, int expected, int* testFlag){
	if (!assertion){
		printf("ERROR IN: %s\nActual: %d\nExpected: %d\n", text, actual, expected);
		*testFlag = 1;
	}
	else{
		printf("pass\n");
	}
}

void checkTest(int testFlag, int testNum){
	if (testFlag == 0){
		printf("ALL TESTS IN TEST %d PASSED\n", testNum);
	}
	else{
		printf("TESTS IN TEST %d NOT PASSED\n", testNum);
	}
}
#endif
