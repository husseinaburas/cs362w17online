/*
 * randomcardtest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: randomcardtest2.c dominion.o rngs.o
 *      gcc -o randomcardtest2 -g  randomcardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"
#define ASSERT_M(exp, MSG) if(!exp) {printf("%s: FAILED!\n", MSG); error = 1;}
#define ASSERT(exp) if(!exp) {printf("Test FAILED!\n"); error = 1;}
int error=0;

//ref dominion files --testdrawcard()
int checkDrawCard(int p, struct gameState *post) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //  printf ("drawCard PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
    
  r = drawCard (p, post);

  //printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

  if (pre.deckCount[p] > 0) {
    pre.handCount[p]++;
    pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
    pre.deckCount[p]--;
  } else if (pre.discardCount[p] > 0) {
    memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
    memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
    pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
    pre.handCount[p]++;
    pre.deckCount[p] = pre.discardCount[p]-1;
    pre.discardCount[p] = 0;
  }

  ASSERT_M((r == 0),"ERROR checkDrawCard: r!=0" );

  ASSERT_M((memcmp(&pre, post, sizeof(struct gameState)) == 0), "DrawCard error!");
}

int checkdiscardCard(int hp, int p, struct gameState *post,  int tf) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //  printf ("drawCard PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
    
  r = discardCard (hp, p, post, tf);

  //printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

  //if card is not trashed, added to Played pile 
  if (tf < 1)
    {
      //add card to played pile
      pre.playedCards[pre.playedCardCount] = pre.hand[p][hp]; 
      pre.playedCardCount++;
    }
	
  //set played card to -1
  pre.hand[p][hp] = -1;
	
  //remove card from player's hand
  if ( hp == (pre.handCount[p] - 1) ) 	//last card in hand array is played
    {
      //reduce number of cards in hand
      pre.handCount[p]--;
    }
  else if ( pre.handCount[p] == 1 ) //only one card in hand
    {
      //reduce number of cards in hand
      pre.handCount[p]--;
    }
  else 	
    {
      //replace discarded card with last card in hand
      pre.hand[p][hp] = pre.hand[p][ (pre.handCount[p] - 1)];
      //set last card to -1
      pre.hand[p][pre.handCount[p] - 1] = -1;
      //reduce number of cards in hand
      pre.handCount[p]--;
    }

  ASSERT_M((r == 0),"ERROR checkdiscardCard: r!=0" );

  ASSERT_M((memcmp(&pre, post, sizeof(struct gameState)) == 0), "discardCard error!");
}

int checkVillage(int p, struct gameState *post, int hp) {
  struct gameState pre;
  int hold_hp;
  int newCards = 1;
  int discarded = 1;
  int Action = 2;
  
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //  printf ("drawCard PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
  hold_hp = hp;  
  playVillage (p, post, hp);

  //printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);
	
	pre.handCount[p] = pre.handCount[p] + newCards - discarded;
	pre.deckCount[p] = pre.deckCount[p] - newCards;
	pre.numActions += 2;

	ASSERT_M((pre.handCount[p] == post->handCount[p]), "checkVillage-handCount");
	ASSERT_M((pre.deckCount[p] == post->deckCount[p]), "checkVillage-deckCount");
	ASSERT_M((pre.numActions == post->numActions), "checkVillage-numActions");
}

int main(int argc, char *argv[]) {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
	int Action = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

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
		thisPlayer = floor(Random() * MAX_PLAYERS);
		G.deckCount[thisPlayer] = floor(Random() * MAX_DECK);
		G.discardCount[thisPlayer] = floor(Random() * MAX_DECK);
		G.handCount[thisPlayer] = floor(Random() * MAX_HAND);
		G.playedCardCount = floor(Random() * (MAX_DECK));

	printf("Random TEST case [%d]\n", m);
	
	checkVillage(thisPlayer, &G, (floor(Random() * MAX_HAND)));
	
   }	
	
  printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}