/*
 * Random Test of Smithy Card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int assertTrue(int expected, int received) {
	if(expected == received)
		return 0;
	else
		return -1;
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("Useage: randomtestcard1 <seed>\n");
		exit(0);	
	}

	printf("Random Test Smithy Card\n");
	printf("-----------------------------------------------------------------------\n");
	int fail = 0;
	int n;
	int i;
	int seed = atoi(argv[1]);
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int numPlayers, numDeck, numHand, numDiscard, numPlayed;
	srand(time(NULL));

	//for loop controls random test runs
	for(n=0; n<500000; n++) {	

		//get a random number of players (2-4)
		numPlayers = rand()%(4+1-2)+2;

		//get random deck, discard sizes, and number of cards played (0-500)
		numDiscard = rand()%(501);
		numDeck = rand()%(501);
		numPlayed = rand()%(501);

		//get random hand size (1-500)
		numHand = rand()%500+1;

		initializeGame(numPlayers, k, seed, &G);

		//create new hand/discard/deck/played piles
		G.deckCount[0] = numDeck;
		G.handCount[0] = numHand;
		G.discardCount[0] = numDiscard;
		G.playedCardCount = numPlayed;

		//rand()%17 because the card enum uses the first 17 cards (0-16)
		for(i=0; i<numDeck; i++) {
			G.deck[0][i] = rand()%17;
		}

		for(i=0; i<numDiscard; i++) {
			G.discard[0][i] = rand()%17;
		}

		for(i=0; i<numHand; i++) {
			G.hand[0][i] = rand()%17;
		}

		for(i=0; i<numPlayed; i++) {
			G.playedCards[i] = rand()%17;
		}

		//place smithy in hand
		G.hand[0][i] = smithy;

		//call smithy card
		smithyCard(&G, 0, 0);

		//if there are enough cards in the deck,
		//deck should be -3, hand +3, discard no change
		if(numDeck >= 3) {
			numDeck = numDeck - 3;
			numHand = numHand + 3;
			if((assertTrue(numDeck, G.deckCount[0])) != 0)
				fail++;
			if((assertTrue(numHand, G.handCount[0])) != 0)
				fail++;
			if((assertTrue(numDiscard, G.discardCount[0])) != 0)
				fail++;
		}
		//else it should shuffle and the discard should be 0
		//the deck should be the deck+discard
		else{
			numDeck = numDeck+numDiscard;
			//if there are enough cards in newly shuffled deck
			//deck now -3, discard 0, hand +3
			if(numDeck >= 3) {
				numDeck = numDeck-3;
				numDiscard = 0;
				numHand = numHand+3;
				if((assertTrue(numDeck, G.deckCount[0])) != 0)
					fail++;
				if((assertTrue(numDiscard, G.discardCount[0])) != 0)
					fail++;
				if((assertTrue(numHand, G.handCount[0])) != 0)
					fail++;
			}
			//if there are not enough cards in newly shuffled deck
			//deck is added to hand (whether 0, 1, or 2)
			//deck and discard become 0
			else {
				numHand = numHand+numDeck;
				numDeck = 0;
				numDiscard = 0;
				if((assertTrue(numDeck, G.deckCount[0])) != 0)
					fail++;
				if((assertTrue(numDiscard, G.discardCount[0])) != 0)
					fail++;
				if((assertTrue(numHand, G.handCount[0])) != 0)
					fail++;
			}
			
		}
		//in all cases played card number increments
		numPlayed++;
		if((assertTrue(numPlayed, G.playedCardCount)) != 0)
			fail++;
	}
	if(fail > 0)
		printf("Tests have failed\n");
	else
		printf("All tests passed\n");
	printf("-----------------------------------------------------------------------\n");
	printf("Random Test Complete\n");

	return 0;
}
