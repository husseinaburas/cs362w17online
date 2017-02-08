//Joseph Rebolledo
//CS362-400 Assignment 3
//Test salvager

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("---Now beginning unit test on salvager card--- \n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	int seed = rand() % 5;
	int numberPlayers = 2;
	int bonus = 0;

	initializeGame(numberPlayers,kingdomCards,seed,&Game);

	//Set player 2 to have 5 cards in deck
	int m = 0;
	while(m<5){
		drawCard(1,&Game);
		m++;
	}

	//Test salvager by salvaging minion
	printf("Testing salvaging minion: \n");

	Game.whoseTurn = 0;
	Game.handCount[0] = 2;
	Game.hand[0][0] = salvager;
	Game.hand[0][1] = minion;
	Game.numBuys = 0;
	Game.coins = 0;

	//Play card and test after effects
	cardEffect(salvager,1,0,0,&Game,0,&bonus);

	printf("Testing player1 buyCount: \n");
	newassert(Game.numBuys == 1);
	printf("Testing player1 goldcount: \n");
	newassert(Game.coins == 5);
	printf("Testing player1 handCount: \n");
	newassert(numHandCards(&Game) == 0);

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

	printf("End salvager unit test\n");
	return 0;
}