//randomtestcard2.c
// testing the steward card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(argc, argv){


	srand(time(NULL)); //seed random with the seed given on command line
	
	int test_deck_size;
	int test_hand_size;
	
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
	
	for (i=0; i<test_hand_size; i++){
	
       		 drawCard(whoseturn, testGame);
	}

	int choice =  rand()%3;
	steward_func(whoseturn, testGame, choice, 1,2);

	int testfail=0;

	if (testGame ->handCount[whoseturn] !=2  && choice == 1)
	{
		testfail++;
		printf("steward draw issue");
	}

	if(testGame ->coins != 2 && choice == 2)
	{
		testfail++;
		printf("steward coin issue");
	}
	
	if(testGame -> handCount[whoseturn] != test_hand_size - 3 && choice == 0)
	{
		testfail++;
		printf("steward trash issue");
	}
		
	if (testfail ==0){printf("steward test passed");}

}
