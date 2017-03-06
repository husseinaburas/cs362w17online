#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "village"
#define NOISY_TEST 1				// set to 0 to remove print statements

int checkPlayVillage(struct gameState *post, int hand_pos, int test_num){
	int p, r, all_clear;
	struct gameState pre;
	
	memcpy(&pre, post, sizeof(struct gameState));
	
	p = pre.whoseTurn;

	/* Must update function call due to different implementation
	r = playVillage(post, hand_pos); */
	
	// Updated function call:
	// Choices and bonus variables not used when a Village is played
	r = cardEffect(village, 0, 0, 0, post, hand_pos, 0);
	
	// Manually perform expected playSmithy() actions on pre gameState
	// Testing strategy learned from testDrawCard.c example
	// Increase number of actions by 2
	pre.numActions += 2;
	
	// Current player draws a card from own deck (refill deck if empty from discard)
	if (pre.deckCount[p] > 0){
		pre.handCount[p]++;
		pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
		pre.deckCount[p]--;
	} else if (pre.discardCount[p] > 0){
		memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
		memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
		pre.deckCount[p] = pre.discardCount[p];
		pre.discardCount[p] = 0;
		pre.handCount[p]++;
		pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
		pre.deckCount[p]--;
	}
	// Current player discards the played Village card (discardCard())
	pre.playedCards[pre.playedCardCount] = pre.hand[p][hand_pos];
	pre.playedCardCount++;
	pre.hand[p][hand_pos] = -1;
	if(hand_pos == (pre.handCount[p]-1) || pre.handCount[p] == 1){
		pre.handCount[p]--;
	} else {
		pre.hand[p][hand_pos] = pre.hand[p][pre.handCount[p]-1];
		pre.hand[p][pre.handCount[p]-1] = -1;
		pre.handCount[p]--;
	}
	
	all_clear = 1;

	// Did the function return 0?
	if(r != 0){
#if NOISY_TEST
		printf("Test %d failure: Did not return 0.\n", test_num);
#endif
		all_clear = 0;
	}
	// Compare pre (manually adjusted) and post gameStates (should be identical).
	// This test can catch if any other aspects of gameState change unexpectedly.
	// eg Card values, Victory or Kingdom piles, non-current players, etc.
	if(memcmp(&pre, post, sizeof(struct gameState)) != 0){
#if NOISY_TEST
		printf("Test %d failure: An unspecified state change occurred.\n", test_num);
#endif
		all_clear = 0;
	}
	// Were 2 additional actions gained as expected?
	if(post->numActions != pre.numActions){
#if NOISY_TEST
		printf("Test %d failure: Action count is %d, should be %d.\n", 
				test_num, post->numActions, pre.numActions);
#endif
		all_clear = 0;
	}
	// Did the current player's hand count increase by 1 (2 new cards, 1 card discarded)?
	if(pre.handCount[p] != post->handCount[p]){
#if NOISY_TEST
	printf("Test %d failure: Hand count is %d, should be %d.\n", 
				test_num, post->handCount[p], pre.handCount[p]);
#endif
		all_clear = 0;
	}
	// Was a card added to the played card pile?
	if(pre.playedCardCount != post->playedCardCount){
#if NOISY_TEST
		printf("Test %d failure: Played card count is %d, should be %d.\n",
				test_num, post->playedCardCount, pre.playedCardCount);
#endif
		all_clear = 0;
	}
	// Is the last played card a Village?
	if(post->playedCards[post->playedCardCount-1] != village){
#if NOISY_TEST
		printf("Test %d failure: Last played card is %d, should be village (%d).\n", 
				test_num, post->playedCards[post->playedCardCount-1], village);
#endif
		all_clear = 0;
	}
	// Check current player's deck count.
	if(pre.deckCount[p] != post->deckCount[p]){
#if NOISY_TEST
		printf("Test %d failure: Deck count is %d, should be %d.\n",
				test_num, post->deckCount[p], pre.deckCount[p]);
#endif
		all_clear = 0;
	}
	// Check current player's discard pile count.
	if(pre.discardCount[p] != post->discardCount[p]){
#if NOISY_TEST
		printf("Test %d failure: Discard count is %d, should be %d.\n",
				test_num, post->discardCount[p], pre.discardCount[p]);
#endif
		all_clear = 0;
	}
	
	return all_clear;
}

int main(int argc, char** argv){
	int i, n, cur_player, hand_pos, seed, all_clear, all_tests_passed;
	struct gameState G;

	if(argc > 1){
		seed = atoi(argv[1]);
	} else { 
		printf("Please provide a seed value.\n");
		exit(1);
	}	
	
	printf("Testing %s.\n", TESTCARD);
	printf("RANDOM TESTS.\n");
	
	SelectStream(2);
	PutSeed(seed);
	
	all_tests_passed = 1;
	
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++){
			((char*)&G)[i] = floor(Random() * 256);
		}
		cur_player = floor(Random() * MAX_PLAYERS);
		G.whoseTurn = cur_player;
		// Test entire possible ranges of card pile sizes.
		G.handCount[cur_player] = floor(Random() * MAX_HAND);
		G.deckCount[cur_player] = floor(Random() * MAX_DECK);
		G.discardCount[cur_player] = floor(Random() * MAX_DECK);
		G.playedCardCount = floor(Random() * MAX_DECK);
		// Set played card to Village -- other card values do not matter as long no unexpected change.
		hand_pos = floor(Random() * G.handCount[cur_player]);
		G.hand[cur_player][hand_pos] = village;
		// Test wide range of possible action values.
		G.numActions = (floor(Random() * 20));
		
		all_clear = checkPlayVillage(&G, hand_pos, n+1);
		
		if(all_clear == 0){
			all_tests_passed = 0;
		}
	}
	// ALL TESTS OK only printed if all tests pass
	if(all_tests_passed){
		printf("ALL TESTS OK\n");
	} else {
		printf("SOME TESTS FAILED\n\n");
	}
	
	exit(0);
}