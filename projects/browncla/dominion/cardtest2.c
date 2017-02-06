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
*/

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