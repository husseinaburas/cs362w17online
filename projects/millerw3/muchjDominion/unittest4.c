//  Author: William Miller - cs362
//  Filename: unittest4.c
//
//  Tests effect of gainCard() (tests all flags associated with gainCard(); attempts to add an adventurer card
//                              to player deck, player hand and player discard)
//
//  Tests performed:
//      Preconditions:
//          valid game state
//          valid hand count
//
//      Tests:
//          attempts to add adventurer card to player's discard pile
//          attempts to add adventurer card to player's deck
//          attempts to add adventurer card to player's hand

#include "unittest4.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "testFunctions.h"
#include <stdlib.h>
#include <stdio.h>

void testGainCard(int numPlayers) {
    int flag;
    int player;
    int deckCount;
    int handCount;
    int discardCount;
    struct gameState* g;
    FILE* fp;
    fp = fopen("unittestresults.out", "a+");
    
    fprintf(fp, "\n\n** TESTING GAINCARD() **\n\n");

    g = initGameState(numPlayers);
    
    for (player = 0; player < numPlayers; player++) {
        fprintf(fp, "\nTesting player %d of %d...\n\n", player + 1, numPlayers);
        player = whoseTurn(g);
        discardCount = g->discardCount[player];
        deckCount = g->deckCount[player];
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
        
        
        for (flag = 0; flag < 3; flag++) {
            gainCard(adventurer, g, flag, player);

            // testing add to deck
            
            if (flag == 1) {
                fprintf(fp, "Testing add to deck...\n");
                
                fprintf(fp, "Expected deck value: %d Actual value: %d\nExpected deck count: %d Actual deck count: %d\n", adventurer, g->deck[player][g->deckCount[player]], deckCount + 1, g->deckCount[player]);
                if (assertTrue(g->deck[player][g->deckCount[player]] == adventurer) && assertTrue(g->deckCount[player] - 1 == deckCount)) {
                    fprintf(fp, "ADD TO DECK SUCCESSFUL. TEST PASSED.\n");
                } else {
                    fprintf(fp, "ADD TO DECK UNSUCCESSFUL. TEST FAILED.\n");
                }
                
            // testing add to hand
                
            } else if (flag == 2) {
                fprintf(fp, "Testing add to hand...\n");
                fprintf(fp, "Expected hand value: %d Actual value: %d\nExpected hand count: %d Actual hand count: %d\n", adventurer, g->hand[player][g->handCount[player]], handCount + 1, g->handCount[player]);
                if (assertTrue(g->hand[player][g->handCount[player]] == adventurer) && assertTrue(g->handCount[player] == handCount + 1)) {
                    fprintf(fp, "ADD TO HAND SUCCESSFUL. TEST PASSED.\n");
                } else {
                    fprintf(fp, "ADD TO HAND UNSUCCESSFUL. TEST FAILED.\n");
                }
                
            // testing add to discard

            } else {
                fprintf(fp, "Testing add to discard...\n");
                fprintf(fp, "Expected discard value: %d Actual value: %d\nExpected discard count: %d Actual discard count: %d\n", adventurer, g->discard[player][g->discardCount[player]], discardCount + 1, g->discardCount[player]);
                if (assertTrue(g->discard[player][g->discardCount[player]] == adventurer) && assertTrue(g->discardCount[player] == discardCount + 1)) {
                    fprintf(fp, "ADD TO DISCARD SUCCESSFUL. TEST PASSED.\n");
                } else {
                    fprintf(fp, "ADD TO DISCARD UNSUCCESSFUL. TEST FAILED.\n");
                }

            }
        }
        endTurn(g);
    }
    fclose(fp);
}
