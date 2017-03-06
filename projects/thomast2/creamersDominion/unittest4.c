//unittest4.c
//supplyCount

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

int main(){
	
	int x;
	int y;
	
	struct gameState state;
	
	state.supplyCount[smithy] = 10;
	x = supplyCount(smithy, &state);
	
	state.supplyCount[smithy] = 3;
	y = supplyCount(smithy, &state);
	
	if ((x-y) == 7)
		printf("supplyCount: Test passed\n");
	else
		printf("supplyCount: Test failed\n");
	
	return 0;
}