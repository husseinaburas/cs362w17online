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

void fillDeck(int *cards, int size, int player, struct gameState *state)
{
    int i;
    for (i = 0; i < size; i++){
        state->deck[player][i] = (*cards + i);
    }
	state->deckCount[player] = size;
}

void fillDecks(int *cards, int size, struct gameState *state)
{
	int i;
	for(i = 0; i < state->numPlayers; i++){
		fillDeck(cards, size, i, state);
	}
}

void reset(struct gameState *state, int player)
{
	int i,j;
	state->whoseTurn = player;
	for(j = 0; j < state->numPlayers; j++){
		//Empty hands
		for(i = 0; i < state->handCount[j]; i++){
			state->hand[j][i] = -1;
		}
		state->handCount[j] = 0;
		//Empty deck
		for(i = 0; i < state->deckCount[j]; i++){
			state->deck[j][i] = -1;
		}
		state->deckCount[j] = 0;
		//Empty discard
		for(i = 0; i < state->discardCount[j]; i++){
			state->discard[j][i] = -1;
		}
		state->discardCount[j] = 0;
	}
	
	//Empty played cards
	for(i = 0; i < state->playedCardCount; i++){
		state->playedCards[i] = 0;
	}
	state->playedCardCount = 0;
	
	//add council_room to handPos 0
	state->hand[player][0] = council_room;
	state->handCount[player] = 1;
	state->numBuys = 1;
	state->whoseTurn = player;
}

static void handler(int sig)
{
	printf("cardtest4 SIGSEGV\n");
	exit(-1);
}

int main () {
    int returnVal, i;
	int player = PLAYER;
	int deck1Size = 5;
	int deck2Size = 5;
	struct gameState *state = malloc(sizeof(struct gameState));
	signal(SIGSEGV, handler);
	
	state->numPlayers = NUM_PLAYERS;
	
	reset(state, player);
	
	//Deck1 for all
	fillDecks(DECK1, deck1Size, state);
	returnVal = playCouncil_Room(state, 0);
	assert(returnVal == 0);
	for(i = 1; i < state->numPlayers; i++){
		assert(state->handCount[i] == 1);
	}
	assert(state->handCount[player] == 4);
	assert(state->playedCardCount == 1);
	assert(state->playedCards[0] == council_room);
	
	reset(state, player);
	
	//NoDeck for player
	for(i = 1; i < state->numPlayers; i++){
		fillDeck(DECK2, deck2Size, i, state);
	}
	returnVal = playCouncil_Room(state, 0);
	assert(returnVal == -1);
	assert(state->playedCardCount == 0);
	assert(state->handCount[player] == 1);
	for(i = 1; i < state->numPlayers; i++){
		assert(state->handCount[i] == 0);
	}
	
	reset(state, player);
	
	//No Deck for all	
	returnVal = playCouncil_Room(state, 0);
	assert(returnVal == -1);
	assert(state->playedCardCount == 0);
	assert(state->handCount[player] == 1);
	for(i = 1; i < state->numPlayers; i++){
		assert(state->handCount[i] == 0);
	}
	
	free(state);
	
	if(!ERROR){
		printf("cardtest4 finished successfully\n");
	} else{
		printf("cardtest4 finished with errors\n");
	}
    return 0;
}
