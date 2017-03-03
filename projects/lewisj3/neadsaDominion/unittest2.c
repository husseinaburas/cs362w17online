#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1
int ERROR = 0;
#undef assert
#define assert(x) if(!(x)){printf("Assertion Error!\n"); ERROR = 1; }

int PLAYER = 0;
int NUM_PLAYERS = 4;
int LAST_ENUM_VALUE = treasure_map;
int MAXHAND = 5;

void fillHand(int *cards, int player, struct gameState *state)
{
    int i;
    for (i = 0; i < MAXHAND; i++){
        state->hand[player][i] = (*cards + i);
    }
	state->handCount[player] = MAXHAND;
}

void testGainCard(int supplyPos, struct gameState *state, int toFlag, 
		int player, int expectedReturn)
{
    int returnVal = gainCard(supplyPos, state, toFlag, player);
    assert(returnVal == expectedReturn);
}

void reset(struct gameState *state, int player)
{
	int i;
	//Empty supply
	for (i = 0; i < LAST_ENUM_VALUE; i++){
		state->supplyCount[i] = 0;
	}
	//Empty hand
	for(i = 0; i < state->handCount[player]; i++){
		state->hand[player][i] = -1;
	}
	//Empty deck
	state->handCount[player] = 0;
	for(i = 0; i < state->deckCount[player]; i++){
		state->deck[player][i] = -1;
	}
	state->deckCount[player] = 0;
	//Empty discard
	for(i = 0; i < state->discardCount[player]; i++){
		state->discard[player][i] = -1;
	}
	state->discardCount[player] = 0;
	
}

int main () {
	int toFlag, expectedReturn, i;
    int player = PLAYER;
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = NUM_PLAYERS;
    state->handCount[player] = MAXHAND;
	int *adventurers = malloc(MAXHAND * sizeof(int));
	for(i = 0; i < MAXHAND; i++){
		adventurers[i] = adventurer;
	}

    //Empty supply pile
	toFlag = 0;
	expectedReturn = -1;
	state->supplyCount[adventurer] = 0;
	testGainCard(adventurer, state, toFlag, player, expectedReturn);
	
	reset(state, player);
	
	//Supply of 1 to discard
	toFlag = 0;
	expectedReturn = 0;
	state->supplyCount[adventurer] = 1;
	testGainCard(adventurer, state, toFlag, player, expectedReturn);
	assert(state->discardCount[player] == 1);
	assert(state->discard[player][0] == adventurer);
	assert(state->supplyCount[adventurer] == 0);
	
	reset(state, player);
	
	//Supply of multiple Gain to discard
	toFlag = 0;
	expectedReturn = 0;
	state->supplyCount[mine] = 20;
	testGainCard(mine, state, toFlag, player, expectedReturn);
	assert(state->discardCount[player] == 1);
	assert(state->discard[player][0] == mine);
	assert(state->supplyCount[mine] == 19);
	
	reset(state, player);
	
	//Gain to deck
	toFlag = 1;
	expectedReturn = 0;
	state->supplyCount[feast] = 1;
	testGainCard(feast, state, toFlag, player, expectedReturn);
	assert(state->deckCount[player] == 1);
	assert(state->deck[player][0] == feast);
	assert(state->supplyCount[feast] == 0);
	
	reset(state, player);
	
	//Full hand, gain to hand
	toFlag = 2;
	expectedReturn = 0;
	state->supplyCount[village] = 1;
	fillHand(adventurers, player, state);
	testGainCard(village, state, toFlag, player, expectedReturn);
	assert(state->handCount[player] == (MAXHAND + 1));
	assert(state->hand[player][MAXHAND] == village);
	assert(state->supplyCount[village] == 0);
	//Bug - Hand size is greater than max hand but village 
	//still set to hand[player][MAXHAND]
	
	reset(state, player);
	
	
	free(state);
	free(adventurers);
	
	if(!ERROR){
		printf("unittest2 finished successfully\n");
	} else{
		printf("unittest2 finished with errors\n");
	}
	
    return 0;
}
