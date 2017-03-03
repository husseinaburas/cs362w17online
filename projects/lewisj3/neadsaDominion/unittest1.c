#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1
int ERROR = 0;
#undef assert
#define assert(x) if(!(x)){printf("Assertion Error!\n"); ERROR = 1; }

int PLAYER = 0;
int NUM_PLAYERS = 4;

void fillHand(int cards[], int player, struct gameState *state)
{
    int i;
    for (i = 0; i < 5; i++){
        state->hand[player][i] = cards[i];
    }
}

void testUpdateCoins(int player, struct gameState *state, int bonus, int expectedCoins)
{
    int returnVal = updateCoins(player, state, bonus);
    //printf("Actual: %d, Expected: %d\n", state->coins, expectedCoins);
    assert(returnVal == 0);
    assert(state->coins == expectedCoins);
}

int main () {
    int bonus, expected;
    int player = PLAYER;
    int testCards[5] = {adventurer, council_room, feast, gardens, mine};
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = NUM_PLAYERS;
    state->handCount[player] = 5;

    fillHand(testCards, PLAYER, state);

    //No Coins
    bonus = 0;
    expected = 0;
    testUpdateCoins(PLAYER, state, bonus, expected);

    //Test 2 Copper
    state->hand[player][0] = copper;
    state->hand[player][1] = copper;
    bonus = 0;
    expected = 2;
    testUpdateCoins(PLAYER, state, bonus, expected);

    //Reset hand
    fillHand(testCards, PLAYER, state);

    //Test 1 Silver 1 Copper
    state->hand[player][0] = silver;
    state->hand[player][4] = copper;
    bonus = 0;
    expected = 3;
    testUpdateCoins(player, state, bonus, expected);

    //Reset Hand
    fillHand(testCards, player, state);

    //Test 1 silver 1 gold
    state->hand[player][0] = silver;
    state->hand[player][1] = gold;
    bonus = 0;
    expected = 5;
    testUpdateCoins(player, state, bonus, expected);


    //Test all gold
    int goldCards[5] = {gold, gold, gold, gold, gold};
    fillHand(goldCards, player, state);
    bonus = 0;
    expected = 15;
    testUpdateCoins(player, state, bonus, expected);


    //Test all gold and bonus
    bonus = 20;
    expected = 35;
    testUpdateCoins(PLAYER, state, bonus, expected);
    free(state);
	
	if(!ERROR){
		printf("unittest1 finished successfully\n");
	} else{
		printf("unittest1 finished with errors\n");
	}
    return 0;
}
