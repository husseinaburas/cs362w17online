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
int PLAYER = 0;
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

void checkPlayAdventurer(struct gameState *state, int expectedReturn) {
	int r;
	r = playAdventurer(state);
	assert(r == expectedReturn, "Return value not expected");
}


static void handler(int sig)
{
	fprintf(stderr, "Adventurer SIGSEGV \n");
	exit(-1);
}

int main (int argc, char *argv[]) {
	int i, j, k, n, expectedReturn;
	signal(SIGSEGV, handler);
	if(argc != 2){
		fprintf(stderr, "Incorrect # of arguments\n");
		exit(1);
	}
	//int k[10] = {adventurer, council_room, feast, gardens, mine,
	       //remodel, smithy, village, baron, great_hall};

	struct gameState *state = malloc(sizeof(struct gameState));
	struct gameState *stateCopy = malloc(sizeof(struct gameState));
	
	printf ("Random Testing Adventurer.\n");
	SelectStream(0);
	PutSeed((long int) argv[1]);
	
	srand((long int) argv[1]);
	
	for (n = 0; n < 500; n++) {
		int numTreasures = 0;
		for (i = 0; i < sizeof(struct gameState); i++) {
		  ((char*)state)[i] = floor(Random() * 256);
		}
		//Fill hands for each player with random cards
		//state->numPlayers = rand() % MAX_PLAYERS + 1;
		state->numPlayers = 1;
		for(j = 0; j < state->numPlayers; j++){
			state->discardCount[j] = 0;
			int handCount = rand() % (MAX_HAND + 1);
			state->handCount[j] = handCount;
			for (k = 0; k < handCount; k ++){
				state->hand[j][k] = rand() % (treasure_map + 1);
			}
		}
		
		/* //Fill decks for each player with random cards
		for (j = 0; j < state->numPlayers; j++){
			state->deckCount[j] = rand() % (MAX_DECK + 1);
			for(k = 0; k < state->deckCount[j]; k++){
				//Increase odds of putting treasure in deck
				if((rand() % 2) == 0){
					state->deck[j][k] = province + (rand() % 3);
					numTreasures += 1;
				}else{
					int card = rand() % (treasure_map + 1);
					if (card == copper || card == silver || card == gold){
						numTreasures += 1;
					}
					state->deck[j][k] = card;
				}
			}
		} */
		
		if(numTreasures > 1){
			expectedReturn = 0;
		} else{
			expectedReturn = -1;
		}
		state->whoseTurn = PLAYER;
		tempError = 0;
		memcpy(stateCopy, state, sizeof(struct gameState));
		checkPlayAdventurer(state, expectedReturn);
		stateCopy->handCount[PLAYER] += (expectedReturn == 0) ? 2 : 0;
		assertEquals(stateCopy->handCount[PLAYER], state->handCount[PLAYER], "Adventurer: Unexpected Handcount");
		if(tempError == 1){
			testPrintState(state);
		}
	}
	
	if(!ERROR){
		printf ("Adventurer tests OK\n");
	} else{
		printf("Adventurer tests finished with errors \n");
	}
	free(state);
	
    exit(0);
}
