/* Author: Bilal Saleem
 * Date: 2/2/17
 * Card to test: village
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

void printHand(struct gameState * G, int player){
	int i;
	
	for(i = 0; i < G->handCount[player]; ++i){
		printf("G->hand[%d][%d] == %d\n", player, i, G->hand[player][i]);
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
// 	should change
//        assert(G->numActions == GCopy->numActions , "numActions changed after call");
        assert(G->coins == GCopy->coins , "coins changed after call");
        assert(G->numBuys == GCopy->numBuys , "numBuys changed after call");
/* 	should change	
	for(i = 0; i < MAX_PLAYERS; ++i){
		for(k = 0; k < MAX_HAND; ++k){
			assert(G->hand[i][k] == GCopy->hand[i][k], "hand changed after call");
		}
	}
*/
	for(i = 0; i < MAX_PLAYERS; ++i){
		assert(G->handCount[i] == GCopy->handCount[i], "handCount changed after call");
	}

	for(i = 0; i < MAX_PLAYERS; ++i){
		for(k = 0; k < MAX_HAND; ++k){
                        assert(G->deck[i][k] == GCopy->deck[i][k], "deck changed after call");
                }
        }
/*	should change
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
/*	should change
	for(i = 0; i < MAX_DECK; ++i){
		assert(G->playedCards[i] == GCopy->playedCards[i], "playedCards changed after call");
	}

	assert(G->playedCardCount == GCopy->playedCardCount, "playedCardCound changed after call");
*/
}

int main() {

	struct gameState * G;
	struct gameState * GCopy;
	int * kCards;
	int hand[5];
	int i, j;

	printf("cardtest3.c\n");
	
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
	hand[4] = village;

	setHand(G, 0, hand, 5);

	// duplicate G in order to make change of state comparisons
	memcpy(GCopy, G, sizeof(struct gameState));

	/*************** TEST ONE *************************
 	* Using the village card should result in +1 card
 	* ************************************************/

	printf("-- TEST ONE --\n");
		
	useVillage(0, 4, G); 

	assert(G->handCount[0] == GCopy->handCount[0] + 1 - 1, "handCount not at appropriate value"); // put one card in play, and drew one card so net 0
	
	// reset game
	memcpy(G, GCopy, sizeof(struct gameState));	

	/******************* TEST TWO ***********************
 	* Using village should result in +2 actions
 	* **************************************************/

	printf("-- TEST TWO -- \n");

	useVillage(0, 4, G);
	
	assert(G->numActions = GCopy->numActions + 2 - 1, "numActions not at appropriate value"); // use one action and gain two so net +1

	// reset game
	memcpy(G, GCopy, sizeof(struct gameState));	

	/***************** TEST THREE ********************************
 	* Using village should result in +1 increase playedCardCount
 	* and playedCards[0] should be village
 	* ***********************************************************/
	
	printf("-- TEST THREE --\n");

	useVillage(0, 4, G);

	assert(G->playedCardCount == GCopy->playedCardCount + 1, "playedCardCount not at appropriate value");
	assert(G->playedCards[0] == village, "village not in playedCards");

	// reset game
	memcpy(G, GCopy, sizeof(struct gameState));	

	/***************** TEST FOUR *********************************
 	* Make sure values that shouldn't change in gameState structure
 	* remain the same
 	* ***********************************************************/
	
	printf("-- TEST FOUR --\n");
	
	useVillage(0, 4, G);

	gameStateCompare(G, GCopy);

	// free memory
	free(G);
	free(GCopy);
	
	return 0;
}
