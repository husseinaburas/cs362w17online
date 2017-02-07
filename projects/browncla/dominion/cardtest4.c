/*cardtest4.c*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

/* Description: If a player plays a village card, the player draws one card from his deck. The player
   does not need to discard this card until the clean up phase. He may use the cards to buy items
   unless he has another action left. The player also gains two actions. If he had one action to start
   and then uses a village card, then he has two more actions that he can play.
   Pre-Conditions: state->phase == 0, the player must be in the action phase
                   state->numActions > 0, the player must have an action to play
                   The name of the card must be village and the value must be between 7 and 26
   Post-Conditions: state->handCount[currentPlayer] should stay the same
                    state->numActions must be increased by 2 and must be >= 0 because player gained 2 action cardss
                    The village card should be discarded

int playVillage(struct gameState *state, int currentPlayer, int handPos, int card){
   

       int origNumActions = state->numActions;
       int startNumCards = state->handCount[currentPlayer];
     //+1 Card
      drawCard(currentPlayer, state);
      
      //+2 Actions
      state->numActions = state->numActions + 2;
      
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
}
*/

//Own assert function
int asserttrue(int input, int number){
	if (input){
		printf("\tTEST %d SUCCESSFUL\n", number);
	}
	else
		printf("\tTEST %d FAILED\n", number);
	return 0;
}

int main(){

	int i;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, salvager, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// ----------- TEST 1: Test phase before and after is 0 -----------
	// ----------- TEST 2: Test number of actions before is > 1 -----------
	// ----------- TEST 3: Test number of actions after increased by 2 -----------
	// ----------- TEST 4: Test number of actions after is greater than 0 -----------
	// ----------- TEST 5: Test handCount of player has not changed -----------
	// ----------- TEST 6: Test that the village card is in the discard pile -----------
	// ----------- TEST 7: Test that the players total number of cards not changed -----------
	// ----------- TEST 8: Test that the number of victory (province, estate, duchy) cards has not changed -----------
	// ----------- TEST 9: Test that number of kingdom cards (supply...) has not changed -----------
	return 0;
}