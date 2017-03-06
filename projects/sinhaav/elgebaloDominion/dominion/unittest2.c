#include "dominion.h"
#include "dominion_helpers.h"
#include "stdlib.h"
#include "stdio.h"
#include "rngs.h" 
#include <string.h>


int testisGameOver(){
	
	printf("\n Test 1 \n");
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G;
	

    initializeGame(2, k, 1000, &G);
	
	/*Check if game ends with supply count at 8*/
	
	printf("Testing: isGameOver() when G.supplyCount[province] is %d", G.supplyCount[province]);
	if(isGameOver(&G) == 0){
		printf(". Test PASS\n");
	}else{
		printf(". Test FAIL\n");
	}
	
	/*check if game ends when setting 4 of them to zero*/
	G.supplyCount[province]=8; //have individuals=8 before having them =0
	G.supplyCount[1]=0, G.supplyCount[2]=0, G.supplyCount[3]=0, G.supplyCount[4]=0;
	
	printf("Test: isGameOver() when G.supplyCount[province] is %d and setting 4 of them to equal 0", G.supplyCount[province]);
	if(isGameOver(&G) == 1){
		printf(". Test Pass\n");
	}else{
		printf(". Test Fail\n");
	}
	
	//check if game ends with supply count =0
	G.supplyCount[province]=0; //=0 if game actually ends
	printf("Test: isGameOver() when G.supplyCount = 0. ");
	if(isGameOver(&G) == 1){
		printf(" Test Pass\n");
	}else{
		printf(" Test Fail\n");
	}
	
	return 0;
}

int main(){
	if(testisGameOver() == 0){
		return 0;
	}else{
		printf("Error: testisGameOver");
		exit(1);
	}
}