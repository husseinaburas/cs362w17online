/* -----------------------------------------------------------------------
 * Test of Smithy card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



//custom assert function
int assertTrue(int input1, int input2)
{
	if(input1 == input2)
	{
		return 1;
	}
	
	else
		return 0;
}


	
int main()
{
	int numberTests = 1;
    int i, z, j;
    int seed = 1000;

    int numPlayers;
	int temp;
	int smithyPos;
	int numberMin, numberMax;
	int testNumber =0;
	int flag1;
	
	//create arrays to store player states
	int originalHandCount[MAX_PLAYERS];
	int originalDiscardCount[MAX_PLAYERS];
	int originalDeckCount[MAX_PLAYERS];
	int originalHand[MAX_PLAYERS][MAX_HAND];
	int originalDeck[MAX_PLAYERS][MAX_DECK];
	int originalDiscard[MAX_PLAYERS][MAX_DECK];
	
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState testGameState;
	
	int currentPlayer; 

	srand(time(NULL));

    printf ("TESTING playSmithy():\n");


	for( i = 1; i <= numberTests; i++)
	{
		testNumber++;
		
		temp = 0;
		numberMin = 2;
		numberMax = MAX_PLAYERS;
		
		//generate random number for # players
		numPlayers = numberMin+(rand() % (numberMax-numberMin + 1 ));	
		
		//intialize game
		temp = initializeGame(numPlayers, k, seed, &testGameState); // initialize a new game

		//if initialize game didn't return error
		if(temp != -1)
		{
			numberMin = 0;
			numberMax = (testGameState.handCount[0] - 1);
			
			//generate random number for where in hand of player 0 Smithy goes
			smithyPos = numberMin+(rand() % (numberMax-numberMin + 1 ));
			
			//replace card in hand with smithy card
			testGameState.hand[0][smithyPos] = smithy;
			
			//store player states
			for(z = 0; z < numPlayers; z++)
			{	
				originalHandCount[z] = testGameState.handCount[z];
				originalDiscardCount[z] = testGameState.discardCount[z];
				originalDeckCount[z] = testGameState.deckCount[z];
				
				//store cards to original arrays
				for(j = 0; j < MAX_HAND; j++)
				{
					originalHand[z][j] = testGameState.hand[z][j];
				}
				
				for(j = 0; j < MAX_DECK; j++)
				{
					originalDeck[z][j] = testGameState.deck[z][j];
				}					
				
				for(j = 0; j < MAX_DECK; j++)
				{
					originalDiscard[z][j] = testGameState.discard[z][j];
				}						
			}

			currentPlayer = testGameState.whoseTurn;		
			
			//call playSmithy
			playSmithy(smithyPos, currentPlayer, &testGameState);


			
			
			
			
			
/***********************************************************************************/			
			//test that player hand counts are unaffected	
			flag1 = 0;
			for(z = 1; z < numPlayers; z++)
			{	
				if((assertTrue(originalHandCount[z], testGameState.handCount[z])) != 1)
				{
					flag1 = 1;	
				}	
			}
			
			if(flag1 != 1)
			{
				printf("Test# %d - Player Hand Counts Unaffected - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Player Hand Counts Unaffected - FAIL\n", testNumber);
			}	


			
			
			
			
/***********************************************************************************/			
			//test that player discard counts are unaffected	
			flag1 = 0;
			for(z = 1; z < numPlayers; z++)
			{	
				if((assertTrue(originalDiscardCount[z], testGameState.discardCount[z])) != 1)
				{
					flag1 = 1;	
				}	
			}
			
			if(flag1 != 1)
			{
				printf("Test# %d - Player Discard Counts Unaffected - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Player Discard Counts Unaffected - FAIL\n", testNumber);
			}	
		

		
		
		
		
		
/***********************************************************************************/			
			//test that player deck counts are unaffected	
			flag1 = 0;
			for(z = 1; z < numPlayers; z++)
			{	
				if((assertTrue(originalDeckCount[z], testGameState.deckCount[z])) != 1)
				{
					flag1 = 1;	
				}	
			}
			
			if(flag1 != 1)
			{
				printf("Test# %d - Player Deck Counts Unaffected - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Player Deck Counts Unaffected - FAIL\n", testNumber);
			}		
			




/***********************************************************************************/			
			//test that players hands are unaffected	
			flag1 = 0;
			
			for(z = 1; z < MAX_PLAYERS; z++)
			{
				for(j = 0; j < MAX_HAND; j++)
				{
					if(assertTrue(originalHand[z][j], testGameState.hand[z][j]) != 1)
					{
						flag1 = 1;
					}
				}
			}
			
			if(flag1 != 1)
			{
				printf("Test# %d - Player Hand Contents Unaffected - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Player Hand Contents Unaffected - FAIL\n", testNumber);
			}			


/***********************************************************************************/			
			//test that players decks are unaffected	
			flag1 = 0;
			
			for(z = 1; z < MAX_PLAYERS; z++)
			{
				for(j = 0; j < MAX_DECK; j++)
				{
					if(assertTrue(originalDeck[z][j], testGameState.deck[z][j]) != 1)
					{
						flag1 = 1;
					}
				}
			}
			
			if(flag1 != 1)
			{
				printf("Test# %d - Player Deck Contents Unaffected - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Player Deck Contents Unaffected - FAIL\n", testNumber);
			}

			
			
			
/***********************************************************************************/			
			//test that players discards are unaffected	
			flag1 = 0;
			
			for(z = 1; z < MAX_PLAYERS; z++)
			{
				for(j = 0; j < MAX_DECK; j++)
				{
					if(assertTrue(originalDiscard[z][j], testGameState.discard[z][j]) != 1)
					{
						flag1 = 1;
					}
				}
			}
			
			if(flag1 != 1)
			{
				printf("Test# %d - Player Discard Contents Unaffected - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Player Discard Contents Unaffected - FAIL\n", testNumber);
			}			
			
			
			
			
			
			

/***********************************************************************************/			
			//test that player who played smithy has proper hand count	
			flag1 = 0;
			
			//add 2 to original handcount (discard smithy, draw 3)
			if((assertTrue(originalHandCount[0]+2, testGameState.handCount[0])) != 1)
			{
				flag1 = 1;	
			}

			if(flag1 != 1)
			{
				printf("Test# %d - Whoseturn Player Hand Count - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Whoseturn Player Hand Count - FAIL\n", testNumber);
			}



/***********************************************************************************/			
			//test that player who played smithy has proper deck count	
			flag1 = 0;
			
			//subtract 3 from original deck count for 3 cards drawn
			if((assertTrue(originalDeckCount[0]-3, testGameState.deckCount[0])) != 1)
			{
				flag1 = 1;	
			}

			if(flag1 != 1)
			{
				printf("Test# %d - Whoseturn Player Deck Count - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Whoseturn Player Deck Count - FAIL\n", testNumber);
			}


			
			
/***********************************************************************************/			
			//test that player who played smithy has proper discard count	
			flag1 = 0;
			
			//add 1 to original discard count for discarded smithy
			if((assertTrue(originalDiscardCount[0]-3, testGameState.discardCount[0])) != 1)
			{
				flag1 = 1;	
			}

			if(flag1 != 1)
			{
				printf("Test# %d - Whoseturn Player Discard Count - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Whoseturn Player Discard Count - FAIL\n", testNumber);
			}			
			
			
			
			
			
/***********************************************************************************/			
			//test that player who played smithy no longer has smithy in hand
			flag1 = 0;
			
			for(z = 0; z < MAX_HAND; z++)
			{
				if(testGameState.hand[0][z] == smithy)
				{
					flag1 = 1;
				}
			}

			if(flag1 != 1)
			{
				printf("Test# %d - Whoseturn Player Hand does not contain smithy post-play - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Whoseturn Player Hand does not contain smithy post-play - FAIL\n", testNumber);
			}			
			
			
		}
		
		
		else
		{
			printf("Test# %d - Game Initiation Error - FAIL\n", testNumber);
		}
			
	

		//clear game state
		memset(&testGameState, 23, sizeof(struct gameState)); 

		//reset temp arrays
		memset(originalHandCount, 23, sizeof(originalHandCount));
		memset(originalDiscardCount, 23, sizeof(originalDiscardCount));
		memset(originalDeckCount, 23, sizeof(originalDeckCount));
		memset(originalHand, 23, sizeof(originalHand));
		memset(originalDeck, 23, sizeof(originalDeck));
		memset(originalDiscard, 23, sizeof(originalDiscard));
	}
		

	return 0;
}



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

