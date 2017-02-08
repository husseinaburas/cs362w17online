// ***************
// * cardtest2.c
// * Desc: Unit test for ADVENTURER card in domion.c
//****************
#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion_refactorwk2.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int assertTrue();
int anyRandCard ();
int getRandIntLowHigh (int low, int high);
int printGameState (struct gameState * G);
int fillHandWithCards (struct gameState * G, int handCt);
int fillDiscardWithCards (struct gameState * G, int discardCt);
int fillDeckWithCards(struct gameState * G, int deckCt);
int checkAdventurer (struct gameState * G);
int myOwnAdventurerAction (int currentPlayer, struct gameState * G, int handPos);

// ***************
// assertTrue() - custom assert function
// ****************
int assertTrue(int control, int test) {
	printf ("** assertTrue result: ");
	if (control == test) {
		printf ("assert successful -- control: %d, test: %d\n", control, test);
		return 1;
	}
	printf ("assert FAILED -- control: %d, test: %d\n", control, test);
	return 0;
}

int anyRandCard () {
	int cardnum = getRandIntLowHigh (0, 26);
	//printf ("anyRandCard = %d\n", cardnum);
	return cardnum;
}

// *********************
// getRandIntLowHigh - selects an int between low and high inclusive
// input: low and high int
// return: integer
// *********************
int getRandIntLowHigh (int low, int high) {
	int randInt = (rand()%(high+1-low))+low;
	return randInt;
}


// *********************
// This systematically fills a HAND of given size with cards
// FOR FUTUERE: you can make this a random tester by assigning random cards
// *********************
int fillHandWithCards (struct gameState * G, int handCt) {
	int p, i;
	int card = 0; // card #s are 0 through 26
	// loop through each player
	for (p=0; p < G->numPlayers; p++) {
		// loop across each hand card
		for (i=0; i < handCt; i++) {
			G->hand[p][i] = card;
			card ++;
			if (card > 26) { card = 0; } // max card # is 26
		}
	}
	return 0;
}

// *********************
// This systematically fills a DISCARD of given size with cards
// FOR FUTUERE: you can make this a random tester by assigning random cards
// *********************
int fillDiscardWithCards (struct gameState * G, int discardCt) {
	int p, i;
	int card = 0; // card #s are 0 through 26
	// loop through each player
	for (p=0; p < G->numPlayers; p++) {
		// loop across each hand card
		for (i=0; i < discardCt; i++) {
			G->discard[p][i] = card;
			//printf ("fillDiscardWithCards card = %d\n", card);
			card ++;
			if (card > 26) { card = 0; } // max card # is 26
		}
	}
	return 0;
}

// *********************
// This systematically fills a DECK of given size with cards
// FOR FUTUERE: you can make this a random tester by assigning random cards
// *********************
int fillDeckWithCards(struct gameState * G, int deckCt) {
	int p, i;
	int card = 0; // card #s are 0 through 26
	// loop through each player
	for (p=0; p < G->numPlayers; p++) {
		// loop across each hand card
		for (i=0; i < deckCt; i++) {
			G->deck[p][i] = card;
			card ++;
			if (card > 26) { card = 0; } // max card # is 26
		}
	}
	return 0;
}

// *********************
// For debugging, this prints out all variables of the game state
// *********************
int printGameState (struct gameState * G) {
	int i;
	int p, j;
	int totalsupply = 0;
	printf ("\n--START PRINTING GAME STATE -------------------\n");
	printf ("numPlayers = %d\n", G->numPlayers);
	for (i = 0; i< (treasure_map+1); i++) {
		totalsupply += G->supplyCount[i];
	}
	printf ("SUPPLY TOTAL=%d, supplyCount: ", totalsupply);
	for (i = 0; i< (treasure_map+1); i++) {
		printf ("#%d: %d, ", i, G->supplyCount[i]);
	}
	printf ("\n");
	printf ("embargoTokens: ");
	for (i = 0; i< (treasure_map+1); i++) {
		printf ("#%d: %d, ", i, G->embargoTokens[i]);
	}
	printf ("\n");
	printf ("outpostPlayed = %d, ", G->outpostPlayed);
	printf ("outpostTurn = %d, ", G->outpostTurn);
	printf ("whoseTurn = %d, ", G->whoseTurn);
	printf ("phase = %d, ", G->phase);
	printf ("numActions = %d, ", G->numActions);
	printf ("coins = %d, ", G->coins);
	printf ("numBuys = %d\n", G->numBuys);
	printf ("playedCardCount = %d, playedCards[x]: ", G->playedCardCount);
	for (j=0; j< (G->playedCardCount); j++) {
		printf ("[%d] = %d", j, G->playedCards[j]);

	}	printf ("\n");

	for (p=0; p< G->numPlayers; p++) {
		printf ("---------------------\n");
		int handCount = G->handCount[p];
		printf ("PLAYER #%d, HANDCOUNT=%d, hand[player][hand]: ", p, handCount);
		for (j = 0; j<handCount; j++) {
			printf ("[%d][hand:%d] = %d, ", p, j, G->hand[p][j]);
		}
		printf ("\n");

		int deckCount = G->deckCount[p];
		printf ("PLAYER #%d, DECKCOUNT=%d, deck[player][hand]: ", p, deckCount);
		for (j = 0; j<deckCount; j++) {
			printf ("[%d][deck:%d] = %d, ", p, j, G->deck[p][j]);
		}
		printf ("\n");

		int discardCount = G->discardCount[p];
		printf ("PLAYER #%d, DISCARDCOUNT=%d, discard[player][hand]: ", p, discardCount);
		for (j = 0; j<discardCount; j++) {
			printf ("[%d][discard: %d] = %d, ", p, j, G->discard[p][j]);
		}
		printf ("\n");
	}
	printf ("--END PRINTING GAME STATE -------------------\n\n");
	return 0;
}

// **********************
// tests for ADVENTURER
// **********************
int checkAdventurer (struct gameState * G) {
	int errorval = 0;
	int testresponse, controlresponse;
	int p;
	int response;

	struct gameState Gpre, Gcontrol;

	// loop through each player
	for (p=0; p< G->numPlayers; p++) {

		G->whoseTurn = p; // setting the turn of the player to play Adventurer

		// find the location of adventurer in player p's hand
		int handPos = -1;
		int c;
		for (c=0; c < G->handCount[p]; c++) {
			if (G->hand[p][c] == adventurer) { handPos = c; }
		}
		if (handPos == -1) {
			printf ("\nNOTE Player %d: did NOT find Adventurer in this player's hand\n", p);
			//printGameState (G);
		}

		// Create a control state that is copy of G
		memcpy (&Gpre, G, sizeof(struct gameState));
		memcpy (&Gcontrol, G, sizeof(struct gameState));

		// call the function to test
		int card = adventurer;
		int choice1 = 0; // not used for adventurer
		int choice2 = 0; // not used for adventurer
		int choice3 = 0; // not used for adventurer
		int bonus = 0;  // not used for adventurer

		testresponse =  cardEffect(card, choice1, choice2, choice3, G,
									handPos, &bonus);

		controlresponse = myOwnAdventurerAction (p, &Gcontrol, handPos);

		// IF THERE WAS AN ADVENTURER CARD TO PLAY
		if (handPos > -1) {

			// check if played card was increased by 1
			if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
				printf ("Success player %d: playedCardCount was increased 1\n", p);
			} else {
				printf ("FAILED player %d: playedCardCount was NOT increased by 1\n", p);
				errorval--;
			}

			// check to see if the total supply count has not changed
			int c;
			int supplyTotalPost = 0;
			int supplyTotalPre = 0;
			for (c=0; c < (treasure_map+1); c++) {
				supplyTotalPost += G->supplyCount[c];
				supplyTotalPre += Gpre.supplyCount[c];
				//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
			}
			if (supplyTotalPost == supplyTotalPre) {
				printf ("Success player %d: given no supply to draw down, no change in total supply count\n", p);
			} else {
				printf ("FAILED player %d: given no supply to draw down, change in total supply count\n", p);
				errorval--;
			}

			// check if hand count between test and control are the same
			if ((G->handCount[p] - Gcontrol.handCount[p]) == 0) {
				printf ("Success player %d: handCount test and control = %d\n", p, G->handCount[p]);
			} else {
				printf ("FAILED player %d: handCount test: %d and control: %d not same\n",
						p, G->handCount[p], Gcontrol.handCount[p]);
				errorval--;
			}

			// check if deck count between test and control are the same
			if ((G->deckCount[p] - Gcontrol.deckCount[p]) == 0) {
				printf ("Success player %d: deckCount test and control = %d\n", p, G->deckCount[p]);
			} else {
				printf ("FAILED player %d: deckCount test: %d and control: %d not same\n",
						p, G->deckCount[p], Gcontrol.deckCount[p]);
				//printGameState (G);
				//printGameState (&Gcontrol);
				errorval--;
			}

		}

		// IF THERE WAS NO ACTION CARD TO PLAY
		if (handPos < 0) {

			// check if handcount is the same)
			if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
				printf ("Success player %d: given no Adventurer handCount increased by 0\n", p);
			} else {
				printf ("FAILED player %d: given no Adventurer handCount NOT increased by 0\n", p);
				//printGameState(G);
				errorval--;
			}

			// check if deck count was decreased by 0
			if (Gpre.deckCount[p] > 2) {
				if ((G->deckCount[p] - Gpre.deckCount[p]) == 0) {
					printf ("Success player %d: given no Adventurer deckCount increased by 0\n", p);
				} else {
					printf ("FAILED player %d: given no Adventurer deckCount NOT increased by 0\n", p);
					errorval--;
				}
			}

			// check if played card was increased by 0
			if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
				printf ("Success player %d: given no Adventurer playedCardCount was increased 0\n", p);
			} else {
				printf ("FAILED player %d: given no AdventurerplayedCardCount was NOT increased by 0\n", p);
				errorval--;
			}

			// check to see if the total supply count has not changed
			int c;
			int supplyTotalPost = 0;
			int supplyTotalPre = 0;
			for (c=0; c < (treasure_map+1); c++) {
				supplyTotalPost += G->supplyCount[c];
				supplyTotalPre += Gpre.supplyCount[c];
				//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
			}
			if (supplyTotalPost == supplyTotalPre) {
				printf ("Success player %d: given no Adventurer, no change in total supply count\n", p);
			} else {
				printf ("FAILED player %d: given no Adventurer, change in total supply count\n", p);
				errorval--;
			}
		}

	}
	return errorval;
}

int myOwnAdventurerAction (int p, struct gameState * G, int handPos) {

	if (G->hand[p][handPos] != adventurer) {
		printf ("There is no adventurer to play in this hand position");
		return -1;
	}

	int drawntreasure=0;
	int z = 0; // for temp hand counter
	int cardDrawn;
	int temphand[MAX_HAND];

	int maxdraw = G->deckCount[p] + G->discardCount[p]; // some maximum time you can loop (if no treasure)
	int loopcounter = 0;

	//discard card from hand (to played pile)
	discardCard (handPos, p, G, 0);

	while ((drawntreasure<2) && (loopcounter < maxdraw)) {
		loopcounter++;
		if (G->deckCount[p] <1){
			//if the deck is empty we need to shuffle discard and add to deck
			shuffle(p, G);
		}

		drawCard(p, G);
		cardDrawn = G->hand[p][G->handCount[p]-1];
		//top card of hand is most recently drawn card.

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
			drawntreasure++;
			printf ("found a treasure!\n");
		} else {
			 temphand[z]=cardDrawn;
			 G->handCount[p]--;
			 //this should just remove the top card (the most recently drawn one).
			 z++;
		 }
	  }

	  while(z-1>=0){
		  G->discard[p][G->discardCount[p]++]=temphand[z-1];
		  // discard all cards in play that have been drawn
		  z=z-1;
	  }
	return 0;
}

int main () {
	printf ("\n\nstarting cardtest1 -- testing SMITHY function\n\n");
	// DEBUGGING
	// printf ("MAX_HAND = %d, MAX_DECK = %d, MAX_PLAYERS = %d\n", MAX_HAND, MAX_DECK, MAX_PLAYERS);
	// MAX_HAND = 500, MAX_DECK = 500, MAX_PLAYERS = 4

	// -----------------
	// setup a standard game
	// -----------------
	struct gameState G; // test game state
	struct gameState Gcontrol; // control game state (pre-test)
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, smithy, treasure_map}; // replaced one of the cards with treasure_map

	// -------------------
	// setup the fixed unit tests  !!! WE ARE NOT DOING RANDOM TESTS!!!
	// INSTEAD we are creating fixed tests by looping through different input spaces
	// for deck, hand and discard size. we also fill in the card positions for each
	// deck, hand and discard by looping through all 26 available cards
	// -------------------
	int player = 0;
	int deckCt = 0;
	int discardCt = 0;
	int handCt = 0;
	int response;
	int trial = 0;

	// Loop through # of players
	// Note: to pass initializeGAme, the number of players must be between 2 and MAX_Players
//	for (player = 2; player <= MAX_PLAYERS; player++) {
	for (player = 2; player <= 2; player++) {

		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("unittest1 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// force a ADVENTURER to player 0's hand so you have instances where you can and cannot play
		int toFlag = 2; // add action card to the hand
		gainCard (adventurer, &G, toFlag, 0);

		// force silver and gold to player 0's deck to test silver and gold
		toFlag = 1; // add to the deck
		gainCard (silver, &G, toFlag, 0);
		gainCard (gold, &G, toFlag, 0);
		// DEBUG
		printGameState (&G);

		response = checkAdventurer (&G);

		// now loop through different sizes of deck, hand, and discard counts

		// USE THIS OPTION TO GENERATE ALL POSSIBLE COMBINATIONS OF DECK SIZE
//		for (deckCt = 0; deckCt < MAX_DECK; deckCt++) {
//			for (discardCt = 0; discardCt < MAX_DECK; discardCt++) {
//				for (handCt = 0; handCt < MAX_HAND; handCt++) {
//
		// USE THIS OPTION TO GENERATE SOE REASONABLE COMBINATIONS OF DECK SIZE
/*
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 8; handCt < 10; handCt++) {

					// set the counts for each card stack for each player
					int pCt;
					for (pCt = 0; pCt < player; pCt++) {
						G.handCount[pCt] = handCt;
						G.discardCount[pCt] = discardCt;
						G.deckCount[pCt] = deckCt;
					}

					// fill in the hand, discard, and deckCount with valid cards (systematically, not randomly)
					fillHandWithCards (&G, handCt);
					fillDiscardWithCards (&G, discardCt);
					fillDeckWithCards(&G, deckCt);

					// each loop is a "trial"
					trial++;
					printf ("--- Trial #%d ---\n", trial);
					response = checkGainCard (&G);

					// ASSERT TO TEST IF CHECK COMPLETED
					if (!(response == 0)) {
						printf ("\nUnittest3: gainCard() did not pass our unit test\n");
// TODO CHANGE						printf ("Debug data: trial #%d, handCt = %d, discardCt = %d, deckCt = %d, players = %d, response = %d\n\n",
// TODO CHANGE								trial, handCt, discardCt, deckCt, player, response);
					} else {
						printf ("\nUnittest2: gainCard() TEST SUCCESSFULLY COMPLETED\n\n");
					}
				}
			}
		}
*/
	}
	return 0;
}
