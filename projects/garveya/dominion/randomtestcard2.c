//random tests for smithy card (playSmithy function)

#include "dominion.h"

#define CARD_NAME "Smithy"
#define CARD_ENUM smithy
#define CARD_FUNC &playSmithy
//playSmithy requires handPos as an argument
#define USE_HAND_POS 1



//function to mock what playSmithy should do
//gives current player 3 cards
int mockCardAction(int currentPlayer, struct gameState *state, int handPos){
	//give player 3 cards
	drawCard(currentPlayer, state);
	drawCard(currentPlayer, state);
	drawCard(currentPlayer, state);

	//discard smithy from player's hand
	discardCard(handPos, currentPlayer, state, 0);

	return 0;
}


#include "random_test_runner.c"