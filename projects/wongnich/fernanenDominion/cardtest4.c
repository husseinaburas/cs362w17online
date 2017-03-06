/* -----------------------------------------------------------------------
Will test Great Hall card functionality

Great_Hall call:

int greatHall(int currentPlayer, struct gameState *state, int handPos){
   //+1 Card
   drawCard(currentPlayer, state);

   //+1 Actions
   state->numActions++;

   //discard card from hand
   discardCard(handPos, currentPlayer, state, 0);
   return -1;
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
    int p, r, handCount=5, tempCount, tempActions;
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

    printf ("TESTING greatHall():\n");
    for (p = 0; p < numPlayer; p++)
    {
      memset(&G, 23, sizeof(struct gameState));   // clear the game state
      r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
      G.handCount[p] = handCount;                 // set the number of cards on hand
      memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to gold
      //updateCoins(p, &G, bonus);
      //tempCoins = G.coins;
      tempActions = G.numActions;
      tempCount = G.handCount[p];
      cardEffect(16, 0, 0, 0, &G, 0, 0);           //call card effect with greatHall  = 16
      //updateCoins(p, &G, bonus);


      if(tempActions == G.numActions-1){
        printf("villageCall(): PASS when testing for +2 actions, initial: %d, final: %d\n", tempActions, G.numActions);
      }
      else{
        printf("villageCall(): FAIL when testing for +2 actions, initial: %d, final: %d\n", tempActions, G.numActions);
      }

      if(tempCount-1 == G.handCount[p]){
        printf("villageCall(): PASS when testing for card discarded, cards discarded: %d\n", (tempCount - G.handCount[p]));
      }
      else{
        printf("villageCall(): FAIL when testing for card discarded, cards discarded: %d\n", (tempCount - G.handCount[p]));
      }
    }

    return 0;
}
