/*******************************************************************
        Long, Joseph C.
        CS 362, winter 2017
        Assignment 4
 
        randomtestcard2.c
        GREAT HALL Card Test.

The purpose of this test is to pick two gameState variables to randomize during testing.
While randomizing these variables, I want to ensure that the Great Hall card will behave as
expected when running these exams.
 
The Two Variables I decided to randomize are:
    1> numberOfPlayers:  This will randomize the gameState variable numOfPlayers to ensure when the card is played, regardless of the number of players, the Actions will increment appropriately.
 
    2>  discardCount:  I randomized this gameState variable to ensure that when randomized, the number of cards in a players hand will be as expected ( i.e. one played, one gained ).
 
 The end result of this random test would be to ensure that randomizing these two variables 
 will result in the number of actions being apporpriate as well as Hand Count.

********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//deifne maxtests
#define TEST_COUNT 20000000

//Added this function to help me with my testing....
//outputs "press any key to continue"...
void cont()
{
	char ch;
	printf("Press ENTER key to Continue\n");
	scanf("%c", &ch);
}

int main()
{
    
    //Seed rand()
    srand(time(NULL));
    

	//Placeholder to keep tabs on fact a card is drawn when cardEffect is called.
	int smithyCards = 3;

	//Catch variables for drawCard() test.
    int expectedActions = 2;


	int seed = 1000;
	struct gameState preG, postG;
	int discarded = 1;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int numPlayers = 2;
	int thisPlayer = 0;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };
    
    //iterator variable
    int i = 0;


	//Test 1:  Randomly Changing the Player Count in Game State as well as handCount.
	printf("\n         GREAT HALL CARD, Test 1: Action Count\n");
    printf("=======================================================\n");
    printf("This test will ensure that, when randomizing handCount and numPlayers,\n");
    printf("The number of Actions will be incremented appropriately from 1 to 2");


    //Track how many tests pass and fail...
    int firstFailureCount = 0;
    int firstPassedCount = 0;
    
    
    for ( i = 0 ; i < TEST_COUNT ; i++)
    {
        //initialize a game state..
        initializeGame(numPlayers, k, seed, &preG);
        
        //Randomly set player count in gameState
        preG.numPlayers = rand() % 4;
        
        //Randomly set players handcount in gameState
        int hc = preG.handCount[thisPlayer] = rand() % MAX_HAND;

        
        
        //Copy over the initialized game state to test game state...
        memcpy(&postG, &preG, sizeof(struct gameState));
        
        //Calling CardEffect...
        cardEffect(great_hall, choice1, choice2, choice3, &postG, handpos, &bonus);
    
        //Capture Post action count
        int postActions = postG.numActions;
       
        /*
        //printf("HandCount is POST: %d\n", post);
        //printf("ACTIONS is is POST: %d\n", postActions);
        */
        
        //Toggle line output to reduce size of randomtests.out file
        
        /*
        //Expected to have this Number of cards
        printf("Current hand Count: %d\n", pre);
        printf("Expected hand Count: %d\n", post);
         */
        
        //do an assertion check.
        if (postActions == expectedActions)
        {
            //printf("\nPASSED:  Actions Incremented.");
            firstPassedCount++;
        }
        else
        {
            //printf("\nTEST FAILURE.\n");
            firstFailureCount++;
        }
        
    }
    

//    //Announce test...
    printf("\n         GREAT HALL CARD, Test 2: DeckCount\n");
    printf("=======================================================\n");
    printf("Checks to see that handCount on player is as expected based on randomizing discardCount\n");
    int secondFailureCount = 0;
    int secondPassedCount = 0;
    
    for ( i = 0; i < TEST_COUNT ; i++ )
    {
        
        //initialize a game state..
        initializeGame(numPlayers, k, seed, &preG);
        
        //Randomly set discardCount in gameState
        int randDiscard = preG.discardCount[thisPlayer] = rand() % MAX_DECK;
        
        //Copy over the initialized game state to test game state...
        memcpy(&postG, &preG, sizeof(struct gameState));
        
        //Calling CardEffect...
        cardEffect(great_hall, choice1, choice2, choice3, &postG, handpos, &bonus);
        
        int preDeck = preG.handCount[thisPlayer];
        int postDeck = postG.handCount[thisPlayer];
        
        //Toggle line output to reduce size of randomtests.out file
        
        /*
        printf("\n\nTEST 2:  Check Players Hand...\n");
        printf("PreDeck value: %d\n", preDeck);
        printf("PostDeck Value: %d\n", postDeck);
        */

        //Run Assertion Test...
        if (preDeck == postDeck)
        {
            //Toggle line output to reduce size of randomtests.out file
            /*
            printf("DECKCOUNT TEST PASSSED \n");
            printf("PreDeck value: %d\n", preDeck);
            printf("PostDeck Value:       %d\n", postDeck);
            */
            secondPassedCount++;
        }
        else
        {
            //printf("TEST FAILED....\n");
            secondFailureCount++;
        }

    }
    
    printf("\nTest 1 Results(randomized numPlayers: \n");
    printf("=========================================================================\n");
    printf("Number Passed: %d\n Number Failed: %d\n",firstPassedCount, firstFailureCount);
    
    printf("\nTest 2 Results(randomized DeckCount: \n");
    printf("=========================================================================\n");
    printf("Number Passed: %d\n Number Failed: %d\n",secondPassedCount, secondFailureCount);

	return 0;


}


