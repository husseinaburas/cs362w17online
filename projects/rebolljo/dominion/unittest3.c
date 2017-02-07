//Joseph Rebolledo
//CS362-400 Assignment 3
//Test updateCoins()

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("---Now beginning unit test on updateCoins()--- \n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	int seed = rand() % 5;
	int numberPlayers = 2;

	initializeGame(numberPlayers,kingdomCards,seed,&Game);


	//Testing updateCoins() with mixture of copper, silver, and gold cards
	printf("Beginning properly updating mixture of copper, silver, and gold test: \n");
	Game.coins = 0;

	Game.whoseTurn = 0;

	Game.handCount[0] = 3;
	Game.hand[0][0] = copper;
	Game.hand[0][1] = silver;
	Game.hand[0][2] = gold;

	updateCoins(0,&Game,0);

	printf("Testing that coins have been properly updated: \n");
	newassert(Game.coins == 6);

	//Treasure plus bonus
	printf("Beginning properly updating treasure cards with bonus test: \n");

	Game.coins = 0;

	Game.whoseTurn = 0;
	Game.handCount[0] = 3;
	Game.hand[0][0] = copper;
	Game.hand[0][1] = silver;
	Game.hand[0][2] = gold;

	updateCoins(0,&Game,1);

	printf("Testing that coins have been properly updated: \n");
	newassert(Game.coins == 7);

	//No treasure cards, no bonus
	printf("Beginning properly updating with no treasure or bonus test: \n");

	Game.coins = 0;

	Game.whoseTurn = 0;
	Game.handCount[0] = 1;
	Game.hand[0][0] = smithy;
	
	updateCoins(0,&Game,0);

	printf("Testing that coins have been properly updated: \n");
	newassert(Game.coins == 0);

	printf("End updateCoins() unit test\n");
	return 0;
}