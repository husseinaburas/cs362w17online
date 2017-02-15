#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "smithy"
#define DEBUG 0
#define NOISY_TEST 1

int checkPlaySmithy(struct gameState *post, int hand_pos){
	int p, r;
	struct gameState pre;
	
	memcpy(&pre, post, sizeof(struct gameState));
	
	p = pre.whoseTurn;
	
	r = playSmithy(post, hand_pos);
	
	if(pre.deckCount[p] > 2){
		pre.handCount[p] += 3;
		pre.hand[p][pre.handCount[p]-3] = pre.deck[p][pre.deckCount[p]-1];
		pre.hand[p][pre.handCount[p]-2] = pre.deck[p][pre.deckCount[p]-2];
		pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-3];
		pre.deckCount[p] -= 3;
	} else if(pre.deckCount[p] == 2 && pre.discardCount[p] > 0){
		pre.handCount[p] += 2;
		pre.hand[p][pre.handCount[p]-2] = pre.deck[p][pre.deckCount[p]-1];
		pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-2];
		pre.deckCount[p] -= 2;
		memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
		memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
		pre.deckCount[p] = pre.discardCount[p];
		pre.discardCount[p] = 0;
		pre.handCount[p]++;
		pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
		pre.deckCount[p]--;
	} else if(pre.deckCount[p] == 1 && pre.discardCount[p] > 1){
		pre.handCount[p] += 1;
		pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
		pre.deckCount[p]--;
		memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
		memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
		pre.deckCount[p] = pre.discardCount[p];
		pre.discardCount[p] = 0;
		pre.handCount[p] += 2;
		pre.hand[p][pre.handCount[p]-2] = pre.deck[p][pre.deckCount[p]-1];
		pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-2];
		pre.deckCount[p] -= 2;
	} else if(pre.deckCount[p] == 0 && pre.discardCount[p] > 2){
		memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
		memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
		pre.deckCount[p] = pre.discardCount[p];
		pre.discardCount[p] = 0;
		pre.handCount[p] += 3;
		pre.hand[p][pre.handCount[p]-3] = pre.deck[p][pre.deckCount[p]-1];
		pre.hand[p][pre.handCount[p]-2] = pre.hand[p][pre.handCount[p]-2];
		pre.hand[p][pre.handCount[p]-1] = pre.hand[p][pre.handCount[p]-3];
		pre.deckCount[p] -= 3;
	}

	assert(r == 0);
	
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main(){
	int i, n, cur_player, hand_pos;
	struct gameState G;
	
	printf("Testing %s.\n", TESTCARD);
	printf("RANDOM TESTS.\n");
	
	SelectStream(2);
	PutSeed(3);
	
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++){
			((char*)&G)[i] = floor(Random() * 256);
		}
		cur_player = floor(Random() * 2);
		G.whoseTurn = cur_player;
		
		G.handCount[cur_player] = floor(Random() * MAX_HAND);
		G.deckCount[cur_player] = floor(Random() * MAX_DECK)+1;
		G.discardCount[cur_player] = MAX_DECK - G.deckCount[cur_player];
		
		hand_pos = floor(Random() * G.handCount[cur_player]);
		
		checkPlaySmithy(&G, hand_pos);
	}
	
	printf("ALL TESTS OK\n");
	
	exit(0);
}