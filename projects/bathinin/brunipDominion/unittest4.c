/*Name: Nipun Bathini
  Assignment: 3
  
  unittest for gainCard() function
  */ 

#include "dominion.h"
#include "dominion_helpers.h"
#include "stdlib.h"
#include "stdio.h"
#include "rngs.h" 
#include <string.h>

int testgainCard(){
	printf("\n --Unit Test 4-- \n");
	//int initialCount;
	int icount;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G;
	initializeGame(2, k, 1000, &G);
	G.whoseTurn = 0;
	G.coins = 2;
	G.numActions = 10;
	
	// TEST 1 & 2 testing no increase and increase in hand
	G.supplyCount[feast] = 0; //set supply count of feast cards to 0   
    gainCard(feast, &G, 2, 1); //attempt to gain feast card
	if(G.handCount[1] == 0){ //no feast card should 
		printf("Should be no change in hand (zero), actual %d. Test PASS\n",G.handCount[1]);
	}
	else{
		printf("Should be no change in hand (zero), actual %d. Test FAIL\n",G.handCount[1]);
	}
	
	G.supplyCount[feast] = 1; //set supply count of feast cards to 1 
    gainCard(feast, &G, 2, 1); //attempt to gain feast card
	if(G.handCount[1] == 1){ // 1 feast card should be there
		printf("Should be one card in hand, actual %d. Test PASS\n",G.handCount[1]);
	}
	else{
		printf("Should be one card in hand , actual %d. Test FAIL\n",G.handCount[1]);
	}
	
	// TEST 3 test the change of deckcount
	icount = G.deckCount[1];
	G.supplyCount[feast] = 1; //number of feast in supply
	gainCard(feast,&G,1,1); //add feast
	if(G.deckCount[1] == icount + 1){
		printf("deckcount should equal initial deckcount + 1, actual deckcount %d actual icount %d. Test PASS\n",G.deckCount[1], icount+1);
	}else{
		printf("deckcount should equal initial deckcount + 1, actual deckcount %d actual icount %d. Test FAIL\n",G.deckCount[1], icount+1);
	}
		


    //TEST 4 Make sure coins,actions,and turn didnt change
	
	if(G.coins != 2){
		printf("Coins isnt 2 after Test FAIL");
	}
	
	if(G.numActions != 10){
		printf("Num of actions isnt 10 test FAIL");
	}
	if(G.whoseTurn != 0){
		printf("Whose turn isnt player 1 test FAIL");
	}
	return 0;
}

int main(){
	if(testgainCard() == 0){
		return 0;
	}else{
		printf("Error: testgainCard");
		exit(1);
	}
}