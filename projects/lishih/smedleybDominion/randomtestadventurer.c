/*
**CS362 Assignment4
**File Name: randomtestadventurer.c
**Random Test for adventurer card
**Shihhui Li
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>


int main (){

	struct gameState game;
	struct gameState gameTest;

	int numPlayer = 2;
	int seed = 1000;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int currentPlayer = 0;
	int otherPlayer =1;
	int k[10] = {adventurer, smithy, village, embargo, minion, mine, cutpurse, sea_hag, tribute, council_room};
	int i;
	time_t t;

	int randomHand = 0;
	int randomDeck = 0;
	int negRandomHand = 0;
	int negRandomDeck = 0;
	int zeroHand = 0;
	int zeroDeck = 0;

	int handPass = 0 ;
	int deckPass = 0;
	int otherHandPass = 0;
	int otherDeckPass = 0;
	int testNumber = 0;

	//initializedd random number generator for test
	srand((unsigned) time(&t));

	//initialize the game , pass to the initializeGame function in dminion c to start the card game
	initializeGame( numPlayer, k, seed, &game);
	printf ("*******Adventurer Card Random Testing**********\n");

    for (i = 0; i <100000; i++) {
	//copy the original game state to the gmaeTest
		memcpy(&gameTest, &game, sizeof (struct gameState));

		//use random generator to generate the cards in hand and deck
		// MAX_HAND = 500, MAX_DECk = 500
		randomHand = rand() % MAX_HAND - 1;
		randomDeck = rand() % MAX_DECK - 1;

		if (randomHand < 0){
			negRandomHand++;
		}
		if (randomDeck < 0){
            negRandomDeck++;
		}

		if (randomHand = 0){
			zeroHand++;
		}
		if (randomDeck = 0){
            zeroDeck++;
		}


	gameTest.handCount [currentPlayer] = randomHand;
	gameTest.deckCount [currentPlayer] = randomHand;

	cardEffect (adventurer, choice1, choice2, choice3, &gameTest, handpos, &bonus);

		if (gameTest.handCount [currentPlayer] == game.handCount [currentPlayer]) {
			handPass++;
		}
		else

		if (gameTest.deckCount [currentPlayer] <= game.deckCount [currentPlayer]) {
			deckPass++;
		}

		if (gameTest.handCount [otherPlayer] == game.handCount [otherPlayer]) {
			otherHandPass++;
		}
		else

		if (gameTest.deckCount [otherPlayer] == game.deckCount [otherPlayer]) {
			otherDeckPass++;
		}
		else
			testNumber++;
	}

        //print test results
        printf("Total test number: %d\n", testNumber);
        printf("Current Player Hand Count Passed: %d\n", handPass);
        printf("Current Player Deck Count passed: %d\n", deckPass);
        printf("Other Player Hand Count Passed: %d\n", otherHandPass);
        printf("Other Player Deck Count passed: %d\n", otherDeckPass);
        printf("Negative Random Hand: %d\n", negRandomHand);
        printf("Negative Deck Hand: %d\n", negRandomDeck);
        printf("zeroHand: %d\n", zeroHand);
        printf("zeroDeck: %d\n", zeroDeck);
	return 0;
}
