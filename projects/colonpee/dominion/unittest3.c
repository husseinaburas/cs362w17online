//Unit Test 3
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>

//test that shuffle works correctly, will return 0 if all was well and -1 if something fails
int testSupplyCount() {
	printf ("TESTING supplyCount function!\n\n");
	int success = 1;
	// Create gamestate
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int r = rand();

    printf ("If 2 players are playing, supply count for Estate, Duchy, and Province cards\nshould be 8 for each card.\n");

    initializeGame(2, k, r, &G);

    int x = supplyCount(estate, &G);
    int y = supplyCount(duchy, &G);
    int z = supplyCount(province, &G);

    if (x == 8) {
        printf("Supply count for Estate is: %d - PASS\n", x);
    }
    else {
        printf("Supply count for Estate is: %d - FAIL (should be 8)\n", x);
        success = 0;
    }
    if (y == 8) {
        printf("Supply count for Duchy is: %d - PASS\n", y);
    }
    else {
        printf("Supply count for Duchy is: %d - FAIL (should be 8)\n", y);
        success = 0;
    }
    if (z == 8) {
        printf("Supply count for Province is: %d - PASS\n", z);
    }
    else {
        printf("Supply count for Province is: %d - FAIL (should be 8)\n", z);
        success = 0;
    }

    printf ("If 3 players are playing, supply count for Estate, Duchy, and Province cards\nshould be 12 for each card.\n");

    initializeGame(3, k, r, &G);

    x = supplyCount(estate, &G);
    y = supplyCount(duchy, &G);
    z = supplyCount(province, &G);

    if (x == 12) {
	    printf("Supply count for Estate is: %d - PASS\n", x);
    }
    else {
    	printf("Supply count for Estate is: %d - FAIL (should be 12)\n", x);
	    success = 0;
    }
    if (y == 12) {
        printf("Supply count for Duchy is: %d - PASS\n", y);
    }
    else {
        printf("Supply count for Duchy is: %d - FAIL (should be 12)\n", y);
        success = 0;
    }
    if (z == 12) {
        printf("Supply count for Province is: %d - PASS\n", z);
    }
    else {
        printf("Supply count for Province is: %d - FAIL (should be 12)\n", z);
        success = 0;
    }

    printf ("If 2 players are playing, supply count for Curse cards should be 10.\n");

    initializeGame(2, k, r, &G);

    int g = supplyCount(curse, &G);

    if (g == 10) {
    	printf("Supply count for Curse is: %d - PASS\n", g);
    }
    else {
    	printf("Supply count for Curse is: %d - FAIL\n", g);
    	success = 0;
    }

    printf ("If 3 players are playing, supply count for Curse cards should be 20.\n");

    initializeGame(3, k, r, &G);

    g = supplyCount(curse, &G);

    if (g == 20) {
    	printf("Supply count for Curse is: %d - PASS\n", g);
    }
    else {
    	printf("Supply count for Curse is: %d - FAIL\n", g);
    	success = 0;
    }

    printf ("If 4 players are playing, supply count for Curse cards should be 30.\n");

    initializeGame(4, k, r, &G);

    g = supplyCount(curse, &G);

    if (g == 30) {
    	printf("Supply count for Curse is: %d - PASS\n", g);
    }
    else {
    	printf("Supply count for Curse is: %d - FAIL\n", g);
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
    int x = testSupplyCount();

    if (x == 0) {
    	printf ("testSupplyCount passes.\n\n");
    }
    else {
    	printf ("testSupplyCount fails miserably.\n\n");
    }
    return 0;
}