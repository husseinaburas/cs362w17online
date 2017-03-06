/* -----------------------------------------------------------------------
 *	smithy Tescase
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
	int results =0;
	int player=0;
	int beforeCards,afterCards=0; 
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
	
    printf ("TESTING Smithy():\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G);
	player = whoseTurn(&G);
	printf("player %d",player);
	beforeCards = G.deckCount[player]; 
	results = smithi(0,&G,player,0,temphand,0,0,0,0);
	afterCards = G.deckCount[player];
	printf("beforeCard count: %d, afterCard count: %d", beforeCards, afterCards); 
	if((beforeCards +3) == afterCards)
	{
		printf(" PASSED! \n"); 
	}
	else 
	{
		printf("FAILED \n");
	}
	
	printf("checking return value, should return 0 for passing: "); 
	if(results == 0) 
		printf("PASSED \n");
	else 
		printf("FAILED \n");
	return 0; 
}
