/*
 * unittest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o refactor.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o refactor.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "getCost()"
#define ASSERT(exp, MSG) if(exp) printf("%s: PASS!\n", MSG); else printf("%s: FAILED!\n", MSG)
#define ASSERT(exp) if(!exp) {printf("Test FAILED!\n"); error = 1;}

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m, error=0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	//expected cost values from card enum
	int k[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};


	printf("----------------- Testing function: %s ----------------\n", TESTCARD);

	// ----------- TEST 1:verify cost values returned from getCost() --------------
	printf("TEST 1: verify cost values returned from getCost()\n");

	for (i = 0; i < treasure_map+1; i++)
		ASSERT((k[i] == getCost(i)));

	// ----------- TEST 2: verify getCost() --------------
	printf("TEST 2: verify unknown cards return -1 from getCost()\n");
	for (i = treasure_map+1; i < (treasure_map+100); i++)
		ASSERT((-1 == getCost(i)));
	
	if (error)
		printf("TEST Failed!\n");
	else
		printf("TEST PASSED!\n");
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}