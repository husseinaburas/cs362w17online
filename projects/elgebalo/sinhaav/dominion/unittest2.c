

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"


#define TEST_FUNCTION 1

int main() {
	printf("\n--- TESTING isGameOver() ---\n");
    int p, isOver;
	int new_game = 0;
    int seed = 1000;
    int numPlayers = 1;
    int copperCoins, silverCoins, goldCoins;
    int provinceCount;
    int k[10] = {adventurer, smithy, council_room, feast, mine, gardens, remodel, village, great_hall, baron};
    struct gameState G;

    for(p = 0; p < numPlayers; ++p) {
        //tests if three treasure cards are empty
        for(copperCoins = 0; copperCoins < 5; ++copperCoins) {
            for(silverCoins = 0; silverCoins < 5; ++silverCoins) {
                for(goldCoins = 0; goldCoins < 5; ++goldCoins) {
                    for(provinceCount = 0; provinceCount < 5; ++provinceCount) {
                        //clear the game state
                        memset(&G, 23, sizeof(struct gameState));
                        //initialize a new game
                        new_game = initializeGame(numPlayers, k, seed, &G);
                        //set game state
                        G.supplyCount[province] = provinceCount;
                        G.supplyCount[copper] = copperCoins;
                        G.supplyCount[silver] = silverCoins;
                        G.supplyCount[gold] = goldCoins;

                        //test if game is over
                        isOver = isGameOver(&G);
#if (TEST_FUNCTION == 1)
                        printf("----------------------\nProvince = %d, Copper coins = %d, Silver coins = %d, Gold coins = %d\n",
                               provinceCount, copperCoins, silverCoins, goldCoins);
                        if(isOver)
                            printf("Game over = YES\n");
                        else
                            printf("Game over = NO\n");
#endif
                    }
                }
            }
        }
    }

    printf("\nAll tests passed: isGameOver()\n");
	printf("\n--- END TESTING ---\n");

    return 0;
}