#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int results = 0; 
	int player = 0;
	int beforeCoins,afterCoins=0; 
	int temphand[MAX_HAND];
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
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    	printf ("TESTING Adventure():\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G);
 	player = G.whoseTurn;	
	beforeCoins = G.coins;
	results = adventure(0,&G,player,0,temphand,0);
	updateCoins(player,&G,0);
	afterCoins = G.coins;
	printf("beforeCoins: %d, after adventure coins: %d ", beforeCoins, afterCoins); 
	if( (beforeCoins+2) == afterCoins)
	{
		printf("PASSED! \n"); 
	}
	else 
	{
		printf("FAILED! \n");
	}
	printf("cheking results of function:");
        if( results == 0)
        {
                printf("PASSED! \n");
        }
        else
        {
                printf("FAILED! \n");
        }
	printf("Tests Complete!"); 
}
