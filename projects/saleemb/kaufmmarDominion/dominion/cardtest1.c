/* Author: Bilal Saleem
 * Date: 2/1/17
 * Card being tested: smithy
 * Card description: this card allows you to draw +3 cards from your deck.
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

void gameStateCompare(struct gameState * G, struct gameState * GCopy, char * msg) {
	int i, k; 	// loop iterators

//	printf("%s \n", msg);
	
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

	// expected to change if functioning correctly
	//assert(G->numBuys == GCopy->numBuys , "numBuys changed after call");
/*	expected to change if functioning correctly	
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
/* expected to change
	for(i = 0; i < MAX_DECK; ++i){
		assert(G->playedCards[i] == GCopy->playedCards[i], "playedCards changed after call");
	}
	 
	 assert(G->playedCardCount == GCopy->playedCardCount, "playedCardCount changed after call");
*/
}

int main(){

	struct gameState * G;		// state of the game
	struct gameState * GCopy;	// used for change in state comparisons
	int * kCards;			// hold the set of kingdom cards to be used during the game
	int numPlayers = 2;
	int playWhoseTurn = 0;		// player identfier for person who will play the card
	int coinBonus = 0;

	printf("cardtest1.c\n");

	// initialize the game and make two copies of the game state
	G = newGame();
	GCopy = newGame();
	
	kCards = kingdomCards(adventurer, council_room, feast, gardens, remodel,
				smithy, village, baron, ambassador, treasure_map);	

	initializeGame(numPlayers, kCards, 1000, G);
	
	memcpy(GCopy, G, sizeof(struct gameState));
	
	/****************** TEST ONE *************************
 	* Should cause the handCount variable to increase by 3
 	******************************************************/
	printf("--TEST ONE--\n");
	useSmithy(0, playWhoseTurn, G);
	gameStateCompare(G, GCopy, "useSmithy(0, playWhoseTurn, G):");
	
	// reset G
	memcpy(G, GCopy, sizeof(struct gameState));

	/**********************************  TEST TWO *****************************************
	* six things from gameState not compared in above gameStateCompare because they were
	* expected to change.  Those six things are: handCount, playedCardCount, 
	* playedCards, hand, deck, and deckCount. They will be tested to see if they match
	* expected values.
	* ************************************************************************************/
	printf("\n--TEST TWO--\n");
	useSmithy(0, playWhoseTurn, G); 
	
	// numBuys shouldn't decrease by 1
//	assert(G->numBuys == (GCopy->numBuys -1), "numBuys not decremented by 1");
	// handCount should decrease by 2 (+3 drawn cards, -1 played card)
	assert(G->handCount[playWhoseTurn] == (GCopy->handCount[playWhoseTurn] + 3 - 1), "handCount not incremented by 2 (+3 - 1)") ;
	// playedCardCount should increase by 1
	assert(G->playedCardCount == (GCopy->playedCardCount + 1), "playedCardCount not incremented");
	// playedCard[0] should have smithy as its value
	assert(G->playedCards[0] == smithy, "smithy has not been placed in played cards");
	// deckCount should decrease by 3
	assert(G->deckCount[playWhoseTurn] == (GCopy->deckCount[playWhoseTurn] - 3), "deckCount not decremented by 3");

	return 0;

}
