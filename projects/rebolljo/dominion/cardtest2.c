//Joseph Rebolledo
//CS362-400 Assignment 3
//Test adventurer

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("---Now beginning unit test on adventurer card--- \n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	int seed = rand() % 5;
	int numberPlayers = 2;

	initializeGame(numberPlayers,kingdomCards,seed,&Game);

	Game.whoseTurn = 0;
	Game.handCount[0] = 1;
	Game.hand[0][0] = adventurer;
	Game.deckCount[0] = 5;

	//Set player 2 to have 5 cards in deck
	int m = 0;
	while(m<5){
		drawCard(1,&Game);
		m++;
	}

	printf("Testing when treasure cards are alternating with other cards in the deck: \n");

	//Filling deck with alternating treasure cards
	Game.deck[0][0] = copper;
	Game.deck[0][2] = copper;
	Game.deck[0][4] = copper;

	Game.deck[0][1] = minion;
	Game.deck[0][3] = salvager;

	//Play card and test after affects
	playCard(0,0,0,0, &Game);

	//Testing player 1
	printf("Testing whether coin count is correct:\n");
	newassert(Game.coins == 2);
	printf("Testing player1 hand count: \n");
	newassert(numHandCards(&Game) == 3);
	printf("Testing player1 discard count: \n");
	newassert(Game.discardCount[0] == 1);
	printf("Testing player1 deckCount count: \n");
	newassert(Game.deckCount[0] == 2);
	printf("Testing whose turn it is: \n");
	newassert(whoseTurn(&Game) == 0);

	endTurn(&Game);

	//Testing player 2 status
	printf("Testing player 2's handCount: \n");
	newassert(numHandCards(&Game) == 5);

	//Testing supply count of victory and curse cards
	printf("Testing curse cards supply count: \n");
	newassert(Game.supplyCount[curse] == 10);
	printf("Testing province cards supply count:: \n");
	newassert(Game.supplyCount[province] == 8);
	printf("Testing estate cards supply count: \n");
	newassert(Game.supplyCount[estate] == 8);
	printf("Testing duchy cards supply count: \n");
	newassert(Game.supplyCount[duchy] == 8);

	printf("End adventurer unit test \n");
	return 0;
}