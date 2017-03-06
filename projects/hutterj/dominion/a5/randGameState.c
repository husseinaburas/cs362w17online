/*
Author: hutterj
Date: 2017.02.19
File: randGameState.c
Purpose: Generate a semi-random game state

Note: srand seeded in main of randomtestcard file.
		
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "randGameState.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MIN_PLAYERS 2


int randGameState(struct gameState *game, int needCard){
	//struct gameState game;
	int i, j;
	int cardCount;


	game->numPlayers = (rand() % (MAX_PLAYERS-MIN_PLAYERS)) + MIN_PLAYERS;
	for (i = 0; i < treasure_map+1; i++){
		game->supplyCount[i] = (rand() % 30) +2;
		game->embargoTokens[i] = rand() % 3;
	}
	game->outpostPlayed = rand() % 2;
	if (game->outpostPlayed == 1){
		game->outpostTurn = rand() % game->numPlayers;
	}
	else {
		game->outpostTurn = 0;
	}
	
	game->whoseTurn = rand() % game->numPlayers;
	game->phase = rand() % 3;
	game->numActions = rand() % 3;
	game->coins = rand() % 10;
	game->numBuys = rand() % 10;
	
	// determine hand/deck/discard for each player
	for (i = 0; i < game->numPlayers; i++){
		// deck
		game->deckCount[i] = rand() % MAX_DECK;
		cardCount = game->deckCount[i];
		for (j = 0; j < game->deckCount[i]; j++){
			game->deck[i][j] = rand() % (treasure_map+1);
		}
		
		// hand
		game->handCount[i] = (rand() % MAX_HAND-1) + 1;
		for (j = 0; j < game->handCount[i]; j++){
			game->hand[i][j] = rand() % (treasure_map+1);
		}
		
		// discard
		if (cardCount == MAX_DECK){
			game->discardCount[i] = 0;
		}
		else {
			game->discardCount[i] = rand() % (MAX_DECK - cardCount);
			for (j = 0; j < game->discardCount[i]; j++){
				game->discard[i][j] = rand() % (treasure_map+1);
			}
		}
		
	}
	
	game->playedCardCount = rand() % MAX_DECK;
	for (i = 0; i < game->playedCardCount; i++){
		// played cards are actions
		game->playedCards[i] = (rand() % (treasure_map-adventurer)) + adventurer;
	}
	
	return 0;
}