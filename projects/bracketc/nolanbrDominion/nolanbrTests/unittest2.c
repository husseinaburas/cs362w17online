/*
File: unittest1.c
Author: Brent Nolan
Description:  This is a unit test for the buyCard function in dominion.c


*/

#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>

//variables for game state, cards, and test passing
struct gameState state;
struct gameState preTest;
int s;
int k[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int pass = 1;

void assert(int j, int t){
	if(j == 0) {
		printf("Test %i failed \n", t);
		pass = 0;
		}
	else 
		printf("Test %i success \n", t);
}

//memcpy(&preTest, state, sizeof(struct gameState));

int main(){

//init game and copy the preTest state
initializeGame(2, k, 2, &state);



 //test to make sure buyCard will return -1 when the current player has no buys left
state.numBuys = 0;
s = buyCard(5, &state);
assert(s == -1, 1);

//test to make sure buyCard will return -1 when the current player has no coins
state.numBuys = 5;
state.coins = 0;
s = buyCard(5, &state);
assert(s == -1, 2);

//test to make sure buyCard will return -1 when the current player does not have enough coins
state.coins = 3;
s = buyCard(3, &state);
assert(s == -1, 3);

//test to make sure buyCard will complete and return 0 when the current player has enough coins 
state.coins = 5;
s = buyCard(3, &state);
assert(s == 0, 3);

 if(pass == 0)
	 printf("buyCard TEST FAILED\n");
 else
	 printf("buyCard TEST SUCCESSFULLY COMPLETED\n");
  return 0;
 
}  