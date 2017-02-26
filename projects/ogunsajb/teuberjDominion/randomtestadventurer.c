/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
#define ASSERT_M(exp, MSG) if(!exp) {printf("%s: FAILED!\n", MSG); error = 1;}
#define ASSERT(exp) if(!exp) {printf("Test FAILED!\n"); error = 1;}
int error=0;

int checkAdventurer(struct gameState *post, int currentPlayer, int drawntreasure) {

int temphand[MAX_HAND];
int z = 0;// this is the counter for the temp hand	
int cardDrawn, saved_dt;   
struct gameState pre;

		 
    memcpy (&pre, post, sizeof(struct gameState));
	saved_dt = drawntreasure;
	
#if 1
	while(drawntreasure<2){
		if (pre.deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, &pre);
		  }
 	  
		drawCard(currentPlayer, &pre);
		cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer] - 1];//?? //top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else{
			temphand[z]=cardDrawn;
			pre.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		 }
     }
	 
       
	while(z-1>=0){
		pre.discard[currentPlayer][pre.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
      }	

#endif

    playAdventurer(currentPlayer, post, saved_dt);

#if  1
    //ASSERT_M(( memcmp(&pre, post, sizeof(struct gameState)) == 0), "adventurer error!"  );
	//check certain aspects of the game state....
	for(z=0; z < MAX_HAND; z++){
		
		ASSERT_M( (pre.hand[currentPlayer][z] == post->hand[currentPlayer][z]), "adventurer hand error!");
		if(error) printf("pre: %d; post: %d\n",pre.hand[currentPlayer][z], post->hand[currentPlayer][z]);
		error=0;
	}
	
	ASSERT_M( (pre.handCount[currentPlayer] == post->handCount[currentPlayer]), "adventurer hand count error!");
	if(error) printf("pre handCount: %d; post handCount: %d\n",pre.handCount[currentPlayer], post->handCount[currentPlayer]);
	error=0;
	
	for(z=0; z < MAX_DECK; z++){
		ASSERT_M( (pre.discard[currentPlayer][z] == post->discard[currentPlayer][z]), "adventurer discard error!");
		if(error) printf("pre discard: %d; post discard: %d\n",pre.discard[currentPlayer][z], post->discard[currentPlayer][z]);
		error=0;
		
		ASSERT_M( (pre.deck[currentPlayer][z] == post->deck[currentPlayer][z]), "adventurer deck error!");
		if(error) printf("pre deck: %d; post deck: %d\n",pre.deck[currentPlayer][z], post->deck[currentPlayer][z]);
		error=0;
	}
	
	ASSERT_M( (pre.deckCount[currentPlayer] == post->deckCount[currentPlayer]), "adventurer deck count error!");	
	if(error) printf("pre deckCount: %d; post deckCount: %d\n",pre.deckCount[currentPlayer], post->deckCount[currentPlayer]);
	error=0;
	
	ASSERT_M( (pre.discardCount[currentPlayer] == post->discardCount[currentPlayer]), "adventurer discardCount count error!");	
	if(error) printf("pre discardCount: %d; post discardCount: %d\n",pre.discardCount[currentPlayer], post->discardCount[currentPlayer]);	
#endif	
}

int main(int argc, char *argv[]) {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int drawntreasure = 2;
	struct gameState G, pre;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	//initializeGame(numPlayers, k, seed, &G);
	SelectStream(2);
	if (argc < 2){
		printf("use case: randomtestcard1 <seed> \n");
		exit(1);
	}
	
	PutSeed(atoi(argv[1]));
    
    printf("-----------------Random Testing Card: %s ----------------\n", TESTCARD);	
	for (m =0; m<2000; m++){
		for(i =0; i < sizeof(struct gameState); i++){
			((char*) &G)[i] = floor(Random() * 256);
		}
		thisPlayer = floor(Random() * (MAX_PLAYERS-1));
		G.deckCount[thisPlayer] = floor(Random() * (MAX_DECK-1));
		G.discardCount[thisPlayer] = floor(Random() * (MAX_DECK-1));
		G.handCount[thisPlayer] = floor(Random() * (MAX_HAND-1));
		G.playedCardCount = floor(Random() * (MAX_DECK-1));
			
		for(j=0; j< MAX_HAND; j++)
			G.hand[thisPlayer][j] = 4 + floor(Random() * 2);


	printf("Random TEST case [%d]\n", m);
	
	// case of drawntreasure ==2
	drawntreasure = 0 + floor(Random() * 2);
	checkAdventurer(&G, thisPlayer, drawntreasure);
	}

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


