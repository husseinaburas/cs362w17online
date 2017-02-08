#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

//unit test for the endturn() function

//Assert function, 3rd argument is operator, use: 0 for =, 1 for <, 2 for >
int assertTrue(int arg1, int arg2, int op){
	if(op == 0){
		if(arg1 == arg2){
			printf(">>>test successful\n\n");			
		}else{printf(">>>test failed\n\n");
			return -1;}
	}else if(op == 1){
		if(arg1 < arg2){
			printf(">>>test successful\n\n");
		}else{printf(">>>test failed\n\n");
			return -1;}
	}else if(op == 2){
		if(arg1 > arg2){
			printf(">>>test successful\n\n");
		}else{printf(">>>test failed\n\n");
			return -1;}
	}
	return 0;
}//end assertTrue

int main(){
	struct 	gameState pretest;
	struct 	gameState state;

	char 	*testCard;	
	int 	numPlayers = 2;
	int 	seed = 5;
	int 	curPlayer;
	int 	prevPlayer;	
	int 	results;
	int 	i, n;
	int 	coinCnt;
	

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};
	
	n=0;
	testCard = (char*)malloc(15 * sizeof(char));
	cardNumToName(k[n], testCard);

	initializeGame(numPlayers, k, seed, &state);
	prevPlayer = state.whoseTurn;
			
	//Save game state before testing
	memcpy(&pretest, &state, sizeof(struct gameState));

	printf("********************************Testing endTurn() function****************************\n");

	results = endTurn(&state);
	curPlayer = state.whoseTurn;

	printf("Check return value \n");
	printf("expected return value = 0, acutal return value = %d\n", results);
	assertTrue(0, results, 0);

	printf("Checking whose turn\n");
	printf("Whose turn before call: player %d, whose turn after call: player %d\n", \
		pretest.whoseTurn, state.whoseTurn);
	assertTrue(pretest.whoseTurn + 1, state.whoseTurn, 0);

	printf("Ensure player before end turn had stats adjusted correctly\n");
	printf("handCount should be 0\nhandCount before test: %d, handCount after: %d\n", \
		pretest.handCount[prevPlayer], state.handCount[prevPlayer]);
	assertTrue(state.handCount[prevPlayer], 0, 0);

	printf("Check that discard count increased by previous hand size\n");
	printf("previous handcount: %d\ndiscardCount before test: %d, discardCount after: %d\n", \
		pretest.handCount[prevPlayer], pretest.discardCount[prevPlayer], state.discardCount[prevPlayer]);
	assertTrue(pretest.discardCount[prevPlayer] + pretest.handCount[prevPlayer], state.discardCount[prevPlayer], 0);

	printf("Check all shared state traits are reset for new turn\n");
	printf("expected outpostPlayed: 0, outpostPlayed: %d\n", state.outpostPlayed);
	assertTrue(0, state.outpostPlayed, 0);

	printf("expected phase: 0, phase: %d\n", state.phase);
	assertTrue(0, state.phase, 0);

	printf("expected numActions: 1, numActions %d\n", state.numActions);
	assertTrue(1, state.numActions, 0);

	printf("expected numBuys: 1, numBuys %d\n", state.numBuys);
	assertTrue(1, state.numBuys, 0);

	printf("expcted playedCardCount: 0, PlayedCardCount %d\n", state.playedCardCount);
	assertTrue(0, state.playedCardCount, 0);

	printf("check new player card piles\n");
	printf("Should've drawn 5 cards, handCount before test: %d, handCount after: %d\n", \
	pretest.handCount[curPlayer], state.handCount[curPlayer]);
	assertTrue(state.handCount[curPlayer], pretest.handCount[curPlayer] + 5, 0);

	printf("deckCount should be 5 less\ndeckCount before test: %d, deckCount after: %d\n", \
	pretest.deckCount[curPlayer], state.deckCount[curPlayer]);
	assertTrue(pretest.deckCount[curPlayer] - state.handCount[curPlayer], state.deckCount[curPlayer] , 0);

	//check coins for new player
	printf("Check that coins match actual coins in hand\n");
	coinCnt = 0;
	for (i = 0; i < state.handCount[curPlayer]; i++)
    {
    	if (state.hand[curPlayer][i] == copper){
	  	coinCnt += 1;
		}
      	else if (state.hand[curPlayer][i] == silver){
	  	coinCnt += 2;
		}
      	else if (state.hand[curPlayer][i] == gold){
	  	coinCnt += 3;
		}	
    }	
    printf("coins count in hand: %d, state.coins: %d\n",coinCnt, state.coins);
    assertTrue(coinCnt, state.coins, 0);

    printf("check that player changes correctly when at max player\n");

    memcpy(&pretest, &state, sizeof(struct gameState));
   	results = endTurn(&state);
   	printf("Player before call: %d, player after call:%d\n",pretest.whoseTurn, state.whoseTurn);
   	assertTrue(pretest.whoseTurn -1,state.whoseTurn,0);



	printf("********************************endTurn() Testing complete****************************\n");



	return 0;
}