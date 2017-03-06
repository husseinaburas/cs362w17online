//This unit test is for the adventurer card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG_MESSAGES 1

int main(){
	int seed = 1000;
	int numPlayer = 2;
	int pos = 0;
	int i = 0;
	int a = 0;
	int testDeck[10] = {adventurer, gardens, mine, copper, smithy, gold, baron, adventurer, silver, great_hall};
	int testHand[1] = {adventurer};
	struct gameState game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	for(i = 0; i < numPlayer; i++){
#if (DEBUG_MESSAGES == 1)
		printf("Adventurercard(): Testing for player: %d\n", i);
#endif
		memset(&game, 23, sizeof(struct gameState));
		a = initializeGame(numPlayer, k, seed, &game);
		game.deckCount[i] = 10;
		memcpy(game.deck[i], testDeck, sizeof(int) * 10);
		game.handCount[i] = 1;
		memcpy(game.hand[i], testHand, sizeof(int));
		int* test;
		adventurerx(&game, i, test, 0);
		
		if(game.discardCount[i] != 3){
			printf("Adventurercard(): TEST ERROR: Proper amount of cards did not discard.\n");
			return 0;
		}
		if(game.discard[i][0] != great_hall && game.discard[i][1] != adventurer && game.discard[i][2] != baron){
			printf("Adventurercard(): TEST ERROR: Proper cards are not in discard pile.\n");
			return 0;
		}
		if(game.handCount[i] != 2){
			printf("Adventurercard(): TEST ERROR: Did not pick out right amount of cards\n.");
			return 0;
		}
		if(game.hand[i][0] != silver && game.hand[i][1] != gold){
			printf("Adventurercard(): TEST ERROR: Did not pick out right cards\n.");
			return 0;
		}
	}
	printf("Adventurercard(): ALL TESTS PASSED.\n");
	return 0;
}