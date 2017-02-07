/*cardtest3.c*/
#include <dominion.h>
#include <dominion_helpers.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <rngs.h>
#include <stdlib.h>

#define TESTCARD "salvager"

/* Description: If a player plays a salvager card, the player gains the ability to make
   one extra buy in the buying phase. The player then must trash a card from their hand and
   gains the number of coins equal to the cost of the trashed card to use in the buying phase.
   Pre-Conditions: state->phase == 0, the player must be in the action phase
                   state->numActions > 0, the player must have an action to play
                   The name of the card must be salvager and the value must be between 7 and 26
                   Choice1 must be a valid card in the players hand
   Post-Conditions: state->numActions must be >= 0 because the number of actions isn't changed in this function
                    state->numBuys should be increased by 1
                    The card represented by choice1 should not be in the players deck
                    The salvager card should be the last discarded card
int playSalvager(struct gameState *state, int currentPlayer, int choice1, int handPos, int card){
   

   //+1 buy
    state->numBuys++;
    
    if (choice1 == smithy){ //BUG
      //gain coins equal to trashed card
      state->coins = state->coins + getCost( handCard(choice1, state) );
      //trash card
      discardCard(choice1, currentPlayer, state, 0);  //BUG
    }
      
    //discard  salvager card
    discardCard(handPos, currentPlayer, state, 0);


    return 0;
}

//Helper function for playSalvager
//Verifies that a certain card is in the given players hand. If the card is in the players hand
// returns 0, else returns 1
int inHand(struct gameState *state, int currentPlayer, int choice1){
  int i;

    for (i = 0; i < state->handCount[currentPlayer]; i++){
      if (state->hand[currentPlayer][i] == choice1){
          return 0;
      }
    }
    return 1;
}
*/

int main(){

	int i;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// ----------- TEST 1: Test phase before and after is 0 -----------
	// ----------- TEST 2: Test number of actions before is > 1 -----------
	// ----------- TEST 3: Test number of actions after decreased by 1 -----------
	// ----------- TEST 4: Test number of actions after is greater than 0 -----------
	// ----------- TEST 5: Test handCount of player decreased by 2 -----------
	// ----------- TEST 6: Test that the Salvager card is in the discard pile -----------
	// ----------- TEST 7: Test that the players total number of cards has decreased by 1 -----------
	// ----------- TEST 8: Test that the number of coins has increased by the value of choice 1 -----------
	// ----------- TEST 9: Test that the number of buys has increased by 1 -----------
	// ----------- TEST 10: Test that the number of victory (province, estate, duchy) cards has not changed -----------
	// ----------- TEST 11: Test that number of kingdom cards (supply...) has not changed -----------
	return 0;
}