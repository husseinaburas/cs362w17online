#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "asserttrue.h"

void asserttrue(char* test_name, int actual, int expected){
	printf("%s = %d, expected = %d    ", test_name, actual, expected);
	if(actual == expected)
		printf("PASS\n");
	else
		printf("FAIL\n");
}

int cards_in_hand(struct gameState* state, int player, int card){
	int i;
	int card_count = 0;
	for(i = 0; i < state->handCount[player]; i++){
		if(state->hand[player][i] == card){
			card_count++;
		}
	}
	return card_count;
}

int treasure_in_hand(struct gameState* state, int player){
	int i;
	int treasure_count = 0;
	int card;
	for(i = 0; i < state->handCount[player]; i++){
		card = state->hand[player][i];
		if(card == copper || card == silver || card == gold){
			treasure_count++;
		}
	}
	return treasure_count;
}