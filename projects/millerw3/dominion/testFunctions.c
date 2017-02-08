//  Author: William Miller - cs362
//  Filename: testFunctions.c

#include <stdio.h>
#include <stdlib.h>
#include "testFunctions.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "cardtest1.h"
#include "cardtest2.h"
#include "cardtest3.h"
#include "cardtest4.h"

// assert function

int assertTrue(int cond) {
    if (cond) {
        return 1;
    } else {
        return 0;
    }
}

// initializes game state struct with random seed and number of players specified by user

struct gameState* initGameState(int numPlayers) {
    struct gameState* g = malloc(sizeof(struct gameState));
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numPlayers, k, 10, g);
    return g;
}

// tests games of size 2 to MAX_PLAYERS for card specified by int card 

void testAllPlayers(int card, int numPlayers) {
    int i;
    int player;
    struct gameState* g = initGameState(numPlayers);
    
    
    for (i = 0; i < numPlayers; i++) {
        player = whoseTurn(g);
        g->hand[player][g->handCount[player] - 1] = card;

        switch (card) {
            case great_hall:
                testGreatHall(g);
                break;
            case smithy:
                testSmithy(g);
                break;
            case village:
                testVillage(g);
                break;
            case adventurer:
                testAdventurer(g);
                break;
            default:
                printf("Invalid card type.\n");
                break;
        }
        endTurn(g);
    }
    free(g);
    
    
}