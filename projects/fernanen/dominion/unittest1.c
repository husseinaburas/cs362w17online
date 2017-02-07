/* -----------------------------------------------------------------------
 *	isGameOver() Tescase
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int provinces,eachCard,supplyCount =0;
    int i;
    int seed = 1000;
    int numPlayer = 2;
    //int maxBonus = 10;
    int p, r, handCount;
    //int bonus;
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

    printf ("TESTING updateCoins():\n");
    for (p = 2; p < 4; p++)
    {
        for (provinces = 1; provinces >=0 ; provinces--)
        {
            for (supplyCount = 0; supplyCount < 25; supplyCount++)
            {
		 memset(&G, 23, sizeof(struct gameState));   // clear the game state
                 r = initializeGame(p, k, seed, &G);
				for (eachCard =0; eachCard < 5; eachCard++)
				{	
					//memset(&G, 23, sizeof(struct gameState));   // clear the game state
					//r = initializeGame(p, k, seed, &G); // initialize a new game
					G.supplyCount[province] = provinces; 
					G.supplyCount[eachCard] = 0;  
					#if (NOISY_TEST == 1)
									printf("numofplayers = %d , G.province = %d , supplycards drained = %d :",p ,G.supplyCount[province],(eachCard+1));
					#endif
					if(G.supplyCount[province] == 0 || eachCard > 1)
					{
						#if (NOISY_TEST == 1)
									printf("should return one\n");
						#endif
						assert(isGameOver(&G) == 1); // checks if the game ends
					}
					else 
					{
						#if (NOISY_TEST == 1)
									printf("should return zero\n");
						#endif
						assert(isGameOver(&G) == 0); // checks if the game ends
					}
				}
            }
        }
    }
    printf("All tests passed!\n");
    return 0;
}
