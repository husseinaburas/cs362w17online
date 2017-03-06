//Name:				unittest3.c
//Assignment:		Assignment 3
//Author:				Benjamin Ford
//Date:					2/5/2017
//Description:		Unit test for gainCard function

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTFUN "Gain Card"

int addToHand(struct gameState *state, int player){
	int startHandCnt = state->handCount[player];
	int afterHandCnt = -1;
	
	//add copper to hand
	gainCard(copper,state,2,player);
	
	afterHandCnt = state->handCount[player];
	
	if(afterHandCnt == (startHandCnt + 1)){
		return 1;
	}
	
	return 0;
}

int addToDeck(struct gameState *state, int player){
	int startDeckCnt = state->deckCount[player];
	int afterDeckCnt = -1;
	
	//add copper to deck
	gainCard(copper,state,1,player);
	
	afterDeckCnt = state->deckCount[player];
	
	if(afterDeckCnt == (startDeckCnt + 1)){
		return 1;
	}
	
	return 0;
}

int addToDiscard(struct gameState *state, int player){
	int startDiscardCnt = state->discardCount[player];
	int afterDiscardCnt = -1;
	
	//add copper to deck
	gainCard(copper,state,0,player);
	
	afterDiscardCnt = state->discardCount[player];
	
	if(afterDiscardCnt == (startDiscardCnt + 1)){
		return 1;
	}
	
	return 0;
}

int checkSupplyCnt(struct gameState *state, int player){
	//get the supply count of copper
	int startSupplyCnt = state->supplyCount[copper];
	int afterSupplyCnt = -1;
	
	//add copper to deck
	gainCard(copper,state,1,player);
	
	afterSupplyCnt = state->supplyCount[copper];
	
	if(afterSupplyCnt == (startSupplyCnt - 1)){
		return 1;
	}
	
	return 0;
}


int main(){
	struct gameState game, testGame;
	const int kCards[] = {adventurer, smithy, village, baron, great_hall, minion, steward, council_room, mine, sea_hag};
	const int players = 2;
	const int gameSeed = 5;
	int testsPassed = 1;
	
	initializeGame(players,kCards,gameSeed,&game);
	
	//Save the game state for test
	memcpy(&testGame, &game, sizeof(struct gameState));
	
	printf("----------------- Testing Fucntion: %s ----------------\n", TESTFUN);
	
	//add a copper to hand
	if(addToHand(&game,1)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	//add a copper to deck
	if(addToDeck(&game,1)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	//add a copper to discard
	if(addToDiscard(&game,1)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	//check the supply count for copper went down after 
	if(checkSupplyCnt(&game,1)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	
	
	if(testsPassed){
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUN);
	}
	else{
		printf("A Test Failed\n");
	}
	
	return 0;
}