/*******************************************************************
  randomtestcard1.c
  ADVENTURER Card Test.
 
  This test will test the following conditions 
    1>
 
 
 
 rand1:   randomtestcard1
	./randomtestcard3 &> rand1.out
	gcov -bf dominion.c >> rand1.out
	cat dominion.c.gcov >> rand1.out

 ********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


#define TEST_COUNT 2000000

//Added this function to help me with my testing....
//outputs "press any key to continue"...
void cont()
{
    char ch;
    printf("Press ENTER key to Continue\n");
    scanf("%c",&ch);
}

int main()

{

    //seed rand()
    srand(time(NULL));
    
    //expected difference of 2 between pre and post hand counts
    int expectedDiff = 2;

    //Game State Variables...
	int seed = 1000;
	struct gameState preG, postG;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    
    
    
	int numPlayers = 2;
	int thisPlayer = 0;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

    
   
    //iterator variable i
    int i = 0;
    
    //counters for passed and failed tests.
    int passed = 0;
    int failed = 0;
    
    
    
    //generate randon values for gamestate...
    
//    /*
//    struct gameState {
//        int numPlayers; //number of players
//        int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
//        int embargoTokens[treasure_map+1];
//        int outpostPlayed;
//        int outpostTurn;
//        int whoseTurn;
//        int phase;
//        int numActions; /* Starts at 1 each turn */
//        int coins; /* Use as you see fit! */
//        int numBuys; /* Starts at 1 each turn */
//        int hand[MAX_PLAYERS][MAX_HAND];
//        int handCount[MAX_PLAYERS];
//        int deck[MAX_PLAYERS][MAX_DECK];
//        int deckCount[MAX_PLAYERS];
//        int discard[MAX_PLAYERS][MAX_DECK];
//        int discardCount[MAX_PLAYERS];
//        int playedCards[MAX_DECK];
//        int playedCardCount;
//    */
    
    
    
   
    
    
//	//Announce test...
//	printf("      ADVENTURER CARD TEST\n");
//    printf("=================================================\n");
//
//    for ( i = 0 ; i < TEST_COUNT ; i++ )
//    {
//        
//    
//        // initialize a game state and player cards
//        printf("Initializing Game State...\n\n");
//        initializeGame(numPlayers, k, seed, &preG);
//        
//        
//        //Max players can be 4, generates number bet 0 and 3.
//        preG.numPlayers = rand() % 4;
//        preG.discardCount = rand() % MAX_PLAYERS;
//
//
//        //Copy over the initialized game state to test game state...
//        memcpy(&postG, &preG, sizeof(struct gameState));
//        
//        //Calling CardEffect...
//        cardEffect(adventurer, choice1, choice2, choice3, &postG, handpos, &bonus);
//        
//    }


    //********************* HANDCOUNT TEST ************************************
    printf("\n     ADVENTURER CARD: TEST ONE, HANDCOUNT INTEGRITY\n");
    printf("===============================================================");
    for ( i = 0 ; i < TEST_COUNT ; i++)
    {
        
        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &preG);
        
        
        //Randomize gameState Variables....
        preG.numPlayers = rand() % 4;
        preG.discardCount[thisPlayer] = rand() % MAX_DECK;
        
        
        //Copy over the initialized game state to test game state...
        memcpy(&postG, &preG, sizeof(struct gameState));
        
        //Calling CardEffect...
        cardEffect(adventurer, choice1, choice2, choice3, &postG, handpos, &bonus);
        
        
        //Capture pre and post handcount values for comparison
        int preHand  = preG.handCount[thisPlayer];
        int postHand = postG.handCount[thisPlayer];
        
        
        if ( (postHand - preHand ) == expectedDiff )
        {
            passed++;
            //Toggle output code for ease of reading...
            /*
            printf("TEST PASSED:  \n");
            printf("----------------------------------------\n");
            printf("(PRE)HAND count: %d\n", preHand);
            printf("(POST)HAND count: %d\n", postHand);
            printf("Expected difference of two ( 2 ) upward between pre and post.\n");
             */
        }
        else
        {
            failed++;
            /*
            printf("TEST FAILED ( PRE/POST HAND COUNT NOT WITHIN PARAMETERS:  \n");
            printf("----------------------------------------\n");
            printf("(PRE)HAND count: %d\n", preHand);
            printf("(POST)HAND count: %d\n", postHand);
             */
        }
    
    }
    
    printf("\nTest 1 Results(randomized numPlayers: \n");
    printf("=========================================================================\n");
    printf("Number Passed: %d\n Number Failed: %d\n",passed, failed);

    //********************* DECKCOUNT TEST ************************************
    printf("\n     ADVENTURER CARD: TEST ONE, DECKCOUNT INTEGRITY\n");
    printf("===============================================================");
    
    //reset counters for failed/passed
    failed = 0;
    passed = 0;
    
    for ( i = 0 ; i < TEST_COUNT ; i++)
    {
       
        int preDeck = preG.deckCount[thisPlayer];
        int postDeck = postG.deckCount[thisPlayer];
        
        if ( (preDeck - postDeck) == expectedDiff  )
        {
            passed++;
            /*     turn off comments for ease of reading
            printf("TEST PASSED:  \n");
            printf("----------------------------------------\n");
            printf("preDeck: %d\n", preDeck);
            printf("postDeck: %d\n", postDeck);
             */
        }
        else
        {
            failed++;
            /*     Turn off comments for ease of reading...
            printf("TEST FAILED:  \n");
            printf("----------------------------------------\n");
            printf("preDeck: %d\n", preDeck);
            printf("postDeck: %d\n", postDeck);
             */
        }
    }
    
    printf("\nTest 2 Results(randomized DeckCount: \n");
    printf("=========================================================================\n");
    printf("Number Passed: %d\n Number Failed: %d\n",passed, failed);


	return 0;
    
  
}


