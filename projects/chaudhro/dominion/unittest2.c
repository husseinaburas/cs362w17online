// this unit test is for the function scoreFor()

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
	int a = 0;
	int c = 0;
	int handpos, handSize, discardSize, deckSize;
	int score;
	int expectedScore;
	int maxDeckSize = 20; //how big the deck is
	int maxDiscardSize = 20; //how big the discard pile is
	int * testHand;
	int * testDeck;
	int * testDiscard;
	int maxHandSize = 10; //how many cards max to test shuffle on, minimum of 3.
	struct gameState game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int possibleCards[] = {curse, estate, duchy, province, great_hall, gardens};
	
	printf("TESTING scoreFor():\n");
	for(i = 0; i < numPlayer; i++){
		for(handSize = 1; handSize < maxHandSize; handSize++){
			for(deckSize = 5; deckSize < maxDeckSize; deckSize++){
				for(discardSize = 0; discardSize < maxDiscardSize; discardSize++){
#if (DEBUG_MESSAGES == 1)
					printf("scoreFor(): Testing for player: %d with a hand size of: %d and deck size of: %d and discard size of : %d\n", i, handSize, deckSize, discardSize);
#endif
					memset(&game, 23, sizeof(struct gameState));
					a = initializeGame(numPlayer, k, seed, &game);
					game.handCount[i] = handSize; //number of cards in hand
					testHand = malloc(sizeof(int) * handSize);
					for(c = 0; c < handSize; c++){
						testHand[c] = possibleCards[c % 6];
					}
					memcpy(game.hand[i], testHand, sizeof(int) * handSize);
					score = scoreFor(i, &game); // test score with just hand
					expectedScore = 0;
					for(c = 0; c < handSize; c++){
						if(testHand[c] == curse){
							expectedScore = expectedScore - 1;
						}
						else if(testHand[c] == estate){
							expectedScore = expectedScore + 1;
						}
						else if(testHand[c] == duchy){
							expectedScore = expectedScore + 3;
						}
						else if(testHand[c] == province){
							expectedScore = expectedScore + 6;
						}
						else if(testHand[c] == great_hall){
							expectedScore = expectedScore + 1;
						}
						else if(testHand[c] == gardens){
							expectedScore = expectedScore + handSize/10;
						}
					}

#if (DEBUG_MESSAGES == 1)
					printf("scoreFor(): just hand - Score: %d Expected Score: %d\n", score, expectedScore);
#endif
					if(score != expectedScore){
						printf("scoreFor(): TEST FAILED: expected score did not match actual score for just hand\n");
						return 0;
					}
					memset(&game, 23, sizeof(struct gameState));
					a = initializeGame(numPlayer, k, seed, &game);
					game.deckCount[i] = deckSize;
					testDeck = malloc(sizeof(int) * deckSize);
					for(c = 0; c < deckSize; c++){
						testDeck[c] = possibleCards[c % 6];
					}
					memcpy(game.deck[i], testDeck, sizeof(int) * deckSize);
					score = scoreFor(i, &game); // test score for discard
					
					expectedScore = 0;
					for(c = 0; c < handSize; c++){
						if(testDeck[c] == curse){
							expectedScore = expectedScore - 1;
						}
						else if(testDeck[c] == estate){
							expectedScore = expectedScore + 1;
						}
						else if(testDeck[c] == duchy){
							expectedScore = expectedScore + 3;
						}
						else if(testDeck[c] == province){
							expectedScore = expectedScore + 6;
						}
						else if(testDeck[c] == great_hall){
							expectedScore = expectedScore + 1;
						}
						else if(testDeck[c] == gardens){
							expectedScore = expectedScore + handSize/10 + deckSize/10;
						}
					}
#if (DEBUG_MESSAGES == 1)
					printf("scoreFor(): just deck - Score: %d Expected Score: %d\n", score, expectedScore);
#endif
					if(score != expectedScore){
						printf("scoreFor(): TEST FAILED: expected score did not match actual score for just deck\n");
						return 0;
					}
					memset(&game, 23, sizeof(struct gameState));
					a = initializeGame(numPlayer, k, seed, &game);
					game.discardCount[i] = discardSize;
					testDiscard = malloc(sizeof(int) * discardSize);
					for(c = 0; c < discardSize; c++){
						testDiscard[c] = possibleCards[c % 6];
					}
					memcpy(game.discard[i], testDiscard, sizeof(int) * discardSize);
					score = scoreFor(i, &game); // test score for discard
					
					expectedScore = 0;
					for(c = 0; c < handSize; c++){
						if(testDeck[c] == curse){
							expectedScore = expectedScore - 1;
						}
						else if(testDeck[c] == estate){
							expectedScore = expectedScore + 1;
						}
						else if(testDeck[c] == duchy){
							expectedScore = expectedScore + 3;
						}
						else if(testDeck[c] == province){
							expectedScore = expectedScore + 6;
						}
						else if(testDeck[c] == great_hall){
							expectedScore = expectedScore + 1;
						}
						else if(testDeck[c] == gardens){
							expectedScore = expectedScore + handSize/10 + deckSize/10;
						}
					}
				
#if (DEBUG_MESSAGES == 1)
					printf("scoreFor(): just discard - Score: %d Expected Score: %d\n\n", score, expectedScore);
#endif
					if(score != expectedScore){
						printf("scoreFor(): TEST FAILED: expected score did not match actual score for just discard\n");
						return 0;
					}
				}		
			}
		}
	}
	printf("scoreFor(): ALL TESTS PASSED!");
	return 0;
}