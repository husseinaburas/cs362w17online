/* -----------------------------------------------------------------------
 * Unit test for Smithy Card
 * Will call callSmithy() function and test it for accuracy
 * based on the actual stats of the card:
 *    cost 4 coins
 *    Draws 3 cards

 Smithy Card Function:

 int smithyCall(int i, int handPos, int currentPlayer, struct gameState *state){
    //+3 Cards
    for (i = 0; i <= 3; i++)
    {
       drawCard(currentPlayer, state);
    }

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
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

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount, tempCount, tempCoins;
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

    printf ("TESTING Smithy Card():\n");
    for (p = 0; p < numPlayer; p++){
        for (handCount = 1; handCount <= maxHandCount; handCount++){
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                tempCount = G.handCount[p];
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                //memcpy(G.hand[0], smithy, sizeof(int) * 1); //set 1st handpos of player to smithy card
                updateCoins(p, &G, 0);                      //update coins in player's hand
                tempCoins = G.coins;                        //use for testing later
                cardEffect(13, 0, 0, 0, &G, 0, 0);           //call card effect with smithy  = 13

                //test hand count + 3
                if(G.handCount[p] == tempCount+2){    //(+2 because we discarded smithy card)
                  printf("smithyCall(): PASS when testing for 3 cards drawn with initial hand count %d, player %d\n", handCount, p);
                }
                else printf("smithyCall(): FAIL when testing for 3 cards drawn, initial cards: %d, final: %d\n", tempCount, handCount);

                //test coins - 4
                if(G.coins == tempCoins-4){
                  printf("smithyCall(): Pass when testing for -4 coins with initial hand count %d, player %d\n", handCount, p);
                }
                else {
                  printf("smithCall(): FAIL when testing for -4 coins, initial coins: %d, final coins: %d\n",tempCoins, G.coins);
                }

                //test if smithy card discarded
                if(G.hand[0] != k[6]){
                  printf("smithyCall(): PASS when testing if discarded smithy card after use for player %d\n", p);
                }
                else printf("smithyCall(): FAIL when testing if discarded smithy card after use for player %d\n", p);
              }
            }


    return 0;
}
