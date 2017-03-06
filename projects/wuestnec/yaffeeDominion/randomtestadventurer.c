#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "adventurer"
#define NOISY_TEST 1				// set to 0 to remove print statements

int checkPlayAdventurer(struct gameState *post, int cur_player, int hand_pos, int num_treasures, int test_num){
	int i, j, p, r;
	int card, pre_treasures, post_treasures, all_clear, pre_dd, post_dd;
	int cards_discarded = 1;
	int drawn_treasure = 0;
	int card_drawn = -1;
	int z = 0;
	int temp_hand[MAX_HAND] = {0};
	struct gameState pre;
	
	memcpy(&pre, post, sizeof(struct gameState));
	
	p = pre.whoseTurn;
	/* Must update function call due to different implementation
	r = playAdventurer(post, hand_pos); */
	
	// Updated function call to match implementation by group member:
	r = adventurerCard(post, drawn_treasure, cur_player, temp_hand, card_drawn, z);
	
	all_clear = 1;
	// Find number of treasures in current player's hand in pre and post game states.
	pre_treasures = 0;
	for(i = 0; i < pre.handCount[p]; i++){
		card = pre.hand[p][i];
		if(card == copper || card == silver || card == gold){
			pre_treasures++;
		}
	}
	post_treasures = 0;
	for(j = 0; j < post->handCount[p]; j++){
		card = post->hand[p][j];
		if(card == copper || card == silver || card == gold){
			post_treasures++;
		}
	}

	pre_dd = pre.deckCount[p] + pre.discardCount[p];
	post_dd = post->deckCount[p] + post->discardCount[p];
	
	// Begin tests:
	// Check that function returned 0 as expected.
	if(r != 0){
#if NOISY_TEST
		printf("Test %d failure: Did not return 0.\n", test_num);
#endif
		all_clear = 0;
	}
	// Check that current player gains 2 treasures (Case: num_treasures > 1).
	if(num_treasures > 1){
		if(pre_treasures + 2 != post_treasures){
#if NOISY_TEST
			printf("Test %d failure: treasure count is %d, should be %d.\n", 
					test_num, post_treasures, (pre_treasures + 2));
#endif
			all_clear = 0;
		}
		// Check that current player's hand is correct (Case: num_treasures > 1)
		if(pre.handCount[p] + 2 - cards_discarded != post->handCount[p]){
#if NOISY_TEST
			printf("Test %d failure: hand count is %d, should be %d.\n",
					test_num, post->handCount[p], (pre.handCount[p] + 2 - cards_discarded));
#endif
			all_clear = 0;
		}
		// Check that current player's deck + discard count is correct.
		if(pre_dd - 2 != post_dd){
#if NOISY_TEST
			printf("Test %d failure: deck + discard count is %d, should be %d.\n",
					test_num, post_dd, (pre_dd - 2));
#endif
			all_clear = 0;
		}
	// Beginning of other Case tests (num_treasures == 1 or num_treasures == 0).
	} else {
		if(pre_treasures + num_treasures != post_treasures){
#if NOISY_TEST
			printf("Test %d failure: treasure count is %d, should be %d.\n", 
					test_num, post_treasures, (pre_treasures + num_treasures));
#endif
			all_clear = 0;
		}
		if(pre.handCount[p] + num_treasures - cards_discarded != post->handCount[p]){
#if NOISY_TEST
			printf("Test %d failure: hand count is %d, should be %d.\n",
					test_num, post->handCount[p], (pre.handCount[p] + num_treasures - cards_discarded));
#endif
			all_clear = 0;
		}
		if(pre_dd - num_treasures != post_dd){
#if NOISY_TEST
			printf("Test %d failure: deck + discard count is %d, should be %d.\n",
					test_num, post_dd, (pre_dd - num_treasures));
#endif
			all_clear = 0;
		}
	}
	// Check if played card count was correctly updated.
	if(pre.playedCardCount + cards_discarded != post->playedCardCount){
#if NOISY_TEST
		printf("Test %d failure: played cards count is %d, should be %d.\n", 
				test_num, post->playedCardCount, pre.playedCardCount + cards_discarded);
#endif
		all_clear = 0;
	}
	// Check if last played card is an Adventurer card.
	if(adventurer != post->playedCards[post->playedCardCount-1]){
#if NOISY_TEST
		printf("Test %d failure: Discard count is %d, should be %d.\n", 
				test_num, post->playedCards[post->playedCardCount-1], adventurer);
#endif
		all_clear = 0;
	}
	// Check hand, deck, and discard counts for non-current players.
	for(i = 0; i < pre.numPlayers; i++){
		if(i != pre.whoseTurn){
			if(post->handCount[i] != pre.handCount[i]){
#if NOISY_TEST
				printf("Test %d failure: Player %d hand count is %d, should be %d.\n", 
						test_num, i, post->handCount[i], pre.handCount[i]);
#endif
				all_clear = 0;
			}
			if(post->deckCount[i] != pre.deckCount[i]){
#if NOISY_TEST		
				printf("Test %d failure: Player %d deck count is %d, should be %d.\n", 
						test_num, i, post->deckCount[i], pre.deckCount[i]);
#endif
				all_clear = 0;
			}
			if(post->discardCount[i] != pre.discardCount[i]){
#if NOISY_TEST
				printf("Test %d failure: Player %d discard count is %d, should be %d.\n", 
						test_num, i, post->discardCount[i], pre.discardCount[i]);
#endif
				all_clear = 0;
			}
		}
	}
	// Check state of card piles (including Victory and Kingdom piles).
	for(i = 0; i < treasure_map; i++){
		if(pre.supplyCount[i] != post->supplyCount[i]){
#if NOISY_TEST
			printf("Test %d failure: Supply Count for card %d changed.\n", test_num, i);
#endif
			all_clear = 0;
		}
	}
	return all_clear;
}

int main(int argc, char** argv){
	int i, j, n;
	int cur_player, hand_pos, seed, card, treasures, 
			all_clear, all_tests_passed;
	int placeholder_num_players = 2;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
			smithy, village, baron, great_hall};
	
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
		
		/* Creating gameState like this was causing segmentation fault
		for (i = 0; i < sizeof(struct gameState); i++){
			((char*)&G)[i] = floor(Random() * 256);
		}*/
		
		// Used initializeGame(), like I did for cardtest2, to fix segmentation fault
		initializeGame(placeholder_num_players, k, floor(Random() *2000)+1, &G);
		
		G.numPlayers = floor(Random() * (MAX_PLAYERS+1));
		cur_player = floor(Random() * G.numPlayers);
		G.whoseTurn = cur_player;
		
		G.handCount[cur_player] = floor(Random() * MAX_HAND);
		// Set card to be played as an Adventurer card
		hand_pos = floor(Random() * G.handCount[cur_player]);
		G.hand[cur_player][hand_pos] = adventurer;
		
		G.playedCardCount = floor(Random() * MAX_DECK);
		G.deckCount[cur_player] = floor(Random() * 20);
		G.discardCount[cur_player] = floor(Random() * 20);
		// Initialize cards in deck and dicard pile so that treasures can be drawn.
		// Count treasure cards to make later testing easier.
		treasures = 0;
		for(i = 0; i < G.deckCount[cur_player]; i++){
			card = floor(Random() * (treasure_map+1));
			if(card == copper || card == silver || card == gold){
				treasures++;
			}
			G.deck[cur_player][i] = card;
		}
		for(j = 0; j < G.discardCount[cur_player]; j++){
			card = floor(Random() * (treasure_map+1));
			if(card == copper || card == silver || card == gold){
				treasures++;
			}
			G.discard[cur_player][j] = card;
		}
		
		all_clear = checkPlayAdventurer(&G, cur_player, hand_pos, treasures, n+1);
		
		if(all_clear == 0){
			all_tests_passed = 0;
		}
	}
	
	if(all_tests_passed){
		printf("ALL TESTS OK\n");
	} else {
		printf("SOME TESTS FAILED\n\n");
	}
	
	exit(0);
}
