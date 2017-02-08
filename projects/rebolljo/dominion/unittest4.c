//Joseph Rebolledo
//CS362-400 Assignment 3
//Test discardCard()

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("---Now beginning unit test on discardCard()--- \n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	int seed = rand() % 5;
	int numberPlayers = 2;

	initializeGame(numberPlayers,kingdomCards,seed,&Game);

	//Test discard last card in hand
	printf("Testing discarding last card in hand: \n");

	Game.whoseTurn = 0;

	Game.handCount[0] = 1;
	Game.hand[0][0] = curse;

	discardCard(0,0,&Game,0);

	printf("Testing that hand is now empty: \n");
	newassert(Game.handCount[0] == 0);

	//Test discarding middle card
	printf("Testing discarding middle card in hand: \n");

	Game.whoseTurn = 0;

	Game.handCount[0] = 3;
	Game.hand[0][0] = curse;
	Game.hand[0][1] = estate;
	Game.hand[0][2] = minion;

	discardCard(1,0,&Game,0);

	printf("Testing that handCount is properly updated: \n");
	newassert(Game.handCount[0] == 2);

	//Test discarding first card in hand
	printf("Testing discarding first card in hand: \n");

	Game.whoseTurn = 0;

	Game.handCount[0] = 3;
	Game.hand[0][0] = salvager;
	Game.hand[0][1] = silver;
	Game.hand[0][2] = smithy;

	discardCard(0,0,&Game,0);

	printf("Testing that handCount is properly updated: \n");
	newassert(Game.handCount[0]==2);

	printf("End discardCard() unit test\n");
	return 0;
}