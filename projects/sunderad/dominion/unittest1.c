#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int main(int argc, char const *argv[])
{
	int i, j;
	int errorFlag[3]={0,0,0};
	int players=2;
	int seed=999;
	struct gameState twoPlayerG, threePlayerG, fourPlayerG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	printf("-----------------------------------------------------------------------\n");
	printf("Running Unit Test 1: Initialize Game Function\n\n");
	printf("Testing initializeGame(), 2 Players\n");
	//-----------------------------------------------------------------------------
	//Test a two player game initialization
	//-----------------------------------------------------------------------------
	initializeGame(players, k, seed, &twoPlayerG);
	if(twoPlayerG.numPlayers != 2){
		printf("Two Player Game: Player Count Error\n");
		errorFlag[0]++;
	}

	//Check Supplies Counts
	//Curse Cards
	if(twoPlayerG.supplyCount[curse] != 10){
		printf("Two Player Game: Curse Card Supply Count Error\n");
		errorFlag[0]++;
	}
	//Victory Cards
	if(twoPlayerG.supplyCount[estate] != 8){
		printf("Two Player Game: Estate Card Supply Count Error\n");
		errorFlag[0]++;
	}
	if(twoPlayerG.supplyCount[duchy] != 8){
		printf("Two Player Game: Duchy Card Supply Count Error\n");
		errorFlag[0]++;
	}
	if(twoPlayerG.supplyCount[province] != 8){
		printf("Two Player Game: Province Card Supply Count Error\n");
		errorFlag[0]++;
	}
	//Treasure Cards
	if(twoPlayerG.supplyCount[copper] != 46){
		printf("Two Player Game: Copper Card Supply Count Error\n");
		errorFlag[0]++;
	}
	if(twoPlayerG.supplyCount[silver] != 40){
		printf("Two Player Game: Silver Card Supply Count Error\n");
		errorFlag[0]++;
	}
	if(twoPlayerG.supplyCount[gold] != 30){
		printf("Two Player Game: Gold Card Supply Count Error\n");
		errorFlag[0]++;
	}
	//Kingdom Cards
	for(i=0; i<10; i++){
		if(twoPlayerG.supplyCount[k[i]] != 10){
			printf("Two Player Game: Kingdom Card Supply Count Error, Array k: Position %d\n", i);
			errorFlag[0]++;
		}
	}

	//Check Starting Decks
	for (i=0; i < players; i++){
		if(twoPlayerG.deckCount[i] != 10){
			if(twoPlayerG.deckCount[i] == 5 && i == 0){
				continue;
			}
			printf("Two Player Game: Starting Deck Supply Count Error, Player %d\n", i);
			errorFlag[0]++;
		}
      	for (j=0; j<10; j++){
      		if(twoPlayerG.deck[i][j] != estate && twoPlayerG.deck[i][j] != copper){
      			printf("Two Player Game: Starting Deck Supply Error, Not a Copper Or Estate Card, Player %d\n", i);
      			errorFlag[0]++;
      		}	  	
		}
    }

    //Check Player Hand Size
    if(twoPlayerG.handCount[0] != 5){
    	printf("Two Player Game: Starting Hand Count Error, Player 1\n");
    	errorFlag[0]++;
    }
    if(twoPlayerG.handCount[1] != 0){
    	printf("Two Player Game: Starting Hand Count Error, Player 2\n");
    	errorFlag[0]++;
    }

    printf("Two Player Game Test Complete, %d Errors\n\n", errorFlag[0]);

	//-----------------------------------------------------------------------------
	//Test a three player game initialization
	//-----------------------------------------------------------------------------
	printf("Testing initializeGame(), 3 Players\n");
	initializeGame((players+1), k, seed, &threePlayerG);
	if(threePlayerG.numPlayers != 3){
		printf("Three Player Game: Player Count Error\n");
		errorFlag[1]++;
	}

	//Check Supplies Counts
	//Curse Cards
	if(threePlayerG.supplyCount[curse] != 20){
		printf("Three Player Game: Curse Card Supply Count Error\n");
		errorFlag[1]++;
	}
	//Victory Cards
	if(threePlayerG.supplyCount[estate] != 12){
		printf("Three Player Game: Estate Card Supply Count Error\n");
		errorFlag[1]++;
	}
	if(threePlayerG.supplyCount[duchy] != 12){
		printf("Three Player Game: Duchy Card Supply Count Error\n");
		errorFlag[1]++;
	}
	if(threePlayerG.supplyCount[province] != 12){
		printf("Three Player Game: Province Card Supply Count Error\n");
		errorFlag[1]++;
	}
	//Treasure Cards
	if(threePlayerG.supplyCount[copper] != 39){
		printf("Three Player Game: Copper Card Supply Count Error\n");
		errorFlag[1]++;
	}
	if(threePlayerG.supplyCount[silver] != 40){
		printf("Three Player Game: Silver Card Supply Count Error\n");
		errorFlag[1]++;
	}
	if(threePlayerG.supplyCount[gold] != 30){
		printf("Three Player Game: Gold Card Supply Count Error\n");
		errorFlag[1]++;
	}
	//Kingdom Cards
	for(i=0; i<10; i++){
		if(threePlayerG.supplyCount[k[i]] != 10){
			printf("Three Player Game: Kingdom Card Supply Count Error, Array k: Position %d\n", i);
			errorFlag[1]++;
		}
	}

	//Check Starting Decks
	for (i=0; i < (players+1); i++){
		if(threePlayerG.deckCount[i] != 10){
			if(threePlayerG.deckCount[i] == 5 && i == 0){
				continue;
			}
			printf("Three Player Game: Starting Deck Supply Count Error, Player %d\n", i);
			errorFlag[1]++;
		}
      	for (j=0; j<10; j++){
      		if(threePlayerG.deck[i][j] != estate && threePlayerG.deck[i][j] != copper){
      			printf("Three Player Game: Starting Deck Supply Error, Not a Copper Or Estate Card, Player %d\n", i);
      			errorFlag[1]++;
      		}	  	
		}
    }

    //Check Player Hand Size
    if(threePlayerG.handCount[0] != 5){
    	printf("Three Player Game: Starting Hand Count Error, Player 1\n");
    	errorFlag[1]++;
    }
    if(threePlayerG.handCount[1] != 0){
    	printf("Three Player Game: Starting Hand Count Error, Player 2\n");
    	errorFlag[1]++;
    }
    if(threePlayerG.handCount[2] != 0){
    	printf("Three Player Game: Starting Hand Count Error, Player 3\n");
    	errorFlag[1]++;
    }

    printf("Three Player Game Test Complete, %d Errors\n\n", errorFlag[1]);

	//-----------------------------------------------------------------------------
	//Test a four player game initialization
	//-----------------------------------------------------------------------------
	printf("Testing initializeGame(), 4 Players\n");
	initializeGame((players+2), k, seed, &fourPlayerG);
	if(fourPlayerG.numPlayers != 4){
		printf("Four Player Game: Player Count Error\n");
		errorFlag[2]++;
	}

	//Check Supplies Counts
	//Curse Cards
	if(fourPlayerG.supplyCount[curse] != 30){
		printf("Four Player Game: Curse Card Supply Count Error\n");
		errorFlag[2]++;
	}
	//Victory Cards
	if(fourPlayerG.supplyCount[estate] != 12){
		printf("Four Player Game: Estate Card Supply Count Error\n");
		errorFlag[2]++;
	}
	if(fourPlayerG.supplyCount[duchy] != 12){
		printf("Four Player Game: Duchy Card Supply Count Error\n");
		errorFlag[2]++;
	}
	if(fourPlayerG.supplyCount[province] != 12){
		printf("Four Player Game: Province Card Supply Count Error\n");
		errorFlag[2]++;
	}
	//Treasure Cards
	if(fourPlayerG.supplyCount[copper] != 32){
		printf("Four Player Game: Copper Card Supply Count Error\n");
		errorFlag[2]++;
	}
	if(fourPlayerG.supplyCount[silver] != 40){
		printf("Four Player Game: Silver Card Supply Count Error\n");
		errorFlag[2]++;
	}
	if(fourPlayerG.supplyCount[gold] != 30){
		printf("Four Player Game: Gold Card Supply Count Error\n");
		errorFlag[2]++;
	}	
	//Kingdom Cards
	for(i=0; i<10; i++){
		if(fourPlayerG.supplyCount[k[i]] != 10){
			printf("Four Player Game: Kingdom Card Supply Count Error, Array k: Position %d\n", i);
			errorFlag[2]++;
		}
	}

	//Check Starting Decks
	for (i=0; i < (players+2); i++){
		if(fourPlayerG.deckCount[i] != 10){
			if(fourPlayerG.deckCount[i] == 5 && i == 0){
				continue;
			}
			printf("Four Player Game: Starting Deck Supply Count Error, Player %d\n", i);
			errorFlag[2]++;
		}
      	for (j=0; j<10; j++){
      		if(fourPlayerG.deck[i][j] != estate && fourPlayerG.deck[i][j] != copper){
      			printf("Four Player Game: Starting Deck Supply Error, Not a Copper Or Estate Card, Player %d\n", i);
      			errorFlag[2]++;
      		}	  	
		}
    }

    //Check Player Hand Size
    if(fourPlayerG.handCount[0] != 5){
    	printf("Four Player Game: Starting Hand Count Error, Player 1\n");
    	errorFlag[2]++;
    }
    if(fourPlayerG.handCount[1] != 0){
    	printf("Four Player Game: Starting Hand Count Error, Player 2\n");
    	errorFlag[2]++;
    }
    if(fourPlayerG.handCount[2] != 0){
    	printf("Four Player Game: Starting Hand Count Error, Player 3\n");
    	errorFlag[2]++;
    }
    if(fourPlayerG.handCount[3] != 0){
    	printf("Four Player Game: Starting Hand Count Error, Player 4\n");
    	errorFlag[2]++;
    }

    printf("Four Player Game Test Complete, %d Errors\n\n", errorFlag[2]);


    printf("Unit Test 1 Complete: %d Total Errors\n",(errorFlag[0]+errorFlag[1]+errorFlag[2]));
    printf("-----------------------------------------------------------------------\n");

	return 0;
}










