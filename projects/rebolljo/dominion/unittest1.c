//Joseph Rebolledo
//CS362-400 Assignment 3
//Test whoseTurn()

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

	printf("---Now beginning unit test on whoseTurn()--- \n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	int seed = rand() % 5;
	int numberPlayers = 2;

	initializeGame(numberPlayers,kingdomCards,seed,&Game);

	//Set the whoseTurn property to an increasing value for the gameState, then test to see if whoseTurn() returns the correct value
	int j = 0;
	while(j < 5){
		int testTurn = j;
		Game.whoseTurn = testTurn;
		int currentTurn = whoseTurn(&Game);
		printf("Testing that turn has iterated to next player: \n");
		newassert(currentTurn == testTurn);
		j++;
	}

	printf("End whoseTurn() unit test \n");
	return 0;
}