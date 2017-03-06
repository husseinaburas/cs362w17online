/* -----------------------------------------------------------------------
 * Test of Adventurer card
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
	int numberTests = 50;
    int i, z, j;
    int seed = 1000;

    int numPlayers;
	int temp;
	int advPos;
	int randomDeckSize;
	int numberMin, numberMax;
	int testNumber =0;
	int numberTreasures;
	int treasurePos;
	int treasureType;
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
	
	

	srand(time(NULL));

    printf ("TESTING playAdventurer():\n");

	for( i = 1; i < numberTests; i++)
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
			int currentPlayer = testGameState.whoseTurn;
			int drawnTreasure=0;
			int cardDrawn;
			int temphand[MAX_HAND];
			int t = 0;
			
			//initialize player 0's cards in hand to all curses for control purposes
			for(z= 0; z <= testGameState.handCount[0]; z++)
			{
				testGameState.hand[0][z] = curse;
			}
			
			
			//clear player's 0's deck to set up controlled deck
			for(z= 0; z < testGameState.deckCount[0]; z++)
			{
				testGameState.deck[0][z] = NULL;
			}			
			
			testGameState.deckCount[0] = 0;
			
			//generate random number for how large player's deck is	
			numberMin = 0;
			numberMax = 20;
			
			randomDeckSize = numberMin+(rand() % (numberMax-numberMin + 1 ));
			

			//initialize player 0's cards in deck to all curses for control purposes
			for(z= 0; z < randomDeckSize; z++)
			{
				testGameState.deck[0][z] = curse;
				testGameState.deckCount[0]++;
			}			
					
			//generate random number for where in hand of player 0 Adventurer goes			
			numberMin = 0;
			numberMax = (testGameState.handCount[0] - 1);
			
			advPos = numberMin+(rand() % (numberMax-numberMin + 1 ));
			
			//replace card in hand with adventurer card
			testGameState.hand[0][advPos] = adventurer;
	
	
			//generate random number for number of treasure cards in deck		
			numberMin = 0;
			numberMax = (testGameState.deckCount[0]);
			
			numberTreasures = numberMin+(rand() % (numberMax-numberMin + 1 ));			
			
			z=0;
			
			while(z < numberTreasures)
			{
				//generate random number for position of deck to put treasures	
				numberMin = 0;
				numberMax = (testGameState.deckCount[0]-1);
			
				treasurePos = numberMin+(rand() % (numberMax-numberMin + 1 ));

				//generate random selection of treasure type enumerated int values	
				numberMin = 1;
				numberMax = 3;
			
				treasureType = numberMin+(rand() % (numberMax-numberMin + 1 ));
				
				//if treasure position doesn't randomly get assigned to where treasure already is
				if((testGameState.deck[0][treasurePos] != copper) && (testGameState.deck[0][treasurePos] != gold) && (testGameState.deck[0][treasurePos] != silver))
				{
					if(treasureType == 1)
						testGameState.deck[0][treasurePos] = copper;

					if(treasureType == 2)
						testGameState.deck[0][treasurePos] = silver;

					if(treasureType == 3)
						testGameState.deck[0][treasurePos] = gold;
					
					z++;
				}
			}
			
	
			//generate random number for number of treasure cards in discard	
				
			//make sure at least one treasure is in deck and/or discard
			//check to see how many got allocated to deck
			if(numberTreasures > 0)
			{
				numberMin = 0;
			}
			
			else
				numberMin = 1;
			
			numberMax = 5;
			
			numberTreasures = numberMin+(rand() % (numberMax-numberMin + 1 ));			
			

			for(z=0; z < numberTreasures; z++)
			{			

				//generate random selection of treasure type enumerated int values	
				numberMin = 1;
				numberMax = 3;
			
				treasureType = numberMin+(rand() % (numberMax-numberMin + 1 ));
				
				if(treasureType == 1)
					testGameState.discard[0][(testGameState.discardCount[0])] = copper;

				if(treasureType == 2)
					testGameState.discard[0][(testGameState.discardCount[0])] = silver;

				if(treasureType == 3)
					testGameState.discard[0][(testGameState.discardCount[0])] = gold;				
								
				testGameState.discardCount[0]++;

			}	
	
		
			
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

			
			//call playAdventurer
			playAdventurer(drawnTreasure, temphand, t, cardDrawn, currentPlayer, &testGameState);


			
			
			
			
			
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
			//test that player who played adventurer has proper hand count	
			flag1 = 0;
			
			//add 1 to original handcount (discard adventurer, draw 2 treasures)
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
			//test that player who played adventurer has proper deck count	
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
			//test that player who playe adevneturer has discount count > 1(for adventurer)
			flag1 = 0;
			
			//add 1 to original discard count for discarded adventurer
			if(testGameState.discardCount[0]>=1)
			{
				flag1 = 1;	
			}

			if(flag1 != 1)
			{
				printf("Test# %d - Whoseturn Player Discard Count >= 1 - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Whoseturn Player Discard Count >= 1 - FAIL\n", testNumber);
			}			
			
			
			
			
			
/***********************************************************************************/			
			//test that player who played adventurer no longer has adventurer in hand
			flag1 = 0;
			
			for(z = 0; z < testGameState.handCount[0]; z++)
			{
				if(testGameState.hand[0][z] == adventurer)
				{
					flag1 = 1;
				}
			}

			if(flag1 != 1)
			{
				printf("Test# %d - Whoseturn Player Hand does not contain adventurer post-play - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Whoseturn Player Hand does not contain adventurer post-play - FAIL\n", testNumber);
			}	




/***********************************************************************************/			
			//test that player who played adventurer has adventurer in discount
			flag1 = 0;
			
			for(z = 0; z < testGameState.discardCount[0]; z++)
			{
				if(testGameState.discard[0][z] == adventurer)
				{
					flag1 = 1;
				}
			}

			if(flag1 == 1)
			{
				printf("Test# %d - Whoseturn Player Discard contains adventurer post-play - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Whoseturn Player Discard contains adventurer post-play - FAIL\n", testNumber);
			}	


/***********************************************************************************/			
			//test that player who played adventurer has at least 1 treasure in hand
			flag1 = 0;
			
			for(z = 0; z < testGameState.handCount[0]; z++)
			{
				if((testGameState.hand[0][z] == copper) || (testGameState.hand[0][z] == gold) || (testGameState.hand[0][z] == silver))
				{
						flag1++;
				}
			}

			if(flag1 >= 1)
			{
				printf("Test# %d - Whoseturn Player Has >= 1 treasure in hand post turn - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Whoseturn Player Has >= 1 treasure in hand post turn - FAIL\n", testNumber);
			}
			
			
/***********************************************************************************/			
			//test that player who played adventurer has no more than 2 treasure cards in hand
			flag1=0;
			
			for(z = 0; z < testGameState.handCount[0]; z++)
			{
				if((testGameState.hand[0][z] == copper) || (testGameState.hand[0][z] == gold) || (testGameState.hand[0][z] == silver))
				{
						flag1++;
				}
			}

			if(flag1 <= 2)
			{
				printf("Test# %d - Whoseturn Player Has no more than 2 treasures in hand - PASS\n", testNumber);
			}
			
			else
			{
				printf("Test# %d - Whoseturn Player Has no more than 2 treasures in hand - FAIL\n", testNumber);
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



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

