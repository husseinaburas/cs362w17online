#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include <string.h>


#define MAXDECK 20
#define MAXHAND 20
#define MAXACT 5
#define MAXPLAYER 4


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("usage: randomtestcard2 [integer]\n");
		exit(1);
	}

	int handPos;
	int handCount;
	int num_act;
	int deckCount;
	int playedCards;
	int player;
	int numCycles = 5000;
	int randomSeed = atoi(argv[1]);
	int k[10] = {adventurer, embargo, village, gardens, feast, smithy,
				 sea_hag, tribute, mine, council_room};
	struct gameState game;
	printf("Random Testing Smithy\n");
	int tests_passed = 0;
	int i;
	int num_failed = 0;
	for (i = 0; i < numCycles; i++) //5000 random tests 
	{
		int g = initializeGame(MAXPLAYER, k, randomSeed, &game); // initialize a new game
		player = (rand() % MAXPLAYER); //randomly select value for player 
		handCount = (rand() % MAXHAND) + 1; //randomly determine handCount
		deckCount =(rand() % MAXDECK) + 1;	//randomly determine size of deck 
		num_act = (rand() % MAXACT) + 1; //randomly set number of actions 
		handPos = (rand() % handCount); //randomly set hand position of card
		playedCards = (rand() % 20); //randomly set number of played cards from 0 to 20 
		game.handCount[player] = handCount;
		game.deckCount[player] = deckCount;
		game.numActions = num_act;
		game.whoseTurn = player;
		game.playedCardCount = playedCards;
		
		//get values of relevant items before tests 
		int pre_smithy_hand = game.handCount[player];
		int pre_smithy_deck = game.deckCount[player];
		int pre_smithy_action = game.numActions; 
		int pre_smithy_played = game.playedCardCount; 

		int t1 = playSmithy(&game, handPos);
		
		if (t1 != 0){ //function didnt return proper value 
		tests_passed = 1;
		num_failed += 1;
		}
		
		if (game.handCount[player] != pre_smithy_hand + 2){ //player plays smithy (-1) and draws 3 (+3). Net total +2.
			tests_passed = 1;
			num_failed += 1;
		}
		
		if (game.numActions != pre_smithy_action){ //number of actions changed when it shouldn't have
			tests_passed = 1;
			num_failed += 1;
		}
		
		if (game.deckCount[player] != pre_smithy_deck - 3){ //did not draw from deck a proper number of cards
			tests_passed = 1;
			num_failed += 1;
		}
		
		if (game.playedCardCount != pre_smithy_played + 1){ //smithy not properly discarded
			tests_passed = 1;
			num_failed += 1;
		}

	}
	
	if (tests_passed != 0){
		printf("TEST FAILED.\n");
		int total_tests = i * 5;
		printf("There were %d value checks. %d of them failed\n", total_tests, num_failed);
		
	}
	
	else{
		printf("TEST PASSED\n");
	}

	return 0;
}
