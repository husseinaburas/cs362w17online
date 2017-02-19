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
int PLAYER = 1;
int tempError = 0;

void testPrintState(struct gameState *state) {
	int i, j;
	char * tempChar = malloc(sizeof(char*)*30);
	fprintf(stderr, "Smithy: Printing State due to error\n");
	fprintf(stderr, "\t numPlayers: %d\n", state->numPlayers);
	fprintf(stderr, "\t whoseTurn: %d\n", state->whoseTurn);
	fprintf(stderr, "\t numActions: %d\n", state->numActions);
	for(i = 0; i < state->numPlayers; i++){
		fprintf(stderr, "\t handCount %d : %d\n", i, state->handCount[i]);
		fprintf(stderr, "\t\t");
		for(j = 0; j < state->handCount[i]; j++){
			if(state->handCount[i] > MAX_HAND){
				fprintf(stderr, "Hand Size Larger than MAX_HAND, breaking to avoid SIGSEGV\n");
				break;
			}
			cardNumToName(state->hand[i][j], tempChar);
			fprintf(stderr, "%s, ", tempChar);
			if((j != 0 && j % 10 == 0) || j == state->handCount[i] - 1){
				fprintf(stderr, "\n\t\t");
			}
		}
	}
	for(i = 0; i < state->numPlayers; i++){
		fprintf(stderr, "\t deckCount %d : %d\n", i, state->deckCount[i]);
		fprintf(stderr, "\t\t");
		for(j = 0; j < state->deckCount[i]; j++){
			if(state->deckCount[i] > MAX_DECK){
				fprintf(stderr, "Deck Size Larger than MAX_DECK, breaking to avoid SIGSEGV\n");
				break;
			}
			cardNumToName(state->deck[i][j], tempChar);
			fprintf(stderr, "%s, ", tempChar);
			if((j != 0 && j % 10 == 0) || j == state->deckCount[i] - 1){
				fprintf(stderr, "\n\t\t");
			}
		}
	}
	for(i = 0; i < state->numPlayers; i++){
		fprintf(stderr, "\t discardCount %d : %d\n", i, state->discardCount[i]);
		fprintf(stderr, "\t\t");
		for(j = 0; j < state->discardCount[i]; j++){
			if(state->discardCount[i] > MAX_DECK){
				fprintf(stderr, "Discard Size Larger than MAX_DECK, breaking to avoid SIGSEGV\n");
				break;
			}
			cardNumToName(state->discard[i][j], tempChar);
			fprintf(stderr, "%s, ", tempChar);
			if((j != 0 && j % 10 == 0) || j == state->discardCount[i] - 1){
				fprintf(stderr, "\n\t\t");
			}
		}
	}
}

#define assertEquals(x, y, z) if(!(x == y)){ fprintf(stderr, "%s, Expected %d, Actual: %d\n",z, x, y); ERROR = 1; tempError = 1; }
#define assert(x, y) if(!(x)){fprintf(stderr, "Assertion Error: %s\n", y); ERROR = 1; tempError = 1; }

void checkVillage(struct gameState *state, int handPos) {
	int r;
	r = playVillage(state, handPos);
	assert(r == 0, "Return value not 0");
}


static void handler(int sig)
{
	fprintf(stderr, "Village SIGSEGV \n");
	exit(-1);
}

int main (int argc, char *argv[]) {
	int i, j, n, handPos;
	signal(SIGSEGV, handler);
	if(argc != 2){
		fprintf(stderr, "Incorrect # of arguments\n");
		exit(1);
	}

	//int k[10] = {adventurer, council_room, feast, gardens, mine,
	       //remodel, smithy, village, baron, great_hall};

	struct gameState *state = malloc(sizeof(struct gameState));
	struct gameState *stateCopy = malloc(sizeof(struct gameState));

	printf ("Random Testing Village.\n");
	SelectStream(0);
	PutSeed((long int) argv[1]);
	srand((long int) argv[1]);
	
	for (n = 0; n < 500; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
		  ((char*)state)[i] = floor(Random() * 256);
		}
		
		//Fill hand with random cards
		int handCount = rand() % (MAX_HAND + 1);
		state->numActions = rand() % 10;
		state->whoseTurn = PLAYER;
		state->numPlayers = 1;
		for(j = 0; j < handCount; j++){
			int card = rand() % (treasure_map + 1);
			state->hand[PLAYER][j] = card;
		}
		state->hand[PLAYER][0] = village;
		handPos = 0;
		state->handCount[PLAYER] = handCount;
		
		int deckCount = rand() % MAX_DECK;
		//Fill deck with random cards
		for(j = 0; j < deckCount; j++){
			int card = rand() % (treasure_map + 1);
			state->deck[PLAYER][j] = card;
		}
		state->discardCount[PLAYER] = 0;
		state->playedCardCount = 0;
		state->deckCount[PLAYER] = deckCount;
		
		tempError = 0;
		memcpy(stateCopy, state, sizeof(struct gameState));
		checkVillage(state, handPos);
		assertEquals(state->handCount[PLAYER], (stateCopy->handCount[PLAYER]), "Village: Unexpected HandCount");
		assertEquals(state->numActions, (stateCopy->numActions + 2), "Village: Unexpected action count");
		state->whoseTurn = 1; //Required, since the bug increments this and our State Printing will not work correctly
		if(tempError == 1){
			testPrintState(state);
		}
		
	}
	
	if(!ERROR){
		printf ("Village tests OK\n");
	} else{
		printf("Village tests finished with errors \n");
	}
	free(state);
	
    exit(0);
}
