/*cardtest1.c*/
#include <dominion.h>
#include <dominion_helpers.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <rngs.h>
#include <stdlib.h>

#define TESTCARD "adventurer"

/* Pre-Conditions: state->phase == 0, the player must be in the action phase
                         state->numActions > 0, the player must have an action to play
                         The name of the card must be adventurer and the value must be between 7 and 26
         Post-Conditions: state->handCount[currentPlayer] should have increased by the number of drawn treasures up to 2 treasure cards
                          state->numActions must be >= 0 because the number of actions is not changed in this function
                          The adventurer card should be in the discard pile
      
int playAdventurer(struct gameState *state, int currentPlayer, int handPos, int card){

       int z=0;
       int drawntreasure = 0;
       int temphand[MAX_HAND];
       int startNumCards = state->handCount[currentPlayer]; // storing the starting number of cards for test
       
      // drawn treasure is the number of cards that have been drawn that are treasure cards
      // keep going until 2 treasure cards are drawn
      while(drawntreasure<1){ //BUG
        //if the deck is empty we need to shuffle discard and add to deck
        if (state->deckCount[currentPlayer] <1){
          shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        int cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
          drawntreasure++;
        else{
          temphand[z]=cardDrawn; //storing the non-treasure drawn card in a temporary hand to discard before continuing play
          state->handCount[currentPlayer]--; //removing the non-treasure card from the current hand
        
          z++;
          }
      }
      //discarding the non-treasure cards that were drawn. 
      while(z-1>0){ //BUG
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn 
        z=z-1;
      }

      discardCard(handPos, currentPlayer, state, 0); // discard the adventure card since it has been played

}*/

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
	// ----------- TEST 5: Test handCount of player increased by 1 (+2 treasures - adventurer) -----------
	// ----------- TEST 6: Test that the Adventurer card is in the discard pile -----------
	// ----------- TEST 7: Test that the players total number of cards has not changed -----------
	// ----------- TEST 8: Test that the number of victory (province, estate, duchy) cards has not changed -----------
	// ----------- TEST 9: Test that number of kingdom cards (supply...) has not changed -----------
	return 0;
}