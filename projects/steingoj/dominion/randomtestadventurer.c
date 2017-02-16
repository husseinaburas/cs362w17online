#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> //for rand
#include <time.h> //for time
#include <assert.h>
#include "rngs.h"
#include "asserttrue.h" //Custom assert macro
#include "math.h" //For floor

#define DEBUG 0
#define NOISY_TEST 1


int checkAdventurer(int p, struct gameState *post){
	int r, cardCount;
	int numTreasures = 0;
	int handCount = post->handCount[p];
	int discardCount = post->discardCount[p];
	int deckCount = post->deckCount[p];	
	int a, b;

	post->whoseTurn = p;
	
	int i = 0;
	//Get the number of cards before two treasures
	while(numTreasures < 2 && i < post->deckCount[p]){
		int num = post->deck[p][i];
		switch(num){
			case copper:
			case silver:
			case gold:
				numTreasures++;
				break;
			default:
				cardCount++; 
		}
		i++;
	}

	r = playAdventurer(post);

	a = handCount;
	b = post->handCount[p];

	//printf("HandCount before: %d\n", handCount); 
	//printf("HandCount after: %d\n", post->handCount[p]);

	
	//handCount should be increased by the number of treasures found
	assertTrue(a + numTreasures==post->handCount[p], "Hand Count did not increment by number of treasures found\n");

	
	//Check the right number of cards was discarded 
	assertTrue(discardCount + cardCount == post->discardCount[p], "Wrong number of cards discarded\n");


	//Check that the deckCount is the same before and after
	assertTrue(deckCount  == post->deckCount[p] - (cardCount + numTreasures), "Right number of cards not taken from deck");



	//Check the handCount increases appropriately 
	if(numTreasures == 0){
		//No treasures, shuffled through the whole deck
		assertTrue(handCount == post->handCount[p], "0 treasures and handCount changed\n");
	}else if(numTreasures == 1){
		assertTrue(handCount+1 == post->handCount[p], "1 treasure found and handCount not increased appropriately\n");
	}else if(numTreasures == 2){
		assertTrue(handCount+2== post->handCount[p], "2 treasures found and handCount not increased appropriately\n"); 
	}else{
		printf("%d treasures found but not all counted\n", numTreasures); 
	}  
 
	return 0;	
}


int main(int argc, char* argv[]) {

	int i, n, r, p, deckCount, discardCount, handCount, rando;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing adventurer.\n");

	printf ("RANDOM TESTS.\n");

	if(argc != 2){
		printf("You only need one argument to run this program\n\n");
	}

	//SelectStream(2);
	//PutSeed(3);
	srand(time(argv[1]));

	//Generate random number of treasure
	//Generate number of other cards
	//Place treasure and cards in deck
	
	
	//TO DO: Increase n for more random testing
	for (n = 0; n < 10; n++) {
		//COULD CREATE LOOP FOR MANY PLAYERS HERE		
		
		//Clear the deck between tests
		for(i = 0; i < MAX_DECK; i++){
			G.deck[0][i] = NULL;
		}   


		//Generate random number of cards
		G.deckCount[0] = rand() % MAX_DECK;  

		//Fill the deck with cards 		
		for(i = 0; i < G.deckCount[0]; i++){
		
		 
			rando = rand() % 100;
			if(rando > 70){
				if(rando > 90){
					G.deck[0][i] = gold;
					 
				}else if(rando > 80){
					G.deck[0][i] = silver;
				}					
				else{
					G.deck[0][i] = copper;
				}
			}else{
				G.deck[0][i] = smithy; //Doesn't matter which card I use
			}
		
		}
    		//p = floor(Random() * 2);
    		G.discardCount[0] = floor(Random() * (MAX_DECK - G.deckCount[0]));
    		G.handCount[0] = floor(Random() * MAX_HAND);
		//random number of treasure and place
		
		p = 0; //Player number
	
		checkAdventurer(p, &G);

  	}
	return 0;
}

