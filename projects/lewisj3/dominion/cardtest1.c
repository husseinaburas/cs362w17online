#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <signal.h>
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
int DECK1[] = {baron, copper, council_room, copper};
int DECK2[] = {silver, gold, village, feast, baron};
int DECK3[] = {baron, council_room, feast};
int DECK4[] = {baron, council_room, feast, copper};

void fillDeck(int *cards, int size, int player, struct gameState *state)
{
    int i;
    for (i = 0; i < size; i++){
        state->deck[player][i] = (*cards + i);
    }
	state->deckCount[player] = size;
}

void reset(struct gameState *state, int player)
{
	int i;
	state->whoseTurn = player;
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
	
	//Empty played cards
	for(i = 0; i < state->playedCardCount; i++){
		state->playedCards[i] = 0;
	}
	state->playedCardCount = 0;
	
	state->hand[player][0] = adventurer;
	state->handCount[player] = 1;
}

static void handler(int sig)
{
	printf("cardtest1 SIGSEGV\n");
	exit(-1);
}

int main () {
    int returnVal;
	int player = PLAYER;
	int deck1Size = 5;
	int deck2Size = 5;
	int deck3Size = 3;
	int deck4Size = 4;
	struct gameState *state = malloc(sizeof(struct gameState));
	signal(SIGSEGV, handler);
	
	reset(state, player);
	
	//No coins in deck + discard
	fillDeck(DECK3, deck3Size, player, state);
	returnVal = playAdventurer(state);
	assert(returnVal == -1);
	assert(state->handCount[player] == 1);
	assert(state->playedCardCount == 0);
	
	reset(state, player);
	
	//1 coin in deck + discard
	fillDeck(DECK4, deck4Size, player, state);
	returnVal = playAdventurer(state);
	assert(returnVal == -1);
	assert(state->handCount[player] == 1);
	assert(state->playedCardCount == 0);
	
	reset(state, player);
	
	//Draw copper, council_room, copper
	fillDeck(DECK1, deck1Size, player, state);
	returnVal = playAdventurer(state);
	assert(returnVal == 0);
	assert(state->handCount[player] == 2);
	assert(state->playedCardCount == 1);
	assert(state->playedCards[0] == adventurer);
	
	reset(state, player);
	
	//Draw all cards until hit two gold
	fillDeck(DECK2, deck2Size, player, state);
	returnVal = playAdventurer(state);
	assert(state->discardCount[player] == 3);
	assert(state->handCount[player] == 2);
	assert(state->playedCardCount == 1);
	assert(state->playedCards[0] == adventurer);
	
	free(state);
	
	if(!ERROR){
		printf("cardtest1 finished successfully\n");
	} else{
		printf("cardtest1 finished with errors\n");
	}
    return 0;
}
