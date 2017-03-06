/* Name: Nipun Bathini
   Assignment: 3
   
   cardtest4.c adventurer
   */
   
#include "dominion.h"
#include "dominion_helpers.h"
#include "stdlib.h"
#include "stdio.h"
#include "rngs.h" 
#include <string.h>
#include <assert.h>
#define TESTCARD "adventurer"

int main(){
	printf("\n --Card Test 4 (adventurer)-- \n");
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int i;
	int handpos = 0;
	int discard = 1;
	int choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
	initializeGame(2,k,1000,&G);
	
	for(i=0; i<5; i++){
        G.deck[0][i] = k[i+1]; //fill 5 cards with 5 cards from k
    }

	G.deck[0][5] = copper; //set copper in deck
	G.deck[0][6] = silver; //set silver in deck
	G.deckCount[0]=7; // set to 7 cards in the deck
	G.hand[0][0] = adventurer; //sets adventurer to card in hand
	G.handCount[0] = 1;//set to 1 card in hand
	
	cardEffect(adventurer,choice1,choice2,choice3, &G, handpos, bonus);
	
	//TEST 1
	printf("testing adventurer: handcount should be 2, actual %d ",G.handCount[0] - discard);
	if(G.handCount[0] - discard == 2){
		printf(". test PASS\n");
	}else{
		printf(". test FAIL\n");
	}
	
	//TEST 2
	printf("testing adventurer: copper should be in hand");
	if(G.hand[0][1] == copper || G.hand[0][2] == copper){
		printf(", test PASS\n");
	}else{
		printf(", test FAIL\n");
	}
	
	//printf("ERROR CHECK: %d and %d and %d", G.hand[0][0],G.hand[0][1], G.hand[0][2]);
	
	//TEST 3
	printf("testing adventurer: silver should be in hand");
	if(G.hand[0][1] == silver || G.hand[0][2] == silver){
		printf(", test PASS\n");
	}else{
		printf(", test FAIL\n");
	}
	
	return 0;
}