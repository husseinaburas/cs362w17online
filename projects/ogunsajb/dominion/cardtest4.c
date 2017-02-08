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
int cardDrawn;   
struct gameState pre;


    memcpy (&pre, post, sizeof(struct gameState));
  
	while(drawntreasure<2){
		if (pre.deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, &pre);
		  }
		  
		drawCard(currentPlayer, &pre);
		cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer]];//?? //top card of hand is most recently drawn card.
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

    playAdventurer(post, currentPlayer,drawntreasure);

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
	
}

int main() {
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
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: test adventurer card drawntreasure == 2 --------------
	printf("TEST 1: test adventurer card drawntreasure ==2\n");

	// case of drawntreasure ==2
	//G.deckCount[thisPlayer] = 3;
	checkAdventurer(&G, thisPlayer, drawntreasure);

	// ----------- TEST 2: test adventurer card drawntreasure ==1 --------------
	printf("TEST 2: test adventurer card drawntreasure == 1\n");

	drawntreasure = 1;
	// case of drawntreasure ==1
	checkAdventurer(&G, thisPlayer, drawntreasure);


	// ----------- TEST 3: test adventurer card drawntreasure == 0 --------------
	printf("TEST 3: test adventurer card drawntreasure == 0\n");

	drawntreasure = 0;
	// case of drawntreasure == 0
	checkAdventurer(&G, thisPlayer, drawntreasure);

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


