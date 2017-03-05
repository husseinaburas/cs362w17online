/*******************************************************************
        Long, Joseph C.
        CS 362, winter 2017
        Assignment 4
 
        randomtestcard2.c
        SMITHY Card Test.

The purpose of this test is to pick two gameState variables to randomize during testing.
While randomizing these variables, I want to ensure that the smithy card will behave as 
expected when running these exams.
 
The Two Variables I decided to randomize are:
    1> numberOfPlayers
    2> discardPile

********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//deifne maxtests
#define TEST_COUNT 200


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
	int expectedDeckCount = 0;
	int actualDeckCount = 0;

	//captures deckCounts
	int preDeck = 0;
	int postDeck = 0;

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


	//Announce test...
	printf("\n         RandomCard Test1: SMITHY CARD\n");
    printf("=======================================================\n");
    //Test 1:  Randomly Changing the Player Count in Game State
    printf("This test will ensure that, when randomizing playerCount\n");
    printf("The hand count does not fall outside of expected paramenters");


    //Track how many tests pass and fail...
    int firstFailureCount = 0;
    int firstPassedCount = 0;
    
    
    for ( i = 0 ; i < TEST_COUNT ; i++)
    {
        //initialize a game state..
        initializeGame(numPlayers, k, seed, &preG);
        
        //Randomly set player count in gameState
        preG.numPlayers = rand() % 4;
        
        //Copy over the initialized game state to test game state...
        memcpy(&postG, &preG, sizeof(struct gameState));
        
        //Calling CardEffect...
        cardEffect(smithy, choice1, choice2, choice3, &postG, handpos, &bonus);
    
        //Capture Pre and Post Hand Count
        int pre = preG.handCount[thisPlayer] - discarded + smithyCards;
        int post = postG.handCount[thisPlayer];
        
        //Toggle line output to reduce size of randomtests.out file
        
        /*
        //Expected to have this Number of cards
        printf("Current hand Count: %d\n", pre);
        printf("Expected hand Count: %d\n", post);
         */
        
        //do an assertion check.
        if (pre == post)
        {
            //printf("\nPASSED:  THREE Cards added");
            firstPassedCount++;
        }
        else
        {
            //printf("\nTEST FAILURE.\n");
            firstFailureCount++;
        }
        
    }
    
    
    

    //Announce test...
    printf("\n         RandomCard Test2: SMITHY CARD\n");
    printf("=======================================================\n");
    //Test 1:  Randomly Changing the Player Count in Game State
    printf("This test will ensure that, when randomizing discardPile\n");
    printf("The discardPile does not fall outside of expected paramenters.\n");
    //Track how many tests pass and fail...
    int secondFailureCount = 0;
    int secondPassedCount = 0;
    
    for ( i = 0; i < TEST_COUNT ; i++ )
    {
        
        //initialize a game state..
        initializeGame(numPlayers, k, seed, &preG);
        
        //Randomly set discardCount in gameState
        int randDiscard = preG.discardCount[thisPlayer] = rand() % MAX_DECK;
        //printf("randDiscard is: %d\n", randDiscard);
        
        
        //Copy over the initialized game state to test game state...
        memcpy(&postG, &preG, sizeof(struct gameState));
        
        //Calling CardEffect...
        cardEffect(smithy, choice1, choice2, choice3, &postG, handpos, &bonus);
        
        
        preDeck = preG.deckCount[thisPlayer] - smithyCards;
        postDeck = postG.deckCount[thisPlayer];
        
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
            printf("PreDeck value less 3: %d\n", preDeck);
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


