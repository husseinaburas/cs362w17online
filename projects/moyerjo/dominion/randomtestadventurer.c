#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//Testing adventurer

#define advMaxTests 1000

int main(int argc, char** argv) {
	int i;
	struct gameState pre, post;
	int curPlayer, handPos;

	for (i = 0; i < advMaxTests; i++) {
		randomSetup(&pre);
		curPlayer = pre.whoseTurn;
		handPos = rand() % pre.handCount[curPlayer];
		pre.hand[curPlayer][handPos] = adventurer;






	}













}