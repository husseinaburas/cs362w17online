/*Name: Nipun Bathini
  Assignment: 3
  
  unittest for isgameOver() function line390 in dominion
  */ 

#include "dominion.h"
#include "dominion_helpers.h"
#include "stdlib.h"
#include "stdio.h"
#include "rngs.h" 
#include <string.h>


int testisGameOver(){
	
	printf("\n --Unit Test 1-- \n");
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G;
	//int player = 0;
	//int bonus = 0;
    //int i, handCount;

    initializeGame(2, k, 1000, &G);
	
	//TEST 1 Check if game doesnt end with the supply count at 8
	
	printf("Testing: isGameOver() when G.supplyCount[province] is %d", G.supplyCount[province]);
	if(isGameOver(&G) == 0){
		printf(". Test PASS\n");
	}else{
		printf(". Test FAIL\n");
	}
	
	//TEST 2 check if game ends when setting 4 of them to zero
	G.supplyCount[province]=8; //set to 8 before setting individuals to 0
	G.supplyCount[1]=0, G.supplyCount[2]=0, G.supplyCount[3]=0, G.supplyCount[4]=0;
	
	printf("Testing: isGameOver() when G.supplyCount[province] is %d and setting 4 of them to 0", G.supplyCount[province]);
	if(isGameOver(&G) == 1){
		printf(". Test PASS\n");
	}else{
		printf(". Test FAIL\n");
	}
	
	// TEST 3 check if game ends with supply count at 0
	G.supplyCount[province]=0; //set to 0 to test if game actually ends
	printf("TEsting: isGameOver() when G.supplyCount is 0. ");
	if(isGameOver(&G) == 1){
		printf(" Test PASS\n");
	}else{
		printf(" Test FAIL\n");
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