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
#define assert(x, y) if(!(x)){printf("Assertion Error: %s\n", y); ERROR = 1; }
int PLAYER = 1;

void checkUpdateCoins(int player, struct gameState *state, int bonus) {
	int r;
	r = updateCoins(player, state, bonus);
	assert(r == 0, "Return Value not 0");
}


static void handler(int sig)
{
	printf("UpdateCoins SIGSEGV\n");
	exit(-1);
}

int main () {
	int i, j, n;
	int total = 0;
	signal(SIGSEGV, handler);

	//int k[10] = {adventurer, council_room, feast, gardens, mine,
	       //remodel, smithy, village, baron, great_hall};

	struct gameState *state = malloc(sizeof(struct gameState));
	struct gameState *stateCopy = malloc(sizeof(struct gameState));

	printf ("Random Testing UpdateCoins.\n");
	SelectStream(2);
	PutSeed(4);
	
	for (n = 0; n < 500; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
		  ((char*)state)[i] = floor(Random() * 256);
		}
		total = 0;
		//Pick Random bonus
		int bonus = rand() % 10;
		state->numPlayers = rand() % MAX_PLAYERS + 1;
		
		
		//Fill hand with random cards. record total coins:
		int handCount = rand() % MAX_HAND;
		
		state->whoseTurn = rand() % (state->numPlayers + 1);
		for(j = 0; j < handCount; j++){
			int card = rand() % (treasure_map + 1);
			switch (card){
				case copper:
					total += 1;
					break;
				case silver:
					total += 2;
					break;
				case gold:
					total += 3;
			}
			state->hand[PLAYER][j] = card;
		}
		state->handCount[PLAYER] = handCount;
		memcpy(stateCopy, state, sizeof(struct gameState));
		checkUpdateCoins(PLAYER, state, bonus);
		stateCopy->coins = total+bonus;
		assert(memcmp(state, stateCopy, sizeof(struct gameState)) == 0, "State and StateCopy not equivalent");
	}
	
	if(!ERROR){
		printf ("UpdateCoins tests OK\n");
	} else{
		printf("UpdateCoins tests finished with errors \n");
	}
	free(state);
	
    exit(0);
}
