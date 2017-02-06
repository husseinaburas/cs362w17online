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
*/
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