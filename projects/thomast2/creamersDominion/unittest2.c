//unittest2.c
//getCost

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(){

	printf("There are 4 tests for this unit test.\n");
	
	if(getCost(0) == 0){
		printf("getCost: Test 1 Passed\n");
	}
	else{
		printf("getCost: Test 1 Failed\n");
	}

	if(getCost(adventurer) == 6){
		printf("getCost: Test 2 Passed\n");
	}
	else{
		printf("getCost: Test 2 Failed\n");
	}
	  
	if(getCost(smithy) == 4){
		printf("getCost: Test 3 Passed\n");
	}
	else{
		printf("getCost: Test 3 Failed\n");
	}
	  
	if(getCost(gold) == 6){
		printf("getCost: Test 4 Passed\n");
	}
	else{
		printf("getCost: Test 4 Failed\n");
	}
	  return 0;
}





