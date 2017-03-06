/* Name: Nipun Bathini
   Assignment: 4
   
   randomtestadventurer
   */

#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int main(int argc, char *argv[]){
	
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
			   
	int seed;
	if(argc == 2){
		seed = atoi(argv[1]); //seet from command line
	}else{
		printf("\n Random seed is being generated: ");
		srand(time(NULL));
		seed = rand();
		printf("%d\n",seed);
	}
	
	srand(seed);
		
		
	int i, j,h;
	int run = 0, c1 =0, c2 = 0, c3 = 0, numPlayers = 0, curPlayer = 0, handPos = 0, handCount = 0, deckCount = 0, discardCount = 0, treasure = 0, z = 0;
	
	struct gameState G;
	//srand(time(NULL));
	
	printf(" -----Random Test for Adventurer -----\n");
	
	printf("PRINTING ALL ERRORS, if none all tests PASSED\n");
	
	for(i = 0; i < 1000; i++){ //loop up to a mah number of tests
		numPlayers = rand()%5; //up to 4 players
		
		if(numPlayers <=1){ //make sure thers more than 1 players
			numPlayers += 2; //adds 2 players
		}
		seed = rand();
		c1 =rand()%2;
		c2 = rand()%2;
		c3 = rand()%2;
		
		handPos = rand()%4;
		
		initializeGame(numPlayers, k, seed, &G);
		
		// Randomize for random test
		G.deckCount[curPlayer] = rand()%MAX_DECK;
		G.discardCount[curPlayer] = rand()%MAX_DECK;
		G.handCount[curPlayer] = rand()%MAX_HAND;
		deckCount = G.deckCount[curPlayer];
		
		if(seed%3 == 0){ //making 1/3 chance of empty deckCount
			G.deckCount[curPlayer] = 0;
		}
		
		for(j = 0; j < G.handCount[curPlayer]; j++){ //add 2 treasure cards to deck
			gainCard(copper,&G,2,curPlayer);
		}
		run = cardEffect(adventurer, c1,c2,c3, &G, handPos, 0);
		
		for(h = 0; h< G.handCount[curPlayer]; h++){
			if(G.hand[curPlayer][h] == copper || G.hand[curPlayer][h] == silver || G.hand[curPlayer][h] == gold){
				treasure++; //if theres a treasure found add to the counter
			}
			else if(G.hand[curPlayer][h] == 0){
				z++;
			}
		}
		assert(run==0); //CardEffect 
		
		
		if(treasure < 2 && z != G.handCount[curPlayer] && G.handCount[curPlayer] != 0){
			printf("\nTest FAIL: the  treasure count is %d must be atelast 2\n", i);

			for(h = 0; h < G.handCount[curPlayer]; h++){
				printf("\n current player hand count is %d\n", G.hand[curPlayer][h]);
				}
		}
		
		if(G.handCount[curPlayer] < 0) {
          printf("\tTest FAIL: hand count should be greater than 0\n", i);
        }
		if(deckCount < G.deckCount[curPlayer]+2 && deckCount != G.deckCount[curPlayer] && G.deckCount[curPlayer] != 0){
          printf("\tTest FAIL: Error in the deck count\n");
        }
		
	}
	
  return 0;

}