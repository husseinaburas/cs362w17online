/*cardtest4.c*/

#include <dominion.h>
#include <dominion_helpers.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <rngs.h>
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
*/
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