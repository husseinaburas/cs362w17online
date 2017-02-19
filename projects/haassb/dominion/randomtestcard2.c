/* -----------------------------------------------------------------------
 * Test of Mine card
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
	int numberTests = 1000;
    int i, z, j;
    int seed = 1000;

    int numPlayers;
	int temp;
	int functionReturn;
	int minePos;
	int treasurePos;
	int numberMin, numberMax;
	int testNumber =0;
	int cardTrashed;
	int cardRequested;
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

    printf ("TESTING playMine():\n");

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
		if(temp == 0)
		{
			//initialize player 0's cards in hand to all curses for control purposes
			for(z= 0; z <= testGameState.handCount[0]; z++)
			{
				testGameState.hand[0][z] = curse;
			}
								
					
			//generate random number for where in hand of player 0 Mine goes			
			numberMin = 0;
			numberMax = (testGameState.handCount[0] - 1);
			
			minePos = numberMin+(rand() % (numberMax-numberMin + 1 ));
			
			//replace card in hand with mine card
			testGameState.hand[0][minePos] = mine;
	
			//generate random number for type of treasure to insert into hand			
			numberMin = 0;
			numberMax = 3;
			
			treasureType = numberMin+(rand() % (numberMax-numberMin + 1 ));	
		
			z=0;
			
			while(z < 1)
			{
				//generate random number for position of hand to put treasure card	
				numberMin = 0;
				numberMax = (testGameState.handCount[0]-1);
			
				treasurePos = numberMin+(rand() % (numberMax-numberMin + 1 ));
				
				//if treasure position doesn't randomly get assigned to where mine is
				if((testGameState.hand[0][treasurePos]) != mine)
				{
					if(treasureType == 1)
						testGameState.hand[0][treasurePos] = copper;

					if(treasureType == 2)
						testGameState.hand[0][treasurePos] = silver;

					if(treasureType == 3)
						testGameState.hand[0][treasurePos] = gold;
				
					z++;
				}
			}
			
			
	
			//generate random number for card trashed position
			numberMin = 0;
			numberMax = (testGameState.handCount[0]-1);
			
			cardTrashed = numberMin+(rand() % (numberMax-numberMin + 1 ));
			
			
			//generate random number for card requested
			numberMin = 1;
			numberMax = 4;
			
			int placeHolder = numberMin+(rand() % (numberMax-numberMin + 1 ));
			
			if(placeHolder == 1)
				cardRequested = copper;

			if(placeHolder == 2)
				cardRequested = silver;

			if(placeHolder == 3)
				cardRequested = gold;		
	
			if(placeHolder == 4)
				cardRequested = curse;	
		
			
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

			
			//call playMine
			functionReturn = playMine(cardTrashed, cardRequested, &testGameState, minePos);


			
					
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
			//test that if card trashed wasn't treasure, returns error				
			
			//if not treasure
			if((originalHand[0][cardTrashed] != copper) && (originalHand[0][cardTrashed] != gold) && (originalHand[0][cardTrashed] != silver))
			{
				if(functionReturn != 0)
				{
					printf("Test# %d - Invalid Trash Card Passed to Function - PASS\n", testNumber);	
				}
				
				else
				{
					printf("Test# %d - Invalid Trash Card Passed to Function - FAIL\n", testNumber);	
				}					
			}
			
			
/***********************************************************************************/			
			//test that if card requested wasn't treasure, returns error				
			
			//if not treasure
			if((cardRequested != copper) && (cardRequested != gold) && (cardRequested != silver))
			{
				if(functionReturn != 0)
				{
					printf("Test# %d - Invalid Requested Card Passed to Function - PASS\n", testNumber);	
				}
				
				else
				{
					printf("Test# %d - Invalid Requested Card Passed to Function - FAIL\n", testNumber);	
				}					
			}			
			
			
			
/***********************************************************************************/			
			//test that if card requested is too expensive, returns error			
			
			//if both cards treasures
			if((originalHand[0][cardTrashed] == copper) || (originalHand[0][cardTrashed] == gold) || (originalHand[0][cardTrashed] == silver))
			{
				if((cardRequested == copper) || (cardRequested == gold) || (cardRequested == silver))
				{
					//if within cost threshold
					if(getCost(originalHand[0][cardTrashed]) + 3 >= getCost(getCost(cardRequested)))
					{
						if(functionReturn == 0)
						{
							printf("Test# %d - Test of Proper Validation of Cost Difference - PASS\n", testNumber);	
						}
						
						else
						{
							printf("Test# %d - Test of Proper Validation of Cost Difference - FAIL\n", testNumber);	
						}						
					}
					
					else
					{

						if(functionReturn != 0)
						{
							printf("Test# %d - Test of Proper Validation of Cost Difference - PASS\n", testNumber);	
						}
						
						else
						{
							printf("Test# %d - Test of Proper Validation of Cost Difference - FAIL\n", testNumber);	
						}					
					}					
					
				}				
			}
			
			
			//proceed with subsequent tests if previous tests with bad test inputs did not terminate test
			if(functionReturn == 0)
			{
				/***********************************************************************************/			
				//test that player who played mine has proper hand count	
				flag1 = 0;
				
				//subtract 1 from original handcount (get new treasure, discard mine and trash treasure
				if((assertTrue(originalHandCount[0]-1, testGameState.handCount[0])) != 1)
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
				//test that player who played mine has proper deck count	
				flag1 = 0;
				

				if((assertTrue(originalDeckCount[0], testGameState.deckCount[0])) != 1)
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
				//test that player who played mine has proper discount count
				flag1 = 0;
				
				//add 1 to original discard count for discarded mine
				if(testGameState.discardCount[0] == originalDiscardCount[0])
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
				//test that player who played mine no longer has mine in hand
				flag1 = 0;
				
				for(z = 0; z < testGameState.handCount[0]; z++)
				{
					if(testGameState.hand[0][z] == mine)
					{
						flag1 = 1;
					}
				}

				if(flag1 != 1)
				{
					printf("Test# %d - Whoseturn Player Hand does not contain mine post-play - PASS\n", testNumber);
				}
				
				else
				{
					printf("Test# %d - Whoseturn Player Hand does not contain mine post-play - FAIL\n", testNumber);
				}	




				/***********************************************************************************/			
				//test that player who played mine has mine in discount
				flag1 = 0;
				
				for(z = 0; z < testGameState.discardCount[0]; z++)
				{
					if(testGameState.discard[0][z] == mine)
					{
						flag1 = 1;
					}
				}

				if(flag1 == 1)
				{
					printf("Test# %d - Whoseturn Player Discard contains mine post play - PASS\n", testNumber);
				}
				
				else
				{
					printf("Test# %d - Whoseturn Player Discard contains mine post play - FAIL\n", testNumber);
				}	


				/***********************************************************************************/			
				//test that player who played mine has new treasure in hand
				flag1 = 0;
				
				for(z = 0; z < testGameState.handCount[0]; z++)
				{
					if((testGameState.hand[0][z]) == cardRequested)
					{
							flag1++;
					}
				}

				if(flag1 == 1)
				{
					printf("Test# %d - Whoseturn Player Has new treasure in hand post turn - PASS\n", testNumber);
				}
				
				else
				{
					printf("Test# %d - Whoseturn Player Has newtreasure in hand post turn - FAIL\n", testNumber);
				}
				
				
				/***********************************************************************************/			
				//test that player who played mine doesn't have trashed card
				flag1=0;
				
				for(z = 0; z < testGameState.handCount[0]; z++)
				{
					if(testGameState.hand[0][z] == originalHand[0][cardTrashed])
					{
							flag1++;
					}
				}

				if(flag1 > 0)
				{
					printf("Test# %d - Whoseturn Player Has no more than 2 treasures in hand - PASS\n", testNumber);
				}
				
				else
				{
					printf("Test# %d - Whoseturn Player Has no more than 2 treasures in hand - FAIL\n", testNumber);
				}			

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



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

