//  Author: William Miller - cs362
//  Filename: unittest2.c
//
//  Tests effect of dicardCard() (removes card from player hand and adds to discard pile or
//  removes cards from player hand and adds to trash pile)
//
//  Tests performed:
//      Preconditions:
//          valid game state
//          valid hand count
//
//      Tests:
//          adds smithy cards to player's hand and attempts to discard all
//          adds smithy cards to player's hand and attempts to trash all

#include "unittest2.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "testFunctions.h"
#include <stdlib.h>
#include <stdio.h>

#define HAND_SIZE 5

void testDicardCard(int numPlayers) {
    struct gameState* g;
    int player;
    int handPos;
    int playedCardCount;
    int handCount;
    int mismatch = 0;
    
    FILE* fp;
    fp = fopen("unittestresults.out", "a+");

    fprintf(fp, "\n\n** TESTING DISCARDCARD() **\n\n");

    for (player = 0; player < numPlayers; player++) {
        fprintf(fp, "\nTesting discard for player %d out of %d...\n\n", player, numPlayers);
        g = initGameState(numPlayers);
        handCount = g->handCount[player];
        
        // preconditions
        
        fprintf(fp, "Testing preconditions...\n");
        if (assertTrue(g != NULL)) {
            fprintf(fp, "game state valid...\n");
        } else {
            fprintf(fp, "invalid game state!\n");
        }
        if (assertTrue(handCount >= 0)) {
            fprintf(fp, "valid hand count...\n");
        } else {
            fprintf(fp, "invalid hand count (less than zero)!\n");
        }
        
        for (handPos = 0; handPos <= HAND_SIZE; handPos++) {
            g->hand[player][handPos] = smithy;
        }
        playedCardCount = g->playedCardCount;
        g->handCount[player] = HAND_SIZE;

        for (handPos = 0; handPos < HAND_SIZE; handPos++) {
            discardCard(handPos, player, g, 0);
        }
        
        // testing discard for hand of smithy cards
        
        for (handPos = 0; handPos < HAND_SIZE; handPos++) {
            if (!assertTrue(g->discard[player][handPos] == smithy)) {
                fprintf(fp, "DISCARD PILE MISMATCH.\n");
                mismatch = 1;
                break;
            }
        }
        
        if (assertTrue(g->handCount[player] == 0) && assertTrue(playedCardCount + HAND_SIZE == g->playedCardCount) && !mismatch) {
            fprintf(fp, "DISCARD TEST SUCCESSFUL. TEST PASSED.\n");
        } else {
            fprintf(fp, "DISCARD TEST UNSUCCESSFUL. TEST FAILED.\n");
        }
        
        free(g);
        
        fprintf(fp, "\nTesting trash for player %d out of %d...\n\n", player, numPlayers);
        g = initGameState(numPlayers);
        
        for (handPos = 0; handPos <= HAND_SIZE; handPos++) {
            g->hand[player][handPos] = smithy;
        }
        
        g->handCount[player] = HAND_SIZE;

        // testing trash for hand of smithy cards
        
        for (handPos = 0; handPos < HAND_SIZE; handPos++) {
            discardCard(handPos, player, g, 1);
        }
        
        if (assertTrue(g->handCount[player] == 0)) {
            fprintf(fp, "TRASH SUCCESSFUL. TEST PASSED.\n");
        } else {
            fprintf(fp, "TRASH UNSUCCESSFUL. TEST FAILED.\n");
        }

        free(g);
    }
    fclose(fp);
}