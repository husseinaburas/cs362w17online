/*
 * Random Test of Adventurer Card
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
		printf("Useage: randomtestadventurer <seed>\n");
		exit(0);	
	}

	printf("Random Test Adventurer Card\n");
	printf("-----------------------------------------------------------------------\n");
	int fail = 0;
	int n;
	int i;
	int seed = atoi(argv[1]);
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int numPlayers, numDeck, numHand, numDiscard;
        int choice1 = 0;
        int choice2 = 0;
        int choice3 = 0;
        int handpos;
        int bonus = 0;
	srand(time(NULL));

	//for loop controls random test runs
	for(n=0; n<5; n++) {	
		int preHandTreas = 0, preDeckTreas = 0, preDiscardTreas = 0, preDeckDisc = 0;
		int postHandTreas = 0, postDeckTreas = 0, postDiscardTreas = 0, postDeckDisc = 0;
		int postHandTreasPlayer = 0, postDeckTreasPlayer = 0, postDiscardTreasPlayer = 0, postDeckDiscPlayer = 0;

		//get a random number of players (2-4)
		numPlayers = rand()%(4+1-2)+2;

		//get random deck and discard sizes (0-500)
		numDiscard = rand()%(501);
		numDeck = rand()%(501);

		//get random hand size (1-500)
		numHand = rand()%500+1;

		initializeGame(numPlayers, k, seed, &G);

		//create new hand/discard/deck
		G.deckCount[0] = numDeck;
		G.handCount[0] = numHand;
		G.discardCount[0] = numDiscard;
		G.whoseTurn = 0;
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

		//place adventurer in hand
		G.hand[0][i] = adventurer;
		handpos=i;
		//copy pre-adventurer card treasure numbers
		for(i=0; i<G.deckCount[0]; i++) {
			if(G.deck[0][i] == copper || G.deck[0][i] == silver || G.deck[0][i] == gold)
				preDeckTreas++;
		}

		for(i=0; i<G.handCount[0]; i++) {
			if(G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold)
				preHandTreas++;
		}

		for(i=0; i<G.discardCount[0]; i++) {
			if(G.discard[0][i] == copper || G.discard[0][i] == silver || G.discard[0][i] == gold)
				preDiscardTreas++;
		}
		//call adventurer card
		cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
		//count treasures in player's cards

		for(i=0; i<G.deckCount[0]; i++) {
			if(G.deck[0][i] == copper || G.deck[0][i] == silver || G.deck[0][i] == gold)
				postDeckTreasPlayer++;
		}

		for(i=0; i<G.handCount[0]; i++) {
			if(G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold)
				postHandTreasPlayer++;
		}

		for(i=0; i<G.discardCount[0]; i++) {
			if(G.discard[0][i] == copper || G.discard[0][i] == silver || G.discard[0][i] == gold)
				postDiscardTreasPlayer++;
		}
		postDeckDiscPlayer = postDiscardTreasPlayer+postDeckTreasPlayer;

		//if there were 2+ treasures in deck, after card called
		//deck should be down 2 treasures
		//hand should be up two treasures
		//discard should have the same number of treasures
		if(preDeckTreas >= 2) {
			postDeckTreas = preDeckTreas - 2;
			postHandTreas = preHandTreas + 2;
			postDiscardTreas = preDiscardTreas;
			if((assertTrue(postDeckTreas, postDeckTreasPlayer)) != 0)
				fail++;
			if((assertTrue(postHandTreas, postHandTreasPlayer)) != 0)
				fail++;
			if((assertTrue(postDiscardTreas, postDiscardTreasPlayer)) != 0)
				fail++;
		}
		//else it will shuffle and we won't know
		//exactly how meany treasures are in the
		//deck and discard, but we know how many would
		//be in both together
		else{
			preDeckDisc = preDeckTreas+preDiscardTreas;
			if(preDeckDisc >= 2) {
				postDeckDisc = preDeckDisc - 2;
				postHandTreas = preHandTreas + 2;
				if((assertTrue(postHandTreas, postHandTreasPlayer)) != 0)
					fail++;
				if((assertTrue(postDeckDisc, postDeckDiscPlayer)) != 0)
					fail++;
			}
			if(preDeckDisc == 1) {
				postDeckDisc = preDeckDisc - 1;
				postHandTreas = preHandTreas + 2;
				if((assertTrue(postHandTreas, postHandTreasPlayer)) != 0)
					fail++;
				if((assertTrue(postDeckDisc, postDeckDiscPlayer)) != 0)
					fail++;
			}
			if(preDeckDisc < 1) {
				if((assertTrue(postHandTreas, postHandTreasPlayer)) != 0)
					fail++;
				if((assertTrue(postDeckDisc, postDeckDiscPlayer)) != 0)
					fail++;
			}
			
		}
	}
	if(fail > 0)
		printf("Tests have failed\n");
	else
		printf("All tests passed\n");
	printf("-----------------------------------------------------------------------\n");
	printf("Random Test Complete\n");

	return 0;
}
