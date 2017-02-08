#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

//unit test for the drawCard() function

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

	int 	numPlayers = 2;
	int 	seed = 5;
	char 	*testCard;
	char	*testCard2;
	int 	curPlayer;	
	int 	results;
	int 	i, n;
	

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};



	n=0;
	testCard = (char*)malloc(15 * sizeof(char));
	testCard2 = (char*)malloc(15 * sizeof(char));
	cardNumToName(k[n], testCard);

	initializeGame(numPlayers, k, seed, &state);
	curPlayer = state.whoseTurn;
			
	//Save game state before testing
	memcpy(&pretest, &state, sizeof(struct gameState));

	printf("********************************Testing drawCard() function****************************\n");

	results = drawCard(curPlayer, &state);
	printf("Check return value with sufficient cards in deck\n");
	printf("expected return value = 0, acutal return value = %d\n", results);
	assertTrue(0, results, 0);

	printf("Check that deck count is decremented\n");
	printf("Deck count before call: %d, after call: %d\n", pretest.deckCount[curPlayer], state.deckCount[curPlayer]);
	assertTrue(pretest.deckCount[curPlayer] - 1, state.deckCount[curPlayer], 0);

	printf("check that hand count increased by 1\n");
	printf("hand count before call = %d, after call = %d\n", pretest.handCount[curPlayer], state.handCount[curPlayer]);
	assertTrue(pretest.handCount[curPlayer] + 1, state.handCount[curPlayer], 0);

	printf("Check that the card that was on the top of the deck is what\n");
	printf("   was added to the current hand\n");
	cardNumToName((pretest.deck[curPlayer][pretest.deckCount[curPlayer]-1]), testCard);
	cardNumToName((state.hand[curPlayer][state.handCount[curPlayer]-1]), testCard2);
	
	printf("Card on top of deck: %s\n", testCard);
	printf("Card on added to hand: %s\n", testCard2);
	assertTrue(pretest.deck[curPlayer][pretest.deckCount[curPlayer]-1], state.hand[curPlayer][state.handCount[curPlayer]-1], 0);



	printf("check that hand count for other player unchanged\n");
	printf("hand count before call= %d, after calli() = %d\n", pretest.handCount[curPlayer+1], state.handCount[curPlayer+1]);
	assertTrue(pretest.handCount[curPlayer+1], state.handCount[curPlayer+1], 0);

	printf("whose turn before call: %d\n", pretest.whoseTurn);
	printf("whose turn after call: %d\n", state.whoseTurn);
	assertTrue(pretest.whoseTurn, state.whoseTurn, 0);

	printf("phase before call: %d\n", pretest.phase);
	printf("phase after call: %d\n", state.phase);
	assertTrue(pretest.phase, state.phase, 0);

	//reset game state for further testing
	memcpy(&state, &pretest, sizeof(struct gameState));

	//move cards in deck to discard pile to test call with empty deck
	for(i = 0; i < state.handCount[curPlayer]; i++){
		state.discard[curPlayer][i] = state.deck[curPlayer][i];
		state.discardCount[curPlayer]++;
	}
	state.deckCount[curPlayer] = 0;

	//save state with updated counts before calling function again
	memcpy(&pretest, &state, sizeof(struct gameState));

	printf("Emptied deck for testing, current deckcount %d\n",state.deckCount[curPlayer]);
	results = drawCard(curPlayer, &state);
	printf("Check return value with insufficient cards in deck, should still succeed\n");
	printf("expected return value = 0, actual return value = %d\n", results);
	assertTrue(0, results, 0);

	//after calling with empty deck, hand shoudl be increased by 1
	printf("check that hand count increased by 1\n");
	printf("hand count before call = %d, after call = %d\n", pretest.handCount[curPlayer], state.handCount[curPlayer]);
	assertTrue(pretest.handCount[curPlayer] + 1, state.handCount[curPlayer], 0);

	//deck should have old hand count -1 for the drawn card
	printf("Check that deck count was reset to old hand count\n");
	printf("   and then decremented by 1\n");
	printf("Hand count before call: %d\nDeck count before call: %d, after call: %d\n", 
		pretest.handCount[curPlayer], pretest.deckCount[curPlayer], state.deckCount[curPlayer]);
	assertTrue(pretest.handCount[curPlayer] - 1, state.deckCount[curPlayer], 0);

	//verify other states not changed
	printf("check that hand count for other player unchanged\n");
	printf("hand count before call= %d, after calli() = %d\n", pretest.handCount[curPlayer+1], state.handCount[curPlayer+1]);
	assertTrue(pretest.handCount[curPlayer+1], state.handCount[curPlayer+1], 0);

	printf("whose turn before call: %d\n", pretest.whoseTurn);
	printf("whose turn after call: %d\n", state.whoseTurn);
	assertTrue(pretest.whoseTurn, state.whoseTurn, 0);

	printf("phase before call: %d\n", pretest.phase);
	printf("phase after call: %d\n", state.phase);
	assertTrue(pretest.phase, state.phase, 0);



	printf("********************************drawCard() Testing Complete****************************\n");


	return 0;
}