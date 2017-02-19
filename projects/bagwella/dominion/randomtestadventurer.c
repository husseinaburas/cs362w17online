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
#define TEST_CARD adventurer
#define NUM_TESTS 20000

//prototype
int countCoins(struct gameState*, int);

int main(){
	
	srand(time(NULL));
	struct gameState G, testG;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int testcase, player, numPlayers, seed, testNum = 0, alreadyChosen, kcard, handPos, cardAcquired, coinsCounted, returnedVal, k_card_counter;
	int error_1_count = 0, error_2_count = 0, error_3_count = 0, error_4_count= 0, error_5_count = 0, error_6_count = 0, error_7_count = 0, error_8_count = 0;
	int kingdom_cards[10], supply[17];
	

	printf("\n\n***************Begin Random Testing for Adventurer card***************\n\n");

	for(testcase = 0; testcase < NUM_TESTS; testcase++){
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
		printf("------Test#%d Adventurer Card--------\n", testNum);

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
	        

		printf("Before playing adventurer: player = %d; deck count = %d; discard count = %d; hand count = %d\n", player+1, testG.deckCount[player], testG.discardCount[player], testG.handCount[player]);
		printf("Playing now....\n");

		memcpy(&G, &testG, sizeof(struct gameState));

		
		printf("TEST#1 - CardEffect return\n");
		fflush(stdout);
	
		//play card and check for error	
		returnedVal = cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);
		printf("returnedVal = %d\n",returnedVal);
		if (returnedVal != 0) {
			error_1_count++;
			printf("ERROR#1 - CardEffect returned improperly.\n");
		}
		else
			printf("TEST#1 - Passed\n");

		coinsCounted = countCoins(&G, G.whoseTurn);
		printf("TEST#2 - changes in handCount\n");

		//If player has 2 or more coins, check if handCount increased by 1 
		if (coinsCounted >= 2) {
			//if there is an error, log in the error array and increment the error counter 
			if (testG.handCount[G.whoseTurn] != G.handCount[G.whoseTurn] + 1) {
				printf("ERROR#2 - player's hand size did not increase by 1.\n");
				printf("ERROR#2- coinsCounted returned: %d\n", coinsCounted);
				error_2_count++;
			}
			else
				printf("TEST#2 - Passed\n");
		}


				//Check that current player handCount remained the same when player has 1 coin combined in deck and discard
		else if (coinsCounted == 1) {
			if (testG.handCount[G.whoseTurn] != G.handCount[G.whoseTurn]) {
				
				printf("ERROR#2 - player's hand size did not remain the same.\n");
				printf("ERROR#2- coinsCounted returned: %d\n", coinsCounted);
				error_2_count++;
			}
			else
				printf("TEST#2 - Passed\n");
		}
		
		else {
			if (testG.handCount[G.whoseTurn] != G.handCount[G.whoseTurn]-1) {
				printf("ERROR#2 - player's hand size did not decrease by 1\n ");
				printf("ERROR#2- coinsCounted returned: %d\n", coinsCounted);
				error_2_count++;
			}
			else
				printf("TEST#2 - Passed\n");
		}
	

		printf("TEST#3 - adventurer card added to playedCard pile\n");
		
		//Check that adventurer card added to played pile 
		if  (testG.playedCards[G.playedCardCount] != adventurer) {
			printf("ERROR#3 - adventurer card not added to the played card pile\n");
			error_3_count++;
		}

		printf("TEST#4 - adventurer card count increment\n");

		//Check if played card count did not increment
		if  (testG.playedCardCount != G.playedCardCount + 1) {
			printf("ERROR#4 - The played card count did not increment.\n");
			error_4_count++;
		}

		cardAcquired = testG.hand[G.whoseTurn][testG.handCount[G.whoseTurn]-2];

		printf("TEST#5 cards added to hand were coins - \n");

		//Check that acquired cards are indeed coins
		if ((cardAcquired != gold) && (cardAcquired != silver) && (cardAcquired != copper)) {
			//check if had 2 or more coins in deck and discard piles combined
			if (coinsCounted >= 2) { 
				printf("ERROR#5 - the cards added to the player's hand were not coins.\n");
				printf("ERROR#5- coinsCounted returned: %d\n", coinsCounted);
				error_5_count++;
			}
		}
		else { 
			//check second card drawn
			cardAcquired = testG.hand[G.whoseTurn][G.handCount[G.whoseTurn]-1];
			if ((cardAcquired != gold) && (cardAcquired != silver) && (cardAcquired != copper)) {
				//if failed check if 2 or more coins in deck and discard piles combined
				if (coinsCounted >= 1) { //if only 0 coins to draw, then not an error
					printf("ERROR#5 - the cards added to the player's hand were not coins.\n");
					printf("ERROR#5- coinsCounted returned: %d\n", coinsCounted);
					error_5_count++;
				}
			}
		}
		//Check that other player's deckCount, handCount, and discardCount were not changed
		for (int i = 0; i < numPlayers; i++) {
			
			if (i != G.whoseTurn) {
				printf("TEST#6\n");
				if (testG.deckCount[i] != G.deckCount[i]) {

					printf("ERROR5 - another player's deck size changed.\n");
					error_6_count++;

				}

				else
					printf("TEST#6 - Passed\n");
				
				printf("TEST#7\n");
				if (testG.handCount[i] != G.handCount[i]) {

					printf("ERROR6 - another player's hand size changed.\n");
					error_7_count++;

				}

				else
					printf("TEST#7 - Passed\n");

				printf("TEST#8\n");
				if (testG.discardCount[i] != G.discardCount[i]) {

					printf("ERROR#8 - another player's discard pile size changed.\n");
					error_8_count++;

				}

				else
					printf("TEST#8 - Passed\n");
	
			}
		}

		printf("\n");	
	
	}
		
	//print results of testing

	printf("\n\n***************Random Testing Results Summary for Adventurer card***************\n\n");
	printf("Error 1: %d\n", error_1_count);
	printf("Error 2: %d\n", error_2_count);
	printf("Error 3: %d\n", error_3_count);
	printf("Error 4: %d\n", error_4_count);
	printf("Error 5: %d\n", error_5_count);
	printf("Error 6: %d\n", error_6_count);
	printf("Error 7: %d\n", error_7_count);
	printf("Error 8: %d\n", error_8_count);


	return 0;
}

//function returns the number of coins combined in the player's deck and discard piles.

int countCoins(struct gameState *game, int player) {
	int coinCount = 0;

	//count coins in deck
	
	for (int i = 0; i < game->deckCount[player]; i++) {
		if ((game->deck[player][i] == copper) || (game->deck[player][i] == silver) || (game->deck[player][i] == gold)) {
			coinCount += 1; 
		}
		
	}

	//count coins that were discarded 

	for (int i = 0; i < game->discardCount[player]; i++) {
		if ((game->discard[player][i] == copper) || (game->discard[player][i] == silver) || (game->discard[player][i] == gold)) {
			coinCount += 1;
	}
		
	}
	return coinCount;
}

