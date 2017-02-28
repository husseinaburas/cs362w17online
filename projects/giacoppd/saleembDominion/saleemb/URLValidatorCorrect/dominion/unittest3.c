/* Author: Bilal Saleem
 * Date: 1/31/17
 * Function to test: int handCard(int, struct gameState*)
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
		printf("Test Failed -- %s \n", msg);
	}
}

void gameStateCompare(struct gameState * G, struct gameState * GCopy, char * msg) {
	int i, k; 	// loop iterators

	//printf("%s \n", msg);
	
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
        assert(G->numActions == GCopy->numActions , "numActions changed after call");
        assert(G->coins == GCopy->coins , "coins changed after call");
        assert(G->numBuys == GCopy->numBuys , "numBuys changed after call");
	
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
	
        for(i = 0; i < MAX_PLAYERS; ++i){
                for(k = 0; k < MAX_HAND; ++k){
                        assert(G->discard[i][k] == GCopy->discard[i][k], "discard changed after call");
                }
        }

        for(i = 0; i < MAX_PLAYERS; ++i){
                assert(G->discardCount[i] == GCopy->discardCount[i], "discardCount changed after call");
        }

	for(i = 0; i < MAX_DECK; ++i){
		assert(G->playedCards[i] == GCopy->playedCards[i], "playedCards changed after call");
	}

	assert(G->playedCardCount == GCopy->playedCardCount, "playedCardCound changed after call");
}

int main(){
	struct gameState * G;	// state of the game held in this variable
	struct gameState *GCopy; 	// used to check for change of state
	int * kCards;	// holds kingdom cards that will initilize the game
//	int i; 		//iterator in loops

	printf("unittest3.c\n");

	/*************** TEST ONE *****************
 	* Should return appropriate card asked
 	* for in the handPos argument
 	* ****************************************/

	G = newGame();
/*	int * kCards = kingdomCards(adventurer, council_room, feast, gardens, mine,
					remodel, smithy, village, baron, great_hall);
	
	if(initializeGame(2, kCards, 1000, G) == -1){
		printf("Failed to initialize game \n");
		return 0;
	}
	
*/	
	// partially initilize the game while knowing state of each players hands
	G->numPlayers = 2;
	G->whoseTurn = 0;

	G->hand[0][0] = adventurer;
	G->hand[0][1] = council_room;
	G->hand[0][2] = feast;
	G->hand[0][3] = gardens;
	G->hand[0][4] = mine;
	G->handCount[0] += 5;
/*
	G->hand[1][0] = remodel;
	G->hand[1][1] = smithy;
	G->hand[1][2] = village;
	G->hand[1][3] = baron;
	G->hand[1][4] = great_hall;	
	G->handCount[1] += 5;
*/	
	// check if handCard returns appropriate cards
	assert(handCard(0, G) == adventurer, "adventurer card not returned");
	assert(handCard(1, G) == council_room, "council_room not returned");
	assert(handCard(2, G) == feast, "feast not returned");
	assert(handCard(3, G) == gardens, "gardens not returned");
	assert(handCard(4, G) == mine, "mine not returned");

	/***************** TEST TWO *******************
 	* Should check if handPos argument is within
 	* range
 	* ********************************************/

	assert(handCard(5, G) != adventurer, "returned adventurer when shouldn't have");
	assert(handCard(5, G) != council_room, "returned council_room when shouldn't have");
	assert(handCard(5, G) != feast, "returned feast when should have");
	assert(handCard(5, G) != gardens, "returned gardens when shouldn't have");
	assert(handCard(5, G) != mine, "returned mine when shouldn't have");

/* 	Cannot handle negative values
	assert(handCard(-1, G) != adventurer, "returned adventurer when shouldn't have");
        assert(handCard(-1, G) != council_room, "returned council_room when shouldn't have");
        assert(handCard(-1, G) != feast, "returned feast when should have");
        assert(handCard(-1, G) != gardens, "returned gardens when shouldn't have");
        assert(handCard(-1, G) != mine, "returned mine when shouldn't have");
*/
	free(G);

	/**************** TEST THREE **********************
 	* Doesn't change struct gameState variables
 	* ************************************************/
	G = newGame();
	GCopy = newGame();
	kCards = kingdomCards(adventurer, council_room, feast, gardens, mine,
                                        remodel, smithy, village, baron, great_hall);
        
        if(initializeGame(2, kCards, 1000, G) == -1){
                printf("Failed to initialize game, exiting \n");
                return 0;
        }
	
	memcpy(GCopy, G, sizeof(struct gameState));

	// call handCard() and see if it causes a change in gameState
	handCard(0, G);
	gameStateCompare(G, GCopy, "handCard(0, G)");

	handCard(1, G);
	gameStateCompare(G, GCopy, "handCard(1, G)");

	// clean-up
	free(G);
	free(GCopy);
	
	return 0;
}
