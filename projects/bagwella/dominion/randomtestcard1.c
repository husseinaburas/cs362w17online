#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


//constants 
#define NUM_KING_CARDS 20
#define TEST_CARD smithy
#define NUM_TESTS 200000


int main() {

	srand(time(NULL));
	struct gameState G, testG;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int testcase, player, numPlayers, seed, testNum = 0, alreadyChosen, kcard, handPos, cardAcquired, coinsCounted, returnedVal, k_card_counter;
	int error_1_count = 0, error_2_count = 0, error_3_count = 0, error_4_count= 0, error_5_count = 0, error_6_count = 0, error_7_count = 0, error_8_count = 0;
	int kingdom_cards[10], supply[17];
	
	for(testcase = 0; testcase < NUM_TESTS; testcase++) {

		seed = rand();
		numPlayers = (rand() % 3) + 2;

		for (int i = 0; i < 10; i++) 	//initialize kingdom cards 
			kingdom_cards[i] = -1;
		

		//randomize kingdom cards used in the game

		for (k_card_counter = 0; k_card_counter < 10; ) {

			//draw a particular card by picking a random enum
			kcard = (rand() % NUM_KING_CARDS) + 7;
			
			//make sure its not the testCard
			while (kcard == TEST_CARD) {
				kcard = (rand() % NUM_KING_CARDS) + 7;
			}

			alreadyChosen = -1;

			//loop through cards to check if picked card has been chosen
			for (int j = 0; j < k_card_counter; j++) {
				if (kingdom_cards[j] == kcard)  {
					alreadyChosen = 0;
					break; 
				}
			}

			if (alreadyChosen == -1) {

				kingdom_cards[k_card_counter] = kcard; 
				k_card_counter += 1; 
			}

		}

		//randomnly replace 1 of the 10 cards with testCard
		kingdom_cards[rand() % 10] = TEST_CARD;

		memset(&testG, 23, sizeof(struct gameState));
		initializeGame(numPlayers, kingdom_cards, seed, &testG);

		testNum++;
		printf("------Test#%d Smithy Card--------\n", testNum);

		player = rand() % numPlayers;
		testG.whoseTurn = player;

	    testG.deckCount[player] = rand() % MAX_DECK;
		testG.discardCount[player] = rand() % MAX_DECK;
	    testG.handCount[player] = rand() % MAX_HAND;
	    

	   	for(int j = 0; j < testG.deckCount[player]; j++)
	        testG.deck[player][j] = rand() % 26;
	       

	    for(int j = 0; j < testG.discardCount[player]; j++)
	    	testG.discard[player][j] = rand() % 26;


	    for(int j = 0; j < testG.handCount[player]; j++)
	        testG.hand[player][j] = rand() % 26;


	    printf("Before playing smithy: player = %d; deck count = %d; discard count = %d; hand count = %d\n", player+1, testG.deckCount[player], testG.discardCount[player], testG.handCount[player]);
	    printf("Playing now....\n");
		

		memcpy(&G, &testG, sizeof(struct gameState));

		printf("TEST#1 - CardEffect return\n");
		returnedVal = cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);
		if (returnedVal != 0) {
			error_1_count++;
			printf("ERROR#1 - CardEffect returned improperly.\n");
		}
		else
			printf("TEST#1 - Passed\n");

		
		printf("TEST#2 - changes in handCount\n");

		if ((testG.handCount[G.whoseTurn]-3) != G.handCount[G.whoseTurn]) {
				printf("ERROR#2 - player's hand size did not increase by 3\n ");
				printf("prior: %d post: %d\n ",G.handCount[G.whoseTurn], testG.handCount[G.whoseTurn]);
				error_2_count++;
			}
		else
			printf("TEST#2 - Passed\n");



		printf("TEST#3 - decrease in deck count\n");

		if (testG.deckCount[G.whoseTurn] != (G.deckCount[G.whoseTurn]-3)) {
				printf("ERROR#3 -  deck size did not decrease by 3\n ");
				printf("prior: %d post: %d\n ",G.deckCount[G.whoseTurn], testG.deckCount[G.whoseTurn]);
				error_3_count++;
			}
		else
			printf("TEST#3 - Passed\n");



		printf("TEST#4 - decrease in discard count\n");

		if (testG.discardCount[G.whoseTurn] != G.discardCount[G.whoseTurn]+1) {
				printf("ERROR#4 -  discard count did not increase by 1\n ");
				error_4_count++;
			}
		else
			printf("TEST#4 - Passed\n");


		printf("TEST#5 - discarding of smithy\n");

		if (testG.discard[G.whoseTurn][0] != smithy) {
				printf("ERROR#5 -  discarded cards are not the same: %d and %d\n", testG.discard[G.whoseTurn][0], smithy);
				error_5_count++;
			}
		else
			printf("TEST#5 - Passed\n");

	}

	//print results of testing

	printf("\n\n***************Random Testing Results Summary for smithy card***************\n\n");
	printf("Error 1: %d\n", error_1_count);
	printf("Error 2: %d\n", error_2_count);
	printf("Error 3: %d\n", error_3_count);
	printf("Error 4: %d\n", error_4_count);
	printf("Error 5: %d\n", error_5_count);

	return 0;
}