/*
Author: hutterj
Date: 2017.02.19
File: randontestadventurer.c
Purpose: perform tests on semi-random game state for adventurer card
	
Same after played:
	numPlayers
	supplyCount[]
	embargoTokens[]
	outpostPlayed
	outpostTurn
	whoseTurn
	phase
	numBuys
	Other players':
		hand[]
		handCount
		deck[]
		deckCount
		discard[]
		discardCount

Diff after played:
	numActions = preState -1
	hand:
		doesn't have adventurer from before
		has 3 new cards on top
	handCount = preState +2 (ie adventurer is discarded, then get 3 cards)
	deckCount[] = -3 from before (need to account for empty deck shuffle)
	discard now adventurer on top
	discardCount = preState +1
	playedCards[] top is adventurer
	playedCardcount = preState +1
	
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "randGameState.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>


#define CARD adventurer
#define INTO_HAND 2
#define ITERATIONS 10000

int oracle(struct gameState game);
int findHandPos(int hand[MAX_PLAYERS][MAX_HAND], int card, int thisPlayer);
void asserttrue(int condition, char* condName);


int main(int argc, char *argv[]){
	struct gameState G;
	int seed;
	int testIterations = ITERATIONS;
	int i;
	
	// use the seed provided or use time for seed
	if (argc > 1){
		seed = atoi(argv[1]);
		srand(seed);
	}
	else{
		srand(time(NULL));
	}
	
	printf("Begin testing for adventurer using seed %d\n", seed);
	
	
	
	for (i = 0; i < testIterations; i++){
		printf("\n--------------------BEGIN TEST %010d--------------------\n", i);
		
		// give us a semi-random game state
		
		//G = randGameState(seed, CARD);
		randGameState(&G, CARD);
		
		// oracle will perform test on that game state and printf the results
		oracle(G);
		
		printf("\n--------------------END TEST %010d--------------------\n|\n|\n|", i);
	}
	

	printf("\nEnd testing for adventurer\n");
	return 0;
}

int oracle(struct gameState game){
	struct gameState preState;
	int playCardStatus;
	int thisPlayer, handPos;
	int player;
	char msgFormatted[100];
	int shuffledDeckCount;
	
	// pre set up: set this player, gain card, find hand pos
	thisPlayer = whoseTurn(&game);
	asserttrue((gainCard(CARD, &game, INTO_HAND, thisPlayer)==0), "added card to hand");
	handPos = findHandPos(game.hand, CARD, thisPlayer);
	
	// copy game to preState, then play card
	memcpy(&preState, &game, sizeof(struct gameState));
	playCardStatus = playCard(handPos, -1, -1, -1, &game); 
	
	// if phase was not 0 or actions 0 or less, playCardStatus should have failed
	if (preState.phase != 0 || preState.numActions <= 0){
		asserttrue((playCardStatus == -1), "phase not action or too few actions, can't play");
		return 1;
	}
	else {
		asserttrue((playCardStatus == 0), "played card");
	}
	
	// check things that should be the same
	asserttrue((game.numPlayers == preState.numPlayers), "num players same");
	asserttrue((memcmp(game.supplyCount, preState.supplyCount, sizeof(game.supplyCount)) == 0), "supplyCount same");
	asserttrue((memcmp(game.embargoTokens, preState.embargoTokens, sizeof(game.embargoTokens)) == 0), "embargoTokens same");
	asserttrue((game.outpostPlayed == preState.outpostPlayed), "outpostPlayed same");
	asserttrue((game.outpostTurn == preState.outpostTurn), "outpostTurn same");
	asserttrue((game.whoseTurn == preState.whoseTurn), "whoseTurn same");
	asserttrue((game.phase == preState.phase), "phase same");
	asserttrue((game.numBuys == preState.numBuys), "numBuys same");
	
	// check other players' deck, hand, discard
	for (player = 0; player < MAX_PLAYERS; player++){
		
		if (player == preState.whoseTurn){
			continue;
		}
		
		// deck
		memset(msgFormatted, '\0', sizeof(msgFormatted));
		sprintf(msgFormatted, "player %d %s same", player, "deck");
		asserttrue((memcmp(game.deck[player], preState.deck[player], sizeof(preState.deck[player])) == 0), msgFormatted);
		
		// deck count
		memset(msgFormatted, '\0', sizeof(msgFormatted));
		sprintf(msgFormatted, "player %d %s same", player, "deckCount");
		asserttrue((game.deckCount[player] == preState.deckCount[player]), msgFormatted);
		
		// hand
		memset(msgFormatted, '\0', sizeof(msgFormatted));
		sprintf(msgFormatted, "player %d %s same", player, "hand");
		asserttrue((memcmp(game.hand[player], preState.hand[player], sizeof(preState.hand[player])) == 0), msgFormatted);
		
		// hand count
		memset(msgFormatted, '\0', sizeof(msgFormatted));
		sprintf(msgFormatted, "player %d %s same", player, "handCount");
		asserttrue((game.handCount[player] == preState.handCount[player]), msgFormatted);
		
		// discard
		memset(msgFormatted, '\0', sizeof(msgFormatted));
		sprintf(msgFormatted, "player %d %s same", player, "discard");
		asserttrue((memcmp(game.discard[player], preState.discard[player], sizeof(preState.discard[player])) == 0), msgFormatted);
		
		// hand count
		memset(msgFormatted, '\0', sizeof(msgFormatted));
		sprintf(msgFormatted, "player %d %s same", player, "discardCount");
		asserttrue((game.discardCount[player] == preState.discardCount[player]), msgFormatted);
	}
	
	// check things that should be different
	asserttrue((game.numActions+1 == preState.numActions), "actions -1 from preState");
	asserttrue((game.handCount[thisPlayer]-2 == preState.handCount[thisPlayer]), "handCount +2 from preState");
	asserttrue(((game.hand[thisPlayer][game.handCount[thisPlayer]-1] >= gold) 
		&& (game.hand[thisPlayer][game.handCount[thisPlayer]-2] >= gold)), "top 2 of hand are treasures");
	
	// account for empty deck having been shuffled or not
	if (preState.deckCount[thisPlayer] >= 3){
		asserttrue((game.deckCount[thisPlayer]+2 <= preState.deckCount[thisPlayer]), "deckCount -2 from preState (not shuffled)");
	}
	else {
		// drawing from deck caused reshuffle, do comparison from combo of preState deck and discard
		shuffledDeckCount = preState.deckCount[thisPlayer] + preState.discardCount[thisPlayer];
		asserttrue((game.deckCount[thisPlayer]+2 <= shuffledDeckCount), "deckCount -3 from preState (shuffled)");
	}
	
	asserttrue((game.discardCount[thisPlayer]-1 >= preState.discardCount[thisPlayer]), "discardCount +1 or more from preState");
	asserttrue((game.playedCardCount-1 == preState.playedCardCount), "playedCardCount +1 from preState");
	asserttrue((game.playedCards[game.playedCardCount-1] == CARD), "last played card is adventurer");
	asserttrue((game.discard[thisPlayer][game.discardCount[thisPlayer]-1] == CARD), "last discarded card is adventurer");
	
	// if the old top of deck wasn't adventurer, adventurer shouldn't be in same handpos as when it was played
	if (preState.deck[thisPlayer][preState.deckCount[thisPlayer]-1] != CARD){
		asserttrue((game.hand[thisPlayer][handPos] != CARD), "adventurer's preState hand pos no longer has adventurer");
	}
	
		
	
	
	return 1;
}


// return handPos of a given card for a given player
int findHandPos(int hand[MAX_PLAYERS][MAX_HAND], int card, int thisPlayer){
	int i;
	
	for (i = 0; i < MAX_HAND; i++){
		if (hand[thisPlayer][i] == card){
			return i;
		}
	}
	
	// card not in hand
	return -10;
}

/*
Name: asserttrue
Purpose:  use something like assert to check conditions
but still be able to collect coverage
*/
void asserttrue(int condition, char* condName){
	if (condition){
		printf("Test: %-50s success.\n", condName);
	}
	else {
		printf("Test: %-50s FAIL.\n", condName);
	}
	return;
}