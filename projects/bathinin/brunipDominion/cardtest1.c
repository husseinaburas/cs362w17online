/* Name: Nipun Bathini
   Assignment: 3
   
   cardtest1.c testSmithy
   NOTE: I added a bug in smithy for Assignment2
   */
   
#include "dominion.h"
#include "dominion_helpers.h"
#include "stdlib.h"
#include "stdio.h"
#include "rngs.h" 
#include <string.h>
#include <assert.h>
#define TESTCARD "smithy"



int main(){
	printf("\n --Card Test 1 (smithy)-- \n");
	struct gameState G, Gtwo;
	int handpos = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int shuffledCards = 0;
	int newCards = 3;
	int discards = 1;
	int curPlayer = 0;
	int nextPlayer = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	
	
	initializeGame(2, k, 1000, &G); //use rand for seed
	
	
	//TEST 1 p1 handCount 
	memcpy(&Gtwo, &G, sizeof(struct gameState));
	cardEffect(smithy,choice1,choice2,choice3, &Gtwo, handpos,&bonus);
	printf("Testing smithy: P1 handcount should be %d, actual ",G.handCount[curPlayer] + newCards);
	newCards = 3; 
	
	if (Gtwo.handCount[curPlayer] == G.handCount[curPlayer] + newCards){
		printf("%d, test PASS\n",Gtwo.handCount[curPlayer]);
	}else{
		printf("%d, test FAIL\n",Gtwo.handCount[curPlayer]);
	}
	//T2
	printf("Testing smithy: P1 deck should be %d, actual ", G.deckCount[curPlayer] - newCards + shuffledCards);
	if (Gtwo.deckCount[curPlayer] == G.deckCount[curPlayer] - newCards + shuffledCards){
		printf("%d, test PASS\n",Gtwo.deckCount[curPlayer]);
	}else{
		printf("%d, test FAIL\n",Gtwo.deckCount[curPlayer]);
	}
	//T3
	printf("Testing smithy: test that handcount doesnt go to next player ");
	 if (Gtwo.handCount[nextPlayer] == G.handCount[nextPlayer]){
		 printf(". test PASS\n");
	 }else{
		  printf(". test FAIL\n");
	 }
	 //T4
	 printf("Testing smithy: test that deckCount doesnt go to next player ");
	 if (Gtwo.deckCount[nextPlayer] == G.deckCount[nextPlayer]){
		 printf(". test PASS\n");
	 }else{
		  printf(". test FAIL\n");
	 }
	//T5
	printf("Testing smithy: Estate count should be same. ");
	if (Gtwo.supplyCount[estate] == G.supplyCount[estate]){
			printf(". test PASS\n" );
	}
	else{
		printf(". test FAIL\n");
	}
	//T6
	printf("Testing smithy: province count should be same. ");
	if (Gtwo.supplyCount[province] == G.supplyCount[province]){
			printf(". test PASS\n" );
	}
	else{
		printf(". test FAIL\n");
	}
	//T7
	printf("Testing smithy: Duchy count should be same. ");
	if (Gtwo.supplyCount[duchy] == G.supplyCount[duchy]){
			printf(". test PASS\n" );
	}
	else{
		printf(". test FAIL\n");
	}
	//T8
	printf("Testing smithy: adventurer count should be same. ");
	if (Gtwo.supplyCount[adventurer] == G.supplyCount[adventurer]){
			printf(". test PASS\n" );
	}
	else{
		printf(". test FAIL\n");
	}

	return 0;
	
}