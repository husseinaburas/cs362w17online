/* Author: Bilal Saleem
 * Date: 2/2/17
 * Card to test: great_hall
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

void setHand(struct gameState * G, int player, int * hCards, int numHCards){
	int i;			// loop counter

	G->handCount[player] = numHCards;
	
	for(i = 0; i < numHCards; ++i)
		G->hand[player][i] = hCards[i];	

}



void gameStateCompare(struct gameState * G, struct gameState * GCopy) {
	int i, k; 	// loop iterators

	// go through all attributes of struct gameState and see if any have changed
	assert(G->numPlayers == GCopy->numPlayers, "numPlayers changed after call");

        for(i = 0; i < treasure_map + 1; ++i){
                assert(G->supplyCount[i] == GCopy->supplyCount[i] , "supplyCount changed after call");
        }

        for(i = 0; i < treasure_map + 1; ++i){
                assert(G->embargoTokens[i] == GCopy->embargoTokens[i], "embargoToekns changed");
        }

        assert(G->outpostPlayed == GCopy->outpostPlayed , "outpostPlayed changed after call");
        assert(G->outpostTurn == GCopy->outpostTurn , "outpostTurn changed after call");
        assert(G->whoseTurn == GCopy->whoseTurn , "whoseTurn changed after call");
        assert(G->phase == GCopy->phase , "phase changed after call");

//      assert(G->numActions == GCopy->numActions , "numActions changed after call");
        assert(G->coins == GCopy->coins , "coins changed after call");
        assert(G->numBuys == GCopy->numBuys , "numBuys changed after call");
/* should change/tested below	
	for(i = 0; i < MAX_PLAYERS; ++i){
		for(k = 0; k < MAX_HAND; ++k){
			assert(G->hand[i][k] == GCopy->hand[i][k], "hand changed after call");
		}
	}

	for(i = 0; i < MAX_PLAYERS; ++i){
		assert(G->handCount[i] == GCopy->handCount[i], "handCount changed after call");
	}

	for(i = 0; i < MAX_PLAYERS; ++i){
		for(k = 0; k < MAX_HAND; ++k){
                        assert(G->deck[i][k] == GCopy->deck[i][k], "deck changed after call");
                }
        }

        for(i = 0; i < MAX_PLAYERS; ++i){
                assert(G->deckCount[i] == GCopy->deckCount[i], "deckCount changed after call");
        }
*/	
        for(i = 0; i < MAX_PLAYERS; ++i){
                for(k = 0; k < MAX_HAND; ++k){
                        assert(G->discard[i][k] == GCopy->discard[i][k], "discard changed after call");
                }
        }

        for(i = 0; i < MAX_PLAYERS; ++i){
                assert(G->discardCount[i] == GCopy->discardCount[i], "discardCount changed after call");
        }
/*
	for(i = 0; i < MAX_DECK; ++i){
		assert(G->playedCards[i] == GCopy->playedCards[i], "playedCards changed after call");
	}

	assert(G->playedCardCount == GCopy->playedCardCount, "playedCardCound changed after call");
*/
}



int main(){

	struct gameState * G;
	struct gameState * GCopy;
	int * kCards;
	int hand[5];


	printf("cardtest4.c\n");
	
	// initialize game
	G = newGame();
	GCopy = newGame();

	kCards = kingdomCards(adventurer, smithy, village, great_hall, council_room,
				feast, gardens, mine, remodel, baron);

	initializeGame(2, kCards, 1000, G);

	// change hand from what was initialized during initializeGame()
	hand[0] = copper;
	hand[1] = copper;
	hand[2] = estate;
	hand[3] = copper;
	hand[4] = great_hall;

	setHand(G, 0, hand, 5);

	// duplicate G in order to make change of state comparisons
	memcpy(GCopy, G, sizeof(struct gameState));

	/******************* TEST ONE *****************************
 	* calling useGreatHall() should result in +1 card drawn, 
 	* and -1 card from hand (card that goes from hand to
 	* playedCards).  So the net cardCount should equal 0
 	* ********************************************************/

	useGreatHall(0, 4, G);

	assert(G->handCount[0] == (GCopy->handCount[0] + 1 - 1), "handCount not at appropriate value");	// draw 1 card, play 1 card -- net +0

	// reset state of game
	memcpy(G, GCopy, sizeof(struct gameState));

	/******************** TEST TWO **************************
 	* calling useGreatHall() should result in +1 Actions after
 	* -1 action (because you played great hall). So the net actions
 	*  should be 0. 
 	*  *****************************************************/

	useGreatHall(0, 4, G);
	
	assert(G->numActions == (GCopy->numActions - 1 + 1), "numActions not at appropriate value"); 	// play an action card, gain an action -- net 0
		
	// reset state of game
	memcpy(G, GCopy, sizeof(struct gameState));

	/******************** TEST THREE ***************************
 	* calling useGreatHall() should result in hand[0][4] to hold a 
 	* card that isn't great_hall.
 	* *********************************************************/
	useGreatHall(0, 4, G);
	
	assert(G->hand[0][4] != great_hall, "great_hall still in hand");

	// reset state of game
	memcpy(G, GCopy, sizeof(struct gameState));

	/****************** TEST FOUR *****************************
 	* calling useGreatHall() should result in playedCards[0] to
 	* hold great_hall.  Also, playedCardCount should be equal to
 	* 1.
 	* ********************************************************/
	useGreatHall(0, 4, G);

	assert(G->playedCards[0] == great_hall, "great_hall not in playedCards");
	assert(G->playedCardCount == 1, "playedCardCount not at appropriate value");

	// reset state of game
	memcpy(G, GCopy, sizeof(struct gameState));

	/******************** TEST FIVE ************************
 	* calling useGreatHall() should result in a -1 decrease
 	* in deckCount
 	* *****************************************************/

	useGreatHall(0, 4, G);
	
	assert(G->deckCount[0] == (GCopy->deckCount[0] -1), "deckCount not at appropriate value");	// draw one card from deck
	
	// reset state of game
	memcpy(G, GCopy, sizeof(struct gameState));


	/*************** TEST SIX  *******************************
 	* all of the variable from struct gameState not mentioned
 	* above should remain the same. 
 	* *******************************************************/
		
	useGreatHall(0, 4, G);

	gameStateCompare(G, GCopy);
	
	// reset state of game
	memcpy(G, GCopy, sizeof(struct gameState));

	/*** Clean-up ***/
	free(G);
	free(GCopy);		


	return 0;
}
