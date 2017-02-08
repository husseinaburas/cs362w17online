/*Name: Nipun Bathini
  Assignment: 3
  
  unittest for scoreFor() function
  */ 

#include "dominion.h"
#include "dominion_helpers.h"
#include "stdlib.h"
#include "stdio.h"
#include "rngs.h" 
#include <string.h>


int testscoreFor(){
	printf("\n --Unit Test 3-- \n");
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int i;
	
	//TEST 1 Player score be 3
	
	initializeGame(2, k, 1000, &G);
	printf("Testing: scorefor()when score for player 1 should equal 3. ");
	if(scoreFor(0,&G) == 3){
		printf("Actual score %d. Test PASS\n",scoreFor(0,&G));
	}else{
		printf("Actual score %d. Test FAIL\n",scoreFor(0,&G));
	}
	
	
	// TEST 2 add 1 province card so score should be 9
	for (i = 0; i < G.handCount[0]; i++){
		if(G.hand[0][i] != 1){
			 G.hand[0][i] = province; //adding the province
			 break;
        }
	 }
	 
	printf("Testing: scorefor()score for p1 should equal 9, after adding province. ");
	if(scoreFor(0,&G) == 9){
		printf("Actual score %d. Test PASS\n",scoreFor(0,&G));
	}else{
		printf("Actual score %d. Test FAIL\n",scoreFor(0,&G));
	}
	 
	 

	return 0;
}

int main(){
	if(testscoreFor() == 0){
		return 0;
	}else{
		printf("Error: testscoreFor");
		exit(1);
	}
}