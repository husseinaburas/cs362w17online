//  Author: William Miller - cs362
//  Filename: randomtestcard2.c
//
//  Tests effect of smithy card (draw 3 cards, discard smithy, reduce player deck by 3)
//
//
//      Random Tests:
//          player hand is increased by 2 (net total)
//          player deck is is reduced by 3
//          smithy card is discarded

#include <stdlib.h>
#include <stdio.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

// maximum number of tests run

#define MAX_TESTS 100

// gameState() function cretes a fresh gameState struct with selected values randomizes to achieve maxmium
// coverage in random testing.

struct gameState* createTestState(int* handPos) {
    struct gameState* g = malloc(sizeof(struct gameState));
    int handCount;
    int player;
    int i;
    int numPlayers = rand() % (MAX_PLAYERS - 1) + 2; // selects betwen 2 and 4 players (boundary constraints of domininon.c)
    int seed = 100;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numPlayers, k, seed, g);
    
    // randomizing player, number of actions, hand count and deck count for that player
    
    g->whoseTurn = rand() % numPlayers;
    g->numActions = rand() % 10 + 1;
    g->handCount[g->whoseTurn] = rand() % MAX_HAND;
    g->deckCount[g->whoseTurn] = rand() % MAX_DECK;

    // creating discard pile of random size smaller size than hand of player
    
    while (g->discardCount[g->whoseTurn] > g->handCount[g->whoseTurn]) {
        g->discardCount[g->whoseTurn] = rand() % MAX_HAND;
    }
    
    player = g->whoseTurn;
    handCount = g->handCount[player];

    // filling player's hand with random cards
    
    for (i = 0; i < g->handCount[player]; i++) {
        g->hand[player][i] = rand() % 27;
    }

    // filling deck with random cards
    
    for (i = 0; i < g->deckCount[player]; i++) {
        g->deck[player][i] = rand() % 27;
    }

    // ensuring that one card is hand is smithy and saving its position
    
    *handPos = rand() % handCount;

    g->hand[player][*handPos] = smithy;


    return g;
}


int main(int argc, const char * argv[]) {
    int handPos = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int bonus = 0;
    int i;
    int player;
    int handCount;
    int handCountAfter;
    int actionCount;
    int actionCountAfter;
    int deckCount;
    int deckCountAfter;

    FILE* fp;
    fp = fopen("randomtestcard2.out", "a+");

    srand((int) atof(argv[1]));

    struct gameState* g;

    // running tests
    
    for (i = 0; i < MAX_TESTS; i++) {
        g = createTestState(&handPos);

        player = g->whoseTurn;

        handCount = g->handCount[player];
        actionCount = g->numActions;
        deckCount = g->deckCount[player];

        cardEffect(smithy, choice1, choice2, choice3, g, handPos, &bonus);

        handCountAfter = g->handCount[player];
        actionCountAfter = g->numActions;
        deckCountAfter = g->deckCount[player];

        // testing hand count
        
        fprintf(fp, "Num of cards in hand before smithy played: %d"
                "\nNum of cards in hand after smithy played: %d\n", handCount, handCountAfter);

        if (handCount + 2 == handCountAfter) {
            fprintf(fp, "HAND COUNT: TEST PASSED.\n");
        } else {
            fprintf(fp, "HAND COUNT: TEST FAILED.\n");
        }


        // testing deck count

        fprintf(fp, "Num of cards in deck before smithy played: %d"
                "\nNum of cards in deck after smithy played: %d\n", deckCount, deckCountAfter);

        if (deckCount - 3 == deckCountAfter) {
            fprintf(fp, "DECK COUNT: TEST PASSED.\n");
        } else {
            fprintf(fp, "DECK COUNT: TEST FAILED.\n");
        }


        if (g->hand[player][handPos] != smithy) {
            fprintf(fp, "DISCARD TEST; LAST CARD NOT SMITHY: TEST PASSED.\n");
        } else {
            fprintf(fp, "DISCARD TEST; LAST CARD STILL SMITHY: TEST FAILED.\n");
        }
        free(g);
    }

    fclose(fp);
    return 0;
}
