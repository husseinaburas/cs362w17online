/*cardtest2.c*/
#include <dominion.h>
#include <dominion_helpers.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <rngs.h>
#include <stdlib.h>

#define TESTCARD "smithy"


/*Pre-Conditions: state->phase == 0, the player must be in the action phase
                   state->numActions > 0, the player must have an action to play
                   The name of the card must be smithy and the value must be between 7 and 26
   Post-Conditions: state->handCount[currentPlayer] should have increased by 2
                    state->numActions must be >= 0 because the number of actions is not changed in this function
                    The smithy card should be discarded


int playSmithy(struct gameState *state, int currentPlayer, int handPos, int card){


      int i;
      int startNumCards = state->handCount[currentPlayer];
      printf("start num cards: %d\n", startNumCards);
      //+3 Cards
      for (i = 0; i <= 3; i++) //BUG
        {
          drawCard(currentPlayer, state);
        }
            
      //discard smithy card from hand
      discardCard(handPos, currentPlayer, state, 0);
      printf("end num cards: %d\n", state->handCount[currentPlayer]);

      return 0;
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
	// ----------- TEST 5: Test handCount of player increased by 2 (+ 3 - smithy) -----------
	// ----------- TEST 6: Test that the smithy card is in the discard pile -----------
	// ----------- TEST 7: Test that the players total number of cards has not changed -----------
	// ----------- TEST 8: Test that the number of victory (province, estate, duchy) cards has not changed -----------
	// ----------- TEST 9: Test that number of kingdom cards (supply...) has not changed -----------
	return 0;
}
