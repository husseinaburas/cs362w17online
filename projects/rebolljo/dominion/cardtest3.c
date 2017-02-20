//Joseph Rebolledo
//CS362-400 Assignment 3
//Test steward

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("---Now beginning unit test on steward card--- \n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	int seed = rand() % 5;
	int numberPlayers = 2;
	int handPosition = 0;
	int bonus = 0;

	initializeGame(numberPlayers,kingdomCards,seed,&Game);

	//Set player 2 to have 5 cards in deck
	int m = 0;
	while(m<5){
		drawCard(1,&Game);
		m++;
	}

	//Test choice 1: +2 cards
	printf("Testing choice 1: +2 cards: \n");

	Game.whoseTurn = 0;
	Game.handCount[0] = 1;
	Game.hand[0][0] = steward;

	//Play card and test after effects
	playCard(0,1,0,0,&Game);

	printf("Testing player1 handcount: \n");
	newassert(numHandCards(&Game) == 2);

	printf("Testing player 2's handCount: \n");
	newassert(Game.handCount[1] == 5);

	//Test choice 2: +2 coins
	printf("Testing choice 2: +2 coins: \n");

	Game.whoseTurn = 0;
	Game.handCount[0] = 1;
	Game.hand[0][0] = steward;

	playCard(0,2,0,0,&Game);

	printf("Testing player1 goldcount: \n");
	newassert(Game.coins == 2);

	//Test choice 3: trash two cards
	printf("Testing choice 3: trash two cards \n");

	Game.whoseTurn = 0;
	Game.handCount[0] = 5;
	Game.hand[0][0] = steward;
	Game.hand[0][1] = smithy;
	Game.hand[0][2] = adventurer;
	Game.hand[0][3] = estate;
	Game.hand[0][4] = duchy;

	cardEffect(steward,3,1,3,&Game,handPosition,&bonus);

	printf("Testing player1 handCount: \n");
	newassert(numHandCards(&Game) == 2);

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

	printf("End steward unit test \n");
	return 0;
}