/* -----------------------------------------------------------------------
 *	Great_HALL Tescase
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
	/****************************variables*****************/
	srand(time(NULL));
	int cardsum;
	int adventureCardpos;
	int randHandcount; 
	int randDeckCount;
	int randDiscardCount;
	int randPlayedCount;
	int results =0;
	int player=0;
	int beforeCards,afterCards=0;
	int beforeActions,afterActions=0;
	int temphand[MAX_HAND];
    int provinces,eachCard,supplyCount =0;
    int i,j,x;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int maxHandCount = 5;
	/****************************variables*****************/
    printf ("TESTING GREAT_HALL:\n");
	x=0;
	while(x<10000)
	{
		/****************************setting random gamestate*****************/
		randHandcount =rand() % MAX_HAND +1;
		randDeckCount =rand() % MAX_DECK +1;
		randDiscardCount = rand() % MAX_HAND;
		randPlayedCount = rand() % MAX_HAND;
		/****************************setting random gamestate*****************/
		numPlayer = rand() %2+2;
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G);
		/****************************setup randon gamestate*****************/
		G.handCount[player] = randHandcount;
		G.deckCount[player] = randDeckCount;
		G.discardCount[player] = randDiscardCount;
		G.playedCardCount = randPlayedCount;
		//random Handcards 
		for(j = 0; j < randHandcount; j++)
		{
			G.hand[player][j] = rand() % 26;
		}
		//random Handcards
		
		// random deckCards 
		for(j = 0; j < randDeckCount; j++)
		{
			G.deck[player][j] = rand() % 26;
		}
		//random deckCards
		
		//random DIscardcards
		for(j = 0; j < randDiscardCount; j++)
		{
			G.discard[player][j] = rand() % 26;
		}
		//random Discardcards
		
		// random playedCards
		for(j = 0; j < randPlayedCount; j++){
			G.playedCards[j] = rand() % 26;
			//printf("    		discard is %i\n", game->discard[currentPlayer][j]);
		}
		// random playedCards
		
		//getadventureCard
		/****************************setup random gamestate*****************/
		player = whoseTurn(&G);	
		beforeCards = G.deckCount[player];
		beforeActions = G.numActions; 
		results = cardEffect(great_hall,0,0,0,&G,0,&provinces);
		afterCards = G.deckCount[player];
		afterActions = G.numActions;
		printf("beforeCard count: %d, afterCard count: %d", beforeCards, afterCards); 

		if((beforeCards-1) == afterCards)
		{
			printf(" PASSED! \n"); 
		}
		else 
		{
			printf("FAILED \n");
		}
		printf("checking actions, should be up by 1 for passing: %d,%d ",beforeActions,afterActions); 
		if((beforeActions+1) == afterActions) 
			printf("PASSED \n");
		else 
			printf("FAILED \n");
		
		printf("checking return value, should return 0 for passing: "); 	
		if(results == 0) 
			printf("PASSED \n");
		else 
			printf("FAILED \n");
		x=x+1; 
	}
	return 0;	
}
