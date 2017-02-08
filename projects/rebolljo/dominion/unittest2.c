//Joseph Rebolledo
//CS362-400 Assignment 3
//Test shuffle()

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("Now beginning unit test on shuffle()---\n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	int seed = rand() % 5;
	int numberPlayers = 2;
	int check;
	initializeGame(numberPlayers,kingdomCards,seed,&Game);

	//Testing shuffle() with 0 cards in deck
	printf("Testing when deck count is 0 : \n");
	Game.deckCount[0] = 0;
	check = shuffle(0,&Game);
	newassert(check == -1);

	//Testing shuffle() with >0 cards in deck
	printf("Testing when deck count is > 0 : \n");
	Game.deckCount[0] = 1;
	check = shuffle(0,&Game);
	newassert(check == 0);

	printf("End shuffle() unit test\n");
	return 0;
}