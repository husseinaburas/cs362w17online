//unittest3.c
//whoseTurn

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>


int main(){

	struct gameState state;

	int turn = 0;
	int p = 0;

	for (int i = 0; i < 15; i++){
		state.whoseTurn = turn;
		p = whoseTurn(&state);

		if(p == turn){
			printf("whoseTurn: Test %d passed", i);
		}
		else{
			return 0;
		}
    turn++;
	}

	return 0;

}