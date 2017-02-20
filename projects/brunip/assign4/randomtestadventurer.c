/* Name: Parker Bruni
* CS362 Assignment 4
* Card Test: Adventurer
*/

#include "dominion.h"
#include <string.h>
#include "rngs.h"
#include "dominion_helpers.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int i, j, h, seed;
	int check = 0, c1 =0, c2 = 0, c3 = 0, numPlayers = 0, curPlayer = 0, handPos = 0, handCount = 0, deckCount = 0, treasure = 0, z = 0;	
	struct gameState G;
	
	printf("___________Random Test for Adventurer___________\n");
	
	
	for(i = 0; i < 2000; i++){ 
		srand(time(NULL)); //for new seeds
		numPlayers = rand()%5; //up to 4 players
		
		//sets valid number of players
		if(numPlayers <= 1){ 
			numPlayers == numPlayers + 2; 
		}
		//generate random seed
		seed = rand();
		c1 = rand() % 2;
		c2 = rand() % 2;
		c3 = rand() % 2;
		handPos = rand() % 4 ;
		
		initializeGame(numPlayers, k, seed, &G);
		
		// Randomize deck count, discard count, handcount
		G.deckCount[curPlayer] = rand() % MAX_DECK;
		G.discardCount[curPlayer] = rand() % MAX_DECK;
		G.handCount[curPlayer] = rand() % MAX_HAND;
		deckCount = G.deckCount[curPlayer];
		
		
		//adding 2 treasure cards to deck
		for(j = 0; j < G.handCount[curPlayer]; j++){
			gainCard(copper,&G,2,curPlayer);
		}
		//1/4 chance of empty deckCount
		if(seed % 4 == 0){ 
			G.deckCount[curPlayer] = 0;
		}
		check = cardEffect(adventurer, c1,c2,c3, &G, handPos, 0);
		
		for(h = 0; h < G.handCount[curPlayer]; h++){
			//seeks out treasure cards and increments accordingly
			if(G.hand[curPlayer][h] == copper || G.hand[curPlayer][h] == silver || G.hand[curPlayer][h] == gold){
				treasure++; 
			}
			else if(G.hand[curPlayer][h] == 0){
				z++;
			}
		}
		
		//checking if cardEffect ran correctly
		assert(check == 0); 
		
		if(treasure < 2 && z != G.handCount[curPlayer] && G.handCount[curPlayer] != 0){
			printf("FAILURE: Treasure Count: %d EXPECTED: 2 or greater\n", i);
			for(h = 0; h < G.handCount[curPlayer]; h++){
				printf("G.hand[curPlayer][h] = %d\n", G.hand[curPlayer][h]);
			}
		}
		
		if(G.handCount[curPlayer] < 0) {
			printf("FAILED: hand count: %d Expected: > 0\n", i);
        }
		if(deckCount < G.deckCount[curPlayer]+2 && deckCount != G.deckCount[curPlayer] && G.deckCount[curPlayer] != 0){
			printf("FAILED: Error with deck count\n");
        }
		
	}
	
	
  return 0;

}