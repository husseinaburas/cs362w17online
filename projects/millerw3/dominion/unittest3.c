//  Author: William Miller - cs362
//  Filename: unittest3.c
//
//  Tests effect of whoseTurn() (test result of whoseTurn() after endTurn() completed (current player has not cycled back to zero
//  and returns the current player)
//
//  Tests performed:
//      Preconditions:
//          valid game state

//      Tests:
//          cycles through players via endTurn() and tests whether current player value has incremented properly

#include "unittest3.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "testFunctions.h"
#include <stdlib.h>
#include <stdio.h>

#define HAND_SIZE 5

void testWhoseTurn(int numPlayers) {
    struct gameState* g = initGameState(numPlayers);
    int player;
    FILE* fp;
    fp = fopen("unittestresults.out", "a+");
    
    // preconditions
    
    fprintf(fp, "Testing preconditions...\n");
    if (assertTrue(g != NULL)) {
        fprintf(fp, "game state valid...\n");
    }
    
    fprintf(fp, "\n\n** TESTING WHOSETURN() **\n\n");
    
    // testing whoseTurn()
    
    for (player = 0; player < numPlayers; player++) {
        fprintf(fp, "\nTesting player %d of %d...\n\n", player + 1, numPlayers);
        endTurn(g);
        if (assertTrue(whoseTurn(g) != 0) && !assertTrue(whoseTurn(g) - 1 == player)) {
            fprintf(fp, "WHOSE TURN TEST FAILED.\n");
            fclose(fp);
            return;
        }
        fprintf(fp, "WHOSE TURN TEST SUCCESSFUL.\n");
    }
    
    fclose(fp);
    return;
}
