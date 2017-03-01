/* -----------------------------------------------------------------------
 * Author: Elton Lee
 * Date: 2-6-2017
 * unittest4.c
 * unit test for isGameOver function
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    printf("\nRunning unittest4\n");
    initializeGame(numPlayer, k, seed, &G);   // initialize a new game
	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
    printf("Test a. full provinces, full supply piles\n");
    printf("isGameOver? = %d, expected = %d\n", isGameOver(&testG), 0);
    assert(isGameOver(&testG) == 0);

	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
    printf("Test b. empty provinces, full supply piles\n");
	testG.supplyCount[province] = 0;
    printf("isGameOver? = %d, expected = %d\n", isGameOver(&testG), 1);
    assert(isGameOver(&testG) == 1);

	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
    printf("Test c. 1 province left, full supply piles\n");
	testG.supplyCount[province] = 1;
    printf("isGameOver? = %d, expected = %d\n", isGameOver(&testG), 0);
    assert(isGameOver(&testG) == 0);

	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
    printf("Test d. full provinces, 3 empty supply piles\n");
	testG.supplyCount[copper] = 0;
	testG.supplyCount[adventurer] = 0;
	testG.supplyCount[baron] = 0;
    printf("isGameOver? = %d, expected = %d\n", isGameOver(&testG), 1);
    assert(isGameOver(&testG) == 1);
	
	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
    printf("Test e. full provinces, 1 empty supply piles\n");
	testG.supplyCount[adventurer] = 0;
   	printf("isGameOver? = %d, expected = %d\n", isGameOver(&testG), 0);
    assert(isGameOver(&testG) == 0);

	memcpy(&testG, &G, sizeof(struct gameState)); // copy the game state to a test case
    printf("Test f. empty provinces, 2 empty supply piles\n");
	testG.supplyCount[adventurer] = 0;
	testG.supplyCount[province] = 0;
	testG.supplyCount[gold] = 0;
   	printf("isGameOver? = %d, expected = %d\n", isGameOver(&testG), 1);
    assert(isGameOver(&testG) == 1);


    printf("All tests passed!\n");
    return 0;
}