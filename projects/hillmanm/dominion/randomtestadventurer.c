/* Matthew Hillman
 * randomtestadventurer.c (Adventurer)
   */
  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define MAX_TESTS 100
#define NOISY 1	//set NOISY to 0 to activate printf statements

#define TESTCARD "Adventurer"

void my_assert(int test, char* msg)
{
	if (!test) {
		printf ("ASSERT HAS FAILED: %s\n", msg);
	}
	return;
}

int main(int argc, char* argv[]) {
    int i, j;
	int newCards = 0;
    int discarded = 0;
    int shuffledCards = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	if (argc > 1) {
        seed = atoi(argv[1]);      
		printf("user input seed: %s\n", argv[1]);
    } 
	else {
        printf("no seed input, standard seed of %d used\n", seed);
    } 

		for (j=0; j<MAX_TESTS; j++) {
			
			//randomize number of players b/t 2 and 5
					numPlayers = (rand() % 4) + 1;
					
						
			// TEST 1: initialize a game state and player cards (deck will have at least two copper)
				initializeGame(numPlayers, k, seed, &G);

				printf("----------------- Testing Card: %s Test 1------------\n", TESTCARD);
					
			// copy the game state to a test case
				memcpy(&testG, &G, sizeof(struct gameState));

					 
			 if (NOISY == 0) {
				printf("Number of players = %d\n", numPlayers);	
				printf("BEFORE hand count = %d\n", testG.handCount[thisPlayer]);
				printf("BEFORE deck count = %d\n", testG.deckCount[thisPlayer]);
			 }	
				
				cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

				newCards = 2;
				
			if (NOISY == 0) {
				printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
				printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
				printf("discard = %d\n", testG.discardCount[thisPlayer]);
				
			 }	
				
							
				my_assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "msg 1");
				my_assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards, "msg 2");


			//check discard (more than two cards exposed)

			if (testG.deckCount[thisPlayer] < 3) {
						my_assert((testG.discardCount[thisPlayer] > 1), "msg 3");
			}
				
			//check no change to supply card piles

			if (NOISY == 0) {
				printf("Verify no change to the supply card piles\n");
			}	
			
			for (i=0; i<sizeof(testG.supplyCount)/sizeof(int); i++) {
			
			if (NOISY == 0) {
				printf("supply card count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
			}	
				my_assert(testG.supplyCount[i] == G.supplyCount[i], "msg 7"); 
			}
			
			//check no change to other players deck
			if (NOISY == 0) {
				printf("other players deck count = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1]);
			}	
			my_assert(testG.deckCount[thisPlayer + 1] == G.deckCount[thisPlayer + 1], "msg 6");
			   
			//check no change to other players hand
			if (NOISY == 0) {
				printf("other players hand count = %d, expected %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
			}	
			my_assert(testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1], "msg 5");
			
		}
		
			
		
		// TEST 2: INITIALIZE A NEW GAME STATE AND PLAYER CARDS (SEED DECK WITH ONLY ONE COPPER)
			
		 	
		for (j=0; j<MAX_TESTS; j++) {
			
		
				//randomize number of players b/t 1 and 4
					numPlayers = (rand() % 4) + 1;
								
					initializeGame(numPlayers, k, seed, &G);

					printf("----------------- Test 2: %s ----------------\n", TESTCARD);
					
				// copy the game state to a test case
				
				//randomize the hand count (test 2)
					G.handCount[thisPlayer] = (rand() % (MAX_HAND - 1) ) + 1;
									
					memcpy(&testG, &G, sizeof(struct gameState));
					newCards = 1;
					
						testG.deck[thisPlayer][0] = copper;
						G.deck[thisPlayer][0] = copper;
						testG.deck[thisPlayer][1] = minion;
						G.deck[thisPlayer][1] = minion;
						testG.deck[thisPlayer][2] = council_room;
						G.deck[thisPlayer][2] = council_room;
						testG.deck[thisPlayer][3] = smithy;
						G.deck[thisPlayer][3] = smithy;
						testG.deck[thisPlayer][4] = adventurer;
						G.deck[thisPlayer][4] = adventurer;
						
					if (NOISY == 0) {
						printf("BEFORE Hand count = %d\n", testG.handCount[thisPlayer]);
						printf("BEFORE Deck count = %d\n", testG.deckCount[thisPlayer]);
					}	
					
					
					cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

					if (NOISY == 0) {
						printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
						printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 5);
						printf("discard = %d\n", testG.discardCount[thisPlayer]);
					}
								
					my_assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "msg 1");
					my_assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 5, "msg 2");


				//check discard = 4
					my_assert((testG.discardCount[thisPlayer] == 4), "msg 3");

				//check no change to supply card piles

				if (NOISY == 0) {
					printf("Verify no change to the supply card piles\n");
				}	
				
				for (i=0; i<sizeof(testG.supplyCount)/sizeof(int); i++) {
				
				if (NOISY == 0) {
					printf("supply card count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
				}	
					my_assert(testG.supplyCount[i] == G.supplyCount[i], "msg 7"); 
				}
				
				//check no change to other players deck
				if (NOISY == 0) {
					printf("other players deck count = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1]);
				}	
				my_assert(testG.deckCount[thisPlayer + 1] == G.deckCount[thisPlayer + 1], "msg 6");
				   
				//check no change to other players hand
				if (NOISY == 0) {
					printf("other players hand count = %d, expected %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
				}	
				my_assert(testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1], "msg 5");
				
			}
		  
		 // TEST 3: INITIALIZE A NEW GAME STATE AND PLAYER CARDS (SEED DECK WITH NO TREASURE CARDS)
			
			
			for (j=0; j<MAX_TESTS; j++) {
			
		
		//randomize number of players b/t 1 and 4
			numPlayers = (rand() % 4) + 1;
								
						
			initializeGame(numPlayers, k, seed, &G);
			
		//randomize the hand count (test 2)
		//		G.handCount[thisPlayer] = (rand() % (MAX_HAND - 1) ) + 1;

			printf("----------------- Test 3: %s ----------------\n", TESTCARD);
			
		// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			newCards = 0;
			
				testG.deck[thisPlayer][0] = village;
				G.deck[thisPlayer][0] = village;
				testG.deck[thisPlayer][1] = minion;
				G.deck[thisPlayer][1] = minion;
				testG.deck[thisPlayer][2] = council_room;
				G.deck[thisPlayer][2] = council_room;
				testG.deck[thisPlayer][3] = smithy;
				G.deck[thisPlayer][3] = smithy;
				testG.deck[thisPlayer][4] = adventurer;
				G.deck[thisPlayer][4] = adventurer;

			
			if (NOISY == 0) {
				printf("BEFORE Hand count = %d\n", testG.handCount[thisPlayer]);
				printf("BEFORE Deck count = %d\n", testG.deckCount[thisPlayer]);
			}
			
			
			cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

			if (NOISY == 0) {
				printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
				printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 5);
				printf("discard = %d\n", testG.discardCount[thisPlayer]);
			}
			
			my_assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, "msg 1");
			my_assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 5, "msg 2");


		//check discard  = 5

				my_assert((testG.discardCount[thisPlayer] == 5), "msg 3");

		
		//check no change to supply card piles

			if (NOISY == 0) {
				printf("Verify no change to the supply card piles\n");
			}	
			
			for (i=0; i<sizeof(testG.supplyCount)/sizeof(int); i++) {
			
			if (NOISY == 0) {
				printf("supply card count = %d, expected = %d\n", testG.supplyCount[i], G.supplyCount[i]);
			}	
				my_assert(testG.supplyCount[i] == G.supplyCount[i], "msg 7"); 
			}
			
			//check no change to other players deck
			if (NOISY == 0) {
				printf("other players deck count = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1]);
			}	
			my_assert(testG.deckCount[thisPlayer + 1] == G.deckCount[thisPlayer + 1], "msg 6");
			   
			//check no change to other players hand
			if (NOISY == 0) {
				printf("other players hand count = %d, expected %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1]);
			}	
			my_assert(testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1], "msg 5");
			
	}
  
 	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


