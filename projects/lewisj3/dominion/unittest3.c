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
int MIXED_DECK[] = {copper, council_room, feast, baron, cutpurse};

void fillHand(int *cards, int size, int player, struct gameState *state)
{
    int i;
    for (i = 0; i < size; i++){
        state->hand[player][i] = (*cards + i);
    }
	state->handCount[player] = size;
}

void fillDeck(int *cards, int size, int player, struct gameState *state)
{
	int i;
	for(i = 0; i < size; i++){
		state->deck[player][i] = cards[i];
	}
	state->deckCount[player] = size;
}

void fillDiscard(int *cards, int size, int player, 
		struct gameState * state)
{
	int i;
	for (i = 0; i < size; i++){
		state->discard[player][i] = cards[i];
	}
	state->discardCount[player] = size;
}

void testDrawCard(int player, struct gameState *state, int count, 
int expectedReturn)
{
	int i, returnVal;
	for(i = 0; i < count; i ++){
		returnVal = drawCard(player, state);
		assert(returnVal == expectedReturn);
	}
    
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
	int count, expectedReturn, i;
    int player = PLAYER;
	int mixedDeckSize = sizeof(MIXED_DECK)/sizeof(MIXED_DECK[0]);
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = NUM_PLAYERS;
    state->handCount[player] = MAXHAND;
	int *adventurers = malloc(MAXHAND * sizeof(int));
	for(i = 0; i < MAXHAND; i++){
		adventurers[i] = adventurer;
	}

	reset(state, player);
	
	fillDiscard(MIXED_DECK, mixedDeckSize,
		player, state);
	
    //Empty deck, MIXED_DECK discard, draw 1
	count = 1;
	expectedReturn = 0;
	testDrawCard(player, state, count, expectedReturn);
	assert(state->handCount[player] == 1);
	assert(state->deckCount[player] == (mixedDeckSize - 1));
	
	reset(state, player);
	
	//Non-Empty Deck, Non-Empty Discard
	fillDiscard(MIXED_DECK, mixedDeckSize, player, state);
	fillDeck(adventurers, MAXHAND, player, state);
	count = 1;
	expectedReturn = 0;
	testDrawCard(player, state, count, expectedReturn);
	assert(state->handCount[player] == 1);
	assert(state->deckCount[player] == (mixedDeckSize - 1));
	
	reset(state, player);
	
	fillDeck(adventurers, MAXHAND, player, state);
	
	//Draw MAXHAND cards, all adventurer
	count = MAXHAND;
	expectedReturn = 0;
	testDrawCard(player, state, count, expectedReturn);
	assert(state->handCount[player] == MAXHAND);
	assert(state->hand[player][MAXHAND/2] == adventurer);
	assert(state->deckCount[player] == 0);
	
	reset(state, player);
	
	//Empty Deck and Discard
	count = 1;
	expectedReturn = -1;
	testDrawCard(player, state, count, expectedReturn);
	assert(state->handCount[player] == 0);
	assert(state->deckCount[player] == 0);
	
	free(state);
	free(adventurers);
	
	if(!ERROR){
		printf("unittest3 finished successfully\n");
	} else{
		printf("unittest3 finished with errors\n");
	}
	
    return 0;
}
