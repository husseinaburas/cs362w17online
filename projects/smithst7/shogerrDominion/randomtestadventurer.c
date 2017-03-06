//randomtestadventurer.c
// testing the adventurer card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "dominion.c"
#include "rngs.c"

int main(argc, argv){


	srand(time(NULL)); //seed random with the seed given on command line
	
	int test_deck_size;
	int test_hand_size;

	int repeat;
	int repeats;
	repeats = 100;
	
	for (repeat=0; repeat < repeats; repeat++){
	test_deck_size = rand()%60 + 10;
	//a player's hand should be five cards for most of the time,
	//however, it is feasible that he or she would have anywhere from 
	//zero to fifteen cards during their turn depending on previous cards played 
	test_hand_size = rand()%16;
	
	struct gameState* testGame = newGame();

	//fill a randomly sized deck with random cards	
        int testcards[test_deck_size];
        int i;
        for (i=0;i<test_deck_size;i++){

                testcards[i] = rand()%27;
        }

	int players = rand()%6+1;

        initializeGame(players, testcards, 5, testGame);

	int whoseturn = rand()%players;
	testGame->whoseTurn = whoseturn;
	
	for (i=0; i<test_hand_size; i++){
	
       		 drawCard(whoseturn, testGame);
	}

	playAdventurer(testGame);

	if (testGame->handCount[whoseturn] > test_hand_size+2)
	{
		printf("adventurer draw issue");
	}
	else printf("adventurer test passed");

	}

}
