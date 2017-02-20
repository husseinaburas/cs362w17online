//random tests for council room card (playCouncil_Room function)

#include "dominion.h"

#define CARD_NAME "Council Room"
#define CARD_ENUM council_room
#define CARD_FUNC &playCouncil_Room
//playCouncil_Room requires handPos as an argument
#define USE_HAND_POS 1



//function to mock what playCouncil_Room should do
//adds 1 to buy, gives player 4 cards and gives everyone else 1 card
int mockCardAction(int currentPlayer, struct gameState *state, int handPos){
	//give current player 4 cards
	//and everyone else 1 card
	int i;
	for(i = 0; i < state->numPlayers; ++i){
		//give everyone 1 card
		drawCard(i, state);
		//if current player, give 3 more cards for total of 4
		if(i == currentPlayer){
			drawCard(i, state);
			drawCard(i, state);
			drawCard(i, state);
		}
	}

	//add 1 to number of buys
	state->numBuys++;

	//discard council room from player's hand
	discardCard(handPos, currentPlayer, state, 0);

	return 0;
}


#include "random_test_runner.c"