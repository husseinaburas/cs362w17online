/* -----------------------------------------------------------------------
* Unit test of function drawCard() from dominion.c
* Will output into unittestresults.out along with other unit tests
* We want to check if draw card function works for:
*   when deck is empty (deck count should go from 0 - 500)
*   how many cards were drawn
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
  int i;
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

    printf ("TESTING drawCard():\n");
    for (p = 1; p <= numPlayer; p++){
      for(i=0; i<=500; i+=500){

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.handCount[p] = handCount;                 // set the number of cards on hand
        memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to gold
        tempCount = G.handCount[p];
        G.deckCount[p] = i;
        tempDeck = G.deckCount[p];
        drawCard(p, &G);

        if(i==0){ // check what happens when deck count is initially 0
          if(G.deckCount[p]==500)  printf("drawCard(): PASS when testing %d deckCount, final deckCount: %d\n", i, G.deckCount[p]);
          else  printf("drawCard(): FAIL when testing %d deckCount, final deckCount: %d\n", i, G.deckCount[p]);
        }
        else if(i==500){  //check what happens when deck count is initially 500
          if(G.deckCount[p]==499)  printf("drawCard(): PASS when testing %d deckCount, final deckCount: %d\n", i, G.deckCount[p]);
          else  printf("drawCard(): FAIL when testing %d deckCount, final deckCount: %d\n", i, G.deckCount[p]);
        }

        if(G.handCount[p] == tempCount+1){
          printf("drawCard(): PASS when testing if 1 card was drawn, initial: %d, final: %d\n", tempCount, G.handCount[p]);
        }
        else{
          printf("drawCard(): FAIL when testing if 1 card was drawn, initial: %d, final: %d\n", tempCount, G.handCount[p]);
        }
      }
    }

    return 0;
  }
