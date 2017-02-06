#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

//unit test for the buyCard() function

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
	int 	numPlayers = 2;
	int 	seed = 5;
	struct 	gameState pretest;
	char 	*testCard;
	char 	*curCard;
	int 	curPlayer;
	int 	cardCnt;
	int 	results;
	int 	i;
	int 	choice1 = 0;
	int 	choice2 = 0;
	int 	choice3 = 0;
	int 	handpos = 0;
	int 	bonus = 0;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};

	struct gameState state;


	testCard = (char*)malloc(15 * sizeof(char));
	curCard = (char*)malloc(15 * sizeof(char));
	cardNumToName(council_room, testCard);

	initializeGame(numPlayers, k, seed, &state);
	curPlayer = state.whoseTurn;

	//add council_room to hand
	state.hand[curPlayer][state.handCount[curPlayer]] = council_room;
	state.handCount[curPlayer]++;
	handpos = state.handCount[curPlayer-1];

	memcpy(&pretest, &state, sizeof(struct gameState));

	printf("********************************Testing council_room Card****************************\n");
//confirm council_room in hand before attempting to play
	for(i=0; i<state.handCount[curPlayer]; i++){
		//cardNumtoName(state.hand[curPlayer][i], &curCard);
		//printf("Card %d= %s\n", i, curCard);
		if(state.hand[curPlayer][i] == council_room){
			cardCnt++;
			handpos = i;
		}
	}
	printf("%s cards in hand before call: %d\n",testCard, cardCnt);
	assertTrue(cardCnt, 0, 2);

	results = cardEffect(council_room, choice1, choice2, choice3, &state, handpos, &bonus);

	//check return value
	printf("expected return value = 0\n");
	printf("acutal return value = %d\n", results);
	assertTrue(0, results, 0);

	printf("card played, check 4 cards added and council_room removed\n");
	//check that hand count increase by 2 for current player
	printf("check that hand count increased by net 3(3 added 1 removed)\n");
	printf("hand count before calling buyCard() = %d\n", pretest.handCount[curPlayer]);
	printf("hand count after calling buyCard() = %d\n", state.handCount[curPlayer]);
	assertTrue(pretest.handCount[curPlayer] + 3, state.handCount[curPlayer], 0);

	//check that card added to played cards
	printf("check playedCard count incremented by 1\n");
	printf("playedCardCount before call = %d, after call %d\n", pretest.playedCardCount, state.playedCardCount);
	assertTrue(pretest.playedCardCount + 1, state.playedCardCount, 0);

	printf("check playedCard includes council_room in last spot\n");
	
	cardNumToName(state.playedCards[state.playedCardCount-1], curCard);
	printf("card in index %d is %s\n", state.playedCardCount-1, curCard );
	assertTrue(state.playedCards[state.playedCardCount-1], council_room, 0);

	printf("check that deckCount decremented by 4\n");
	printf("deckCount before call = %d, after call %d\n", pretest.deckCount[curPlayer], state.deckCount[curPlayer]);
	assertTrue(pretest.deckCount[curPlayer] - 4, state.deckCount[curPlayer], 0);

	printf("check that numBuys incremented");
	printf("expected numBuys: %d, numBuys %d\n", pretest.numBuys + 1, state.numBuys);
	assertTrue(pretest.numBuys + 1, state.numBuys, 0);

	printf("check other game state field to ensure not altered\n");
	printf("expected outpostPlayed: 0, outpostPlayed: %d\n", state.outpostPlayed);
	assertTrue(0, state.outpostPlayed, 0);

	printf("expected phase: 0, phase: %d\n", state.phase);
	assertTrue(0, state.phase, 0);

	printf("expected numActions: 1, numActions %d\n", state.numActions);
	assertTrue(1, state.numActions, 0);

	printf("check that hand count for other player incremented\n");
	printf("hand count before call= %d, after call() = %d\n", pretest.handCount[curPlayer+1], state.handCount[curPlayer+1]);
	assertTrue(pretest.handCount[curPlayer+1] + 1, state.handCount[curPlayer+1], 0);

	printf("check that deck count for other player decremented\n");
	printf("hand count before call= %d, after call() = %d\n", pretest.deckCount[curPlayer+1], state.deckCount[curPlayer+1]);
	assertTrue(pretest.deckCount[curPlayer+1] - 1, state.deckCount[curPlayer+1], 0);




	printf("********************************council_room Testing Complete****************************\n");
	return 0;
}