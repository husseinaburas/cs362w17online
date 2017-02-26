/*
 * cardtest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Great_hall"
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

int main() {
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

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Great_hall = +1 action --------------
	printf("TEST 1: play  Great_hall = +1 action\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;
	xtraCoins = 0;
	Action =1;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	ASSERT_M((testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded), "TEST1-handCount");
	ASSERT_M((testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards), "TEST1-deckCount");
	ASSERT_M((testG.coins == G.coins + xtraCoins), "TEST1-coins");
	ASSERT_M((testG.numActions == G.numActions + Action), "TEST1-actions");
	
	// ----------- TEST 2: check that draw card is working --------------
	printf("TEST 2: check that draw card is working\n");
	//error = 0;

	//verify that no other changes occurred...
	G.handCount[thisPlayer] = G.handCount[thisPlayer] + newCards - discarded;
	G.deckCount[thisPlayer] = G.deckCount[thisPlayer] - newCards + shuffledCards;
	G.coins = G.coins + xtraCoins;
	
	
	checkDrawCard(thisPlayer, &testG);

	// ----------- TEST 3: check that discard card is working --------------
	printf("TEST 3: check that discardcard is working\n");
	//error = 0;
	
	checkdiscardCard(handpos, thisPlayer, &testG, 0);
	checkdiscardCard(handpos, thisPlayer, &testG, 1);
	
	if (error)
		printf("TEST Failed!\n");
	else
		printf("TEST PASSED!\n");	

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}