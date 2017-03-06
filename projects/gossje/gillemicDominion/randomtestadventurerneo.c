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
		printf("usage: randomtestadventurer [integer]\n");
		exit(1);
	}

	int handPos;
	int handCount;
	int num_act;
	int deckCount;
	int playedCards;
	int player;
	int preTreasure_hand;
	int postTreasure_hand;
	int preTreasure_deck;
	int postTreasure_deck;
	int card; 
	int numCycles = 5000;
	int randomSeed = atoi(argv[1]);
	int k[10] = {adventurer, embargo, village, gardens, feast, smithy,
				 sea_hag, tribute, mine, council_room};
	struct gameState game;
	printf("Random Testing Adventurer\n");
	int tests_passed = 0;
	int i;
	int num_failed = 0;
	int temphand[MAXHAND];

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
		preTreasure_deck = 0;
		preTreasure_hand = 0;
		
		int j;
		
		for (j = 0; j < game.deckCount[player]; j++){ //loop through deck
			card = game.deck[player][j]; //get card in deck
			if (card == copper || card == silver || card == gold){ //if card is a treasure
				preTreasure_deck++; //increment 
			}
		}
		
		for (j = 0; j < game.handCount[player]; j++){ //loop through cards in hand 
			card = game.hand[player][j];
			if (card == copper || card == silver || card == gold){
				preTreasure_hand++;
			}
		}
		
		int pre_advent_hand = game.handCount[player];
		int pre_advent_deck = game.deckCount[player];
		int pre_advent_action = game.numActions; 
		int pre_advent_played = game.playedCardCount; 

		int t1 = playAdventurer(&game, player, 0, 0, temphand, 0);
		
		//get post adventurer values
		postTreasure_deck = 0;
		postTreasure_hand = 0;
		
		int k;
		
		for (k = 0; k < game.deckCount[player]; k++){ //loop through deck
			card = game.deck[player][k]; //get card in deck
			if (card == copper || card == silver || card == gold){ //if card is a treasure
				postTreasure_deck++; //increment 
			}
		}
		
		for (k = 0; k < game.handCount[player]; k++){ //loop through cards in hand 
			card = game.hand[player][k];
			if (card == copper || card == silver || card == gold){
				postTreasure_hand++;
			}
		}
		
		if (t1 != 0){ //function didnt return proper value 
		tests_passed = 1;
		num_failed += 1;
		}
		
		if (game.handCount[player] != pre_advent_hand + 1){ //player plays adventurer (-1) and draws 2 (+2). Net total +1.
			tests_passed = 1;
			num_failed += 1;
		}
		
		if (game.numActions != pre_advent_action){ //number of actions changed when it shouldn't have
			tests_passed = 1;
			num_failed += 1;
		}
		
		//need at least 2 treasures in deck for this test
		if (preTreasure_deck >= 2 && postTreasure_deck != preTreasure_deck - 2){ //did not draw from deck a proper number of treasures from deck
			tests_passed = 1;
			num_failed += 1;
		}
		
		//need at least 2 treasures in deck for this test. 
		if (preTreasure_deck >= 2 && postTreasure_hand != preTreasure_hand + 2){ //2 treasures not added to hand
			tests_passed = 1;
			num_failed += 1;
		}
		
		//1 treasure in deck case
		if (preTreasure_deck == 1 && postTreasure_deck != preTreasure_deck - 1){ //did not draw from deck a proper number of treasures from deck
			tests_passed = 1;
			num_failed += 1;
		}
		
		//1 treasure in deck case
		if (preTreasure_deck == 1 && postTreasure_hand != preTreasure_hand + 1){ //1 treasure not added to hand
			tests_passed = 1;
			num_failed += 1;
		}
		
		//0 treasure in deck case 
		if (preTreasure_deck == 0 && postTreasure_deck != preTreasure_deck){ //treasures somehow added to deck 
			tests_passed = 1;
			num_failed += 1;
		}
		
		//0 treasure in deck case
		if (preTreasure_deck == 0 && postTreasure_hand != preTreasure_hand){ //treasures somehow added to hand 
			tests_passed = 1;
			num_failed += 1;
		}
		
		if (preTreasure_deck >= 2 && pre_advent_hand != game.handCount[player] - 2){ //more than just treasure added to hand 
			tests_passed = 1;
			num_failed += 1;
		}
		
		if (preTreasure_deck == 1 && pre_advent_hand != game.handCount[player] - 1){ //more than just treasure added to hand 
			tests_passed = 1;
			num_failed += 1;
		}	
		
		if (preTreasure_deck == 0 && pre_advent_hand != game.handCount){ //more than just treasure added to hand 
			tests_passed = 1;
			num_failed += 1;
		}		
		

	}
	
	if (tests_passed != 0){
		printf("TEST FAILED.\n");
		int total_tests = i * 12;
		printf("There were %d value checks. %d of them failed\n", total_tests, num_failed);
		
	}
	
	else{
		printf("TEST PASSED\n");
	}

	return 0;
}