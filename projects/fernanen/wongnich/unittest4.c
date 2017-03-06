/* -----------------------------------------------------------------------
* Unit test of function discardCard() from dominion.c
* Will output into unittestresults.out along with other unit tests
* We want to check if discard card function works for:
*   when player has 1 card in hand vs > 1
*   when trash flag is 2 and when trash flag is 0
*
* to see if the function properly returns the state of the game
* 2/1/17
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
  int i, j;
  int seed = 1000;
  int numPlayer = 2;
  int maxBonus = 10;
  int p, r, handCount=5, tempCount, tempDeck;
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

    printf ("TESTING discardCard():\n");
    for (p = 1; p <= numPlayer; p++){
      //for(i=0; i<2; i++){
        for(j=handCount; j>0; j--){

          memset(&G, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
          G.handCount[p] = j;                 // set the number of cards on hand
          memcpy(G.hand[p], golds, sizeof(int) * j); // set all the cards to gold rich man
          tempCount = G.handCount[p];
          discardCard(0, p, &G, 1);

          if(j==1){ // check what happens when hand is initially 1
            if(G.handCount[p]==0)  printf("discardCard(): PASS when testing %d initial handCount, final handCount: %d\n", j, G.handCount[p]);
            else  printf("discardCard(): FAIL when testing %d initial handCount, final handCount: %d\n", j, G.handCount[p]);
          }
          if(j>0){   //check what happens when hand is initially > 0
            if(tempCount = G.handCount[p]+1)  printf("discardCard(): PASS when testing %d initial handCount, final handCount: %d\n", j, G.handCount[p]);
            else  printf("discardCard(): FAIL when testing %d initial handCount, final handCount: %d\n", j, G.handCount[p]);

          }
          /*if(i==0){  //check what happens when trash flag is 0
            if(G.deckCount[p]==499)  printf("drawCard(): PASS when testing %d deckCount, final deckCount: %d\n", i, G.deckCount[p]);
            else  printf("drawCard(): FAIL when testing %d deckCount, final deckCount: %d\n", i, G.deckCount[p]);
          }

          if(i==1){  //check what happens when trash flag is 1
            printf("drawCard(): PASS when testing if 1 card was drawn, initial: %d, final: %d\n", tempCount, G.handCount[p]);
          }
          else{
            printf("drawCard(): FAIL when testing if 1 card was drawn, initial: %d, final: %d\n", tempCount, G.handCount[p]);
          }*/
        //}
      }
    }

    return 0;
  }
