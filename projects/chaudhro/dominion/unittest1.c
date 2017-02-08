// This unit test is for the function shuffle()

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
	int i = 0;
	int b = 0, c = 0;
	int samespot = 0;
	int test = 0;
	int a, handSize;
	int maxHandSize = 10; //how many cards max to test shuffle on, minimum of 3.
	struct gameState game;
	int testHand[maxHandSize];
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	for(i = 0; i < maxHandSize; i++){
		testHand[i] = i % 25;
	}
	
	printf("TESTING shuffle(): \n");
	for(i = 0; i < numPlayer; i++){
		for(handSize = 2; handSize < maxHandSize; handSize++){
#if (DEBUG_MESSAGES == 1)
			printf("shuffle(): Testing for player: %d with a hand size of: %d \n", i, handSize);
#endif
			memset(&game, 23, sizeof(struct gameState));
			a = initializeGame(numPlayer, k, seed, &game);
			game.handCount[i] = handSize; //number of cards in hand
			memcpy(game.hand[i], testHand, sizeof(int) * handSize);
			shuffle(i, &game);
#if (DEBUG_MESSAGES == 1)
			printf("shuffle(): Size of hand: %d expected hand size: %d\n", game.handCount[i], handSize);
#endif
			if(!(game.handCount[i] == handSize)){ //make sure the hand has the same amount of cards as before
				printf("TEST FAILED: hand changed sizes\n");
				return 0;
			}
			for(b = 0; b < handSize; b++){
				test = 0;
				samespot = 0;
				for(c = 0; c < handSize; c++){
					if(game.hand[i][b] == testHand[c]){
						test = 1;
						if(b == c){
							samespot++;
						}
						break;
					}
				}
#if (DEBUG_MESSAGES == 1)
				if(test == 1){
					printf("shuffle(): card %d found in hand!\n", game.hand[i][b]);
				}
				else{
					printf("shuffle(): card %d not found in hand!\n", game.hand[i][b]);
				}
#endif
				if(test == 0){
					printf("shuffle(): TEST FAILED: card missing from shuffled hand\n");
					return 0;
				}
				if(samespot == handSize){
					printf("shuffle(): TEST FAILED: all cards found in the same spot! %d \n");
					return 0;
				}
			}
			
		}
	}
	printf("shuffle(): ALL TESTS PASSED!\n");
	return 0;
}
