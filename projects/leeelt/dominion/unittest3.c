/* -----------------------------------------------------------------------
 * Author: Elton Lee
 * Date: 2-4-2017
 * unittest3.c
 * unit test for fullDeckCount function
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int p = 0; // player 1
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("\nRunning unittest3\n");
    memset(&G, 23, sizeof(struct gameState)); // clear the game state
    initializeGame(numPlayer, k, seed, &G);   // initialize a new game

    printf("Test a. 0 coppers in total\n");
    fillArrays(&G, p, copper, 0, copper, 0, copper, 0);
    printf("total coppers = %d, expected total = 0\n", fullDeckCount(p, copper, &G));
    assert(fullDeckCount(p, copper, &G) == 0);

	printf("Test b. 5 coppers in deck\n");
    fillArrays(&G, p, copper, 5, copper, 0, silver, 0);
    printf("total coppers = %d, expected total = 5\n", fullDeckCount(p, copper, &G));
    assert(fullDeckCount(p, copper, &G) == 5);

	printf("Test c. 7 coppers in hand\n");
    fillArrays(&G, p, copper, 0, copper, 7, silver, 0);
    printf("total coppers = %d, expected total = 7\n", fullDeckCount(p, copper, &G));
    assert(fullDeckCount(p, copper, &G) == 7);

	printf("Test d. 9 coppers in discard\n");
    fillArrays(&G, p, copper, 0, copper, 0, copper, 9);
    printf("total coppers = %d, expected total = 9\n", fullDeckCount(p, copper, &G));
    assert(fullDeckCount(p, copper, &G) == 9);

	printf("Test e. 5 coppers in deck, 7 coppers in hand, 0 coppers in discard\n");
    fillArrays(&G, p, copper, 5, copper, 7, copper, 0);
    printf("total coppers = %d, expected total = 12\n", fullDeckCount(p, copper, &G));
    assert(fullDeckCount(p, copper, &G) == 12);

	printf("Test f. 5 coppers in deck, 0 coppers in hand, 9 coppers in discard\n");
    fillArrays(&G, p, copper, 5, copper, 0, copper, 9);
    printf("Test f. total coppers = %d, expected total = 14\n", fullDeckCount(p, copper, &G));
    assert(fullDeckCount(p, copper, &G) == 14);

	printf("Test g. 0 coppers in deck, 7 coppers in hand, 9 coppers in discard\n");
    fillArrays(&G, p, copper, 0, copper, 7, copper, 9);
    printf("total coppers = %d, expected total = 16\n", fullDeckCount(p, copper, &G));
    assert(fullDeckCount(p, copper, &G) == 16);

	printf("Test h. 5 coppers and 1 gold in hand\n");
    fillArrays(&G, p, copper, 5, copper, 0, copper, 0);
	G.deck[p][5] = gold;
	G.deckCount[p]++;
    printf("total coppers = %d, expected total = 5\n", fullDeckCount(p, copper, &G));
    assert(fullDeckCount(p, copper, &G) == 5);

	printf("Test i. 5 coppers in deck, 3 golds in hand, 6 silvers in discard\n");
    fillArrays(&G, p, copper, 5, gold, 3, silver, 6);
    printf("total coppers = %d, expected total = 5\n", fullDeckCount(p, copper, &G));
    assert(fullDeckCount(p, copper, &G) == 5);

    printf("All tests passed!\n");
    return 0;
}

// Fill the deck, hand, and discard with the specified cards.
int fillArrays(struct gameState *G, int p, int card_deck, int size_deck, int card_hand, int size_hand, int card_discard, int size_discard)
{
    int i;
    // clear deck of all cards
    for (i = 0; i < MAX_DECK; i++) G->deck[p][i] = -1;
    G->deckCount[p] = 0;
    for (i = 0; i < MAX_HAND; i++) G->hand[p][i] = -1;
    G->handCount[p] = 0;
    for (i = 0; i < MAX_DECK; i++) G->discard[p][i] = -1;
    G->discardCount[p] = 0;

	// fill with inputs
    for (i = 0; i < size_hand; i++)
    {
	G->hand[p][i] = card_hand;
    }
    G->handCount[p] = size_hand;

    for (i = 0; i < size_deck; i++)
    {
	G->deck[p][i] = card_deck;
    }
    G->deckCount[p] = size_deck;

    for (i = 0; i < size_discard; i++)
    {
	G->discard[p][i] = card_discard;
    }
    G->discardCount[p] = size_discard;

    return 0;
}