/* -----------------------------------------------------------------------
Will test Adventurer card functionality

Adventurer call:

int adventurerCall(int drawntreasure, struct gameState *state, int currentPlayer, int cardDrawn, int z, int temphand[MAX_HAND]){
   while(drawntreasure<6){
      if(state->deckCount[currentPlayer]<1){	//if the deck is empty we need to shuffle discard and add to deck
	 shuffle(currentPlayer, state);
      }
      drawCard(currentPlayer, state);
      cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
      if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	 drawntreasure++;
      else{
	 temphand[z]=cardDrawn;
	 state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	 z++;
      }
   }
   while(z-1>=0){
      state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
      z=z-1;
   }


   return 0;
}
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount=5, tempCount, tempCoins;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING adventurerCall():\n");
    for (p = 0; p < numPlayer; p++)
    {
      memset(&G, 23, sizeof(struct gameState));   // clear the game state
      r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
      G.handCount[p] = handCount;                 // set the number of cards on hand
      memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to gold
      updateCoins(p, &G, bonus);
      tempCoins = G.coins;
      tempCount = G.handCount[p];
      cardEffect(7, 0, 0, 0, &G, 0, 0);           //call card effect with adventurer  = 7
      updateCoins(p, &G, bonus);


      if(tempCoins == G.coins+6){
        printf("adventurerCall(): PASS when testing for coins spent, initial: %d, final: %d\n", tempCoins, G.coins);
      }
      else{
        printf("adventurerCall(): FAIL when testing for coins spent, initial: %d, final: %d\n", tempCoins, G.coins);
      }

      if(((G.handCount[p] - tempCount)-1)==2){
        printf("adventurerCall(): PASS when testing for cards drawn: %d cards drawn:\n", (G.handCount[p] - tempCount)-1);
      }
      else{
        printf("adventurerCall(): FAIL when testing for cards drawn: %d cards drawn:\n", (G.handCount[p] - tempCount)-1);
      }
    }

    return 0;
}
