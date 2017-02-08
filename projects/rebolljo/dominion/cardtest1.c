//Joseph Rebolledo
//CS362-400 Assignment 3
//Test smithy

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("---Now beginning unit test on smithy card--- \n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	int seed = rand() % 5;
	int numberPlayers = 2;

	initializeGame(numberPlayers,kingdomCards,seed,&Game);
	
	printf("Testing that player correctly gains 3 cards: \n");

	//Set the current turn to first player
	//Set their hand to have one card, set that card to smithy
	//Set the first players deck so as to have 5 cards to later test

	Game.whoseTurn = 0;
	Game.handCount[0] = 1;
	Game.hand[0][0] = smithy;
	Game.deckCount[0] = 5;

	//Set player 2 to have 5 cards in deck
	int m = 0;
	while(m<5){
		drawCard(1,&Game);
		m++;
	}
	
	//Play card and test after effects
	playCard(0,0,0,0,&Game);

	//Testing player 1
	printf("Testing player 1's hand count: \n");
	newassert(numHandCards(&Game) == 3);
	printf("Testing player 1's deck count: \n");
	newassert(Game.deckCount[0] == 2);
	printf("Testing whose turn it is: \n");
	newassert(whoseTurn(&Game) ==  0);

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

	printf("End smithy unit test\n");
	return 0;
}