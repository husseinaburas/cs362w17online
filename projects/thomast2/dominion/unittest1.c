//unittest1.c
//isGameOver

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
	
	struct gameState state;	
	int j;

	int k[10] = {1,2,3,4,5,6,7,8,9,10};
	//test for condition 1
	initializeGame(2,k,2,&state);
	state.supplyCount[province] = 0;
	
	j = isGameOver(&state);
	if(j==1){
		printf("isGameOver: Test 1 Passed\n");
	}
	else{
		printf("isGameOver: Test 1 Failed\n");
	}
	//assert(j == 1);
	//end test for condition 1
	//test for condition 2
	state.supplyCount[1] = 0;
	state.supplyCount[4] = 0;
	state.supplyCount[7] = 0;
	
	j = isGameOver(&state);
	if(j==1){
		printf("isGameOver: Test 2 Passed\n");
	}
	else{
		printf("isGameOver: Test 2 Failed\n");
	}
	
	
	//assert(j == 1);


	
}