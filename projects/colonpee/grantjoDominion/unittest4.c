//Unit Test 4
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>

//test that shuffle works correctly, will return 0 if all was well and -1 if something fails
int testGameOver() {
	printf ("TESTING gameOver function!\n\n");
	int success = 1;
	// Create gamestate
    struct gameState G;

    printf ("2 supply piles at 0 and all other at 3,\ngame should not be over\n");
    

    for (int i = 0; i < 25; i++) {
    	G.supplyCount[i] = 3;
    }

    G.supplyCount[0] = 0;
    G.supplyCount[1] = 0;

    if (isGameOver(&G) == 0) {
    	printf("Game not over - PASS\n\n");
    }
    else {
    	printf("Game over - FAIL\n");
    	printf("testGameOver fails.\n");
    	success = 0;
    }

    printf ("3 supply piles at 0 and all other at 3,\ngame should be over\n");

    for (int i = 0; i < 25; i++) {
    	G.supplyCount[i] = 3;
    }

    G.supplyCount[0] = 0;
    G.supplyCount[1] = 0;
    G.supplyCount[2] = 0;

    if (isGameOver(&G) == 1) {
    	printf("Game over - PASS\n\n");
    }
    else {
    	printf("Game not over - FAIL\n");
    	printf("testGameOver fails.\n");
    	success = 0;
    }

	printf ("0 Province Cards left and all other at 3,\ngame should be over\n");

	for (int i = 0; i < 25; i++) {
	    G.supplyCount[i] = 3;
	}

    G.supplyCount[province] = 0;

    if (isGameOver(&G) == 1) {
    	printf("Game over - PASS\n\n");
    }
    else {
    	printf("Game not over - FAIL\n");
    	printf("testGameOver fails.\n");
    	success = 0;
    }

    if (success == 1) {
    	return 0;
    }
    else {
    	return 1;
    }
}


int main() {
	int x = testGameOver();
	if (x == 0) {
		printf("testGameOver passes.\n\n");
	}
	else {
		printf("testGameOver fails miserably.\n\n");
	}
    return 0;
}