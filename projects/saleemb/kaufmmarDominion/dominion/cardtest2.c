/* Author: Bilal Saleem
 * Date: 2/2/17
 * Card to test: adventurer
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0


void assert(bool j, char * msg){
	if(j == false) {
		printf("-- %s \n", msg);
	}
}

void setDeck(struct gameState * G, int player, int * dCards, int numDCards){
	int i;			// loop counter

	G->deckCount[player] = numDCards;
	
	for(i = 0; i < numDCards; ++i)
		G->deck[player][i] = dCards[i];	

}

// cards must be in same order to be considered equivalent
void compareHands(int * handOne, int * handTwo, int numCards) {
	int i;

	for(i = 0; i < numCards; ++i)
		assert(handOne[i] == handTwo[i], "hand doesn't contain appropriate cards");

}

int main() {

	struct gameState * G;		// state of the game -- one for calling functions on
	struct gameState * GCopy;	// state of the game -- one for comparisons/resetting the game
	int * kCards; 			// set of kingdom cards to be used in the game
	int deck[10];			// used to initialize a player's deck
	int correctHand[MAX_HAND];	// used for comparisons; holds what a players hand should look like
	int numCardInHand;		// holds how many cards are stored in correctHand
	int temphand[MAX_HAND];		// holds cards temporarily while adventurer is being played
	int correctDiscard[MAX_HAND];	// used for comparisons; holds what the discard pile should look like
	int i, j;			// loop counter

	printf("cardtest2.c\n");
	
	/*** initialize game without shuffling deck ***/
	G = newGame();
	GCopy = newGame();
	kCards = kingdomCards(smithy, adventurer, village, great_hall, council_room, feast,
				gardens, mine, remodel, outpost);	
	// set up random number generator
	SelectStream(1);
	PutSeed((long)1000);

	// set number of cards based on a two-player game
	G->numPlayers = 2;
	G->supplyCount[curse] = 10;
	G->supplyCount[estate] = 8;
	G->supplyCount[duchy] = 8;
	G->supplyCount[province] = 8;
	G->supplyCount[copper] = 60 - (7 * 2);  // 60 - (7 * number_of_players)
	G->supplyCount[silver] = 40; 	
	G->supplyCount[gold] = 30;
	
	for(i = adventurer; i <= treasure_map; ++i){
		for(j = 0; j < 10; ++j){
			if(kCards[j] == i) {
				if(kCards[j] == great_hall || kCards[j] == gardens) 
					G->supplyCount[i] = 8;
				else
					G->supplyCount[i] = 10;
				break;
			} else {
				G->supplyCount[i] = -1;
			}	
		}
	}	
	// set player decks
	deck[9] = copper;	// top of deck
	deck[8] = copper;
	deck[7] = estate;
	deck[6] = copper;
	deck[5] = estate;
	deck[4] = estate;
	deck[3] = copper;
	deck[2] = copper;
	deck[1] = copper;
	deck[0] = copper;	// bottom of deck

	setDeck(G, 0, deck, 10);

	/* replaced with setDeck()
	for(i = 0; i < 2; ++i){
		G->deckCount[i] = 0;
		for(j = 0; j < 3; ++j){
			G->deck[i][j] = estate;
			G->deckCount[j]++;
		}
		for(j = 3; j < 10; ++j){
			G->deck[i][j] = copper;
			G->deckCount[i]++;
		}
	}
	*/
	// at this point you would normally shuffle the deck
	// however this will not be done so that we know what cards are in the deck
	// and in what order
	
	// set handCount and discardCount for both players
	for(i = 0; i < 2; ++i){
		G->handCount[i] = 0;
		G->discardCount[i] = 0;
	}
	
	// set embargo tokens for all supply piles to none/zero
	for(i = 0; i <= treasure_map; ++i)
		G->embargoTokens[i] = 0;

	// initialize first players turn
	G->outpostPlayed = 0;
	G->phase = 0;
	G->numActions = 1;
	G->numBuys = 1;
	G->playedCardCount = 0;
	G->whoseTurn = 0;
	G->handCount[G->whoseTurn] = 0;

	// draw five cards for player 1
	for(i = 0; i < 5; ++i)
		drawCard(G->whoseTurn, G);
	
	updateCoins(G->whoseTurn, G, 0);

	// make a copy of the game state for comparison purposes
	memcpy(GCopy, G, sizeof(struct gameState));
/*
	// print hand and deck of player one
	printf("Hand of player 1: \n");
	for(i = 0; i < G->handCount[0]; ++i)
		printf("G->hand[0][%d] == %d\n", i, G->hand[0][i]);
		
	printf("Deck of player 1: \n");
	for(i = 0; i < G->deckCount[0]; ++i)
		printf("G->deck[0][%d] == %d\n", i, G->deck[0][i]);
*/
	/***************** TEST ONE *****************************
 	* Currently, the hand of of player 1 is: copper, copper,
 	* estate, copper and estate.  The cards in the deck from
 	* top to bottom are: estate, copper, copper, copper, and
 	* copper. So if adventurer card is played, player 1's hand
 	* should become copper,copper, estate, copper, estate, copper,
 	* and copper.  
 	* *******************************************************/
	printf("-- TEST ONE --\n");

	correctHand[0] = copper;
	correctHand[1] = copper;
	correctHand[2] = estate;
	correctHand[3] = copper;
	correctHand[4] = estate;
	correctHand[5] = copper; // drawn due to adventurer
	correctHand[6] = copper; // drawn due to adventurer
	numCardInHand = 7;

	useAdventurer(0, G, temphand);
	
	compareHands(correctHand, G->hand[0], numCardInHand);

	// reset state of game
	memcpy(G, GCopy, sizeof(struct gameState));

/*
	// print hand and deck of player one
	printf("Hand of player 1 after reset: \n");
	for(i = 0; i < G->handCount[0]; ++i)
		printf("G->hand[0][%d] == %d\n", i, G->hand[0][i]);
		
	printf("Deck of player 1: \n");
	for(i = 0; i < G->deckCount[0]; ++i)
		printf("G->deck[0][%d] == %d\n", i, G->deck[0][i]);

*/		
	/********************* TEST TWO ****************************
 	* Currently, the hand of the player is: copper, copper, estate,
 	* copper, and estate.  After adventurer is played, the hand should
 	* be: copper, copper, estate, copper, estate, copper, and copper.
 	* Meanwhile, the discard should be estate and the discardCount
 	* should be 1.
 	***********************************************************/
	
	printf("-- TEST TWO -- \n");

	correctDiscard[0] = estate;
	
	useAdventurer(0, G, temphand);
	
	assert(G->discardCount[0] == GCopy->discardCount[0] + 1, "discardCount not at appopriate value");
	for(i = 0; i < G->discardCount[0]; ++i)
		assert(G->discard[0][i] == correctDiscard[i], "discard pile differs");
	
	// reset state of game
	memcpy(G, GCopy, sizeof(struct gameState));

	/********************* TEST THREE ******************************
 	* playedCardCount should be incremented by 1 and playedCards[0]
 	* should be equal to adventurer
 	* *************************************************************/

	printf("-- TEST THREE -- \n");

	useAdventurer(0, G, temphand);

	assert(G->playedCardCount == GCopy->playedCardCount + 1, "playedCardCount not incremented appropriately");
	assert(G->playedCards[0] == adventurer, "adventurer not placed in playedCards");

	
	return 0; 

}
