#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void assertTrue(int a, char* assertion){
	if (a){
		printf("TEST PASSED");
	}
	else{
		printf("TEST FAILED");
	}
}