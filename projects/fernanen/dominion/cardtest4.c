/* -----------------------------------------------------------------------
 *	counsilRoom Tescase
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
	int beforeActions,afterActions=0;
	int temphand[MAX_HAND];
    int provinces,eachCard,supplyCount =0;
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int maxHandCount = 5;
	
    printf ("TESTING Council_Room:\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G);
	player = whoseTurn(&G);
		
	beforeCards = G.deckCount[player];
	beforeActions = G.numBuys; 
	results = cardEffect(council_room,0,0,0,&G,0,&provinces);
	afterCards = G.deckCount[player];
	afterActions = G.numBuys;
	printf("beforecard count: %d, afterCard count: %d", beforeCards, afterCards); 

	if((beforeCards + 3) == afterCards)
	{
		printf(" PASSED! \n"); 
	}
	else 
	{
		printf("FAILED \n");
	}
	
	printf("checking buys, should be up by 1 for passing: %d,%d ",beforeActions,afterActions); 
	if((beforeActions+1) == afterActions) 
		printf("PASSED \n");
	else 
		printf("FAILED \n");
	
	printf("checking return value, should return 0 for passing: "); 	
	if(results == 0) 
		printf("PASSED \n");
	else 
		printf("FAILED \n");
	return 0;	
}
