//This unit test is for the treasure map card

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
	int testDeck[0] = {};
	int testHand1[5] = {adventurer, gardens, treasure_map, copper, treasure_map};
	int testHand2[5] = {adventurer, gardens, smithy, copper, treasure_map};
	struct gameState game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	for(i = 0; i < numPlayer; i++){
#if (DEBUG_MESSAGES == 1)
		printf("Treasuremapcard(): Testing for player: %d\n", i);
#endif
		memset(&game, 23, sizeof(struct gameState));
		a = initializeGame(numPlayer, k, seed, &game);
		game.deckCount[i] = 0;
		memcpy(game.deck[i], testDeck, sizeof(int) * 10);
		game.handCount[i] = 5;
		memcpy(game.hand[i], testHand1, sizeof(int) * 5);
		treasuremapcard(4, i, &game);
		for(a = 0; a < game.handCount[i]; a++){
			if(game.hand[i][a] == treasure_map){
				printf("Treasuremapcard(): TEST ERROR: Did not remove treasure_maps from hand\n");
			}
			if(game.hand[i][a] != adventurer && game.hand[i][a] != gardens && game.hand[i][a] != copper){
				printf("Treasuremapcard(): TEST ERROR: Unexpected card in hand!\n");
			}
		}
		
		if(game.deckCount[i] != 4){
			printf("Treasuremapcard(): TEST ERROR: Unexpected amount of cards in deck!\n");
		}
		
		for(a = 0; a < game.deckCount[i]; a++){
			if(game.deck[i][a] != gold){
				printf("Treasuremapcard(): TEST ERROR: Deck does not contain 4 gold cards!\n");
			}
		}
		
		game.deckCount[i] = 0;
		memcpy(game.deck[i], testDeck, sizeof(int) * 10);
		game.handCount[i] = 5;
		memcpy(game.hand[i], testHand2, sizeof(int) * 5);
		treasuremapcard(4, i, &game);
		
		for(a = 0; a < game.handCount[i]; a++){
			if(game.hand[i][a] == treasure_map){
				printf("Treasuremapcard(): TEST ERROR: Did not remove treasure_map from hand!\n");
			}
			if(game.hand[i][a] != adventurer && game.hand[i][a] != gardens && game.hand[i][a] != copper && game.hand[i][a] != smithy){
				printf("Treasuremapcard(): TEST ERROR: Unexpected card in hand!\n");
			}
		}
		
		if(game.deckCount[i] != 0){
			printf("Treasuremapcard(): TEST ERROR: Unexpected amount of cards in deck!\n");
		}		
		
	}
	return 0;
}