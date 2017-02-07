//  Author: William Miller - cs362
//  Filename: unittest1.c
//
//  Tests effect of updateCards() (correctly update coin counts (numCoins * denom + bonus) w/ hands of different
//  denominations and all bonus sizes up to MAX_BONUS)
//
//  Tests performed:
//      Preconditions:
//          valid game state
//          valid hand count
//
//      Tests:
//          test hand of coppers
//          test hand of silvers
//          test hand of golds
//          test with bonuses of all sizes up to MAX_BONUS


#include "unittest1.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "testFunctions.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_BONUS 10
#define HAND_SIZE 5

void testUpdateCoins(numPlayers) {
    struct gameState* g;
    int player;
    int handPos;
    int bonus;
    int handCount;
    
    FILE* fp;
    fp = fopen("unittestresults.out", "a+");
    
    fprintf(fp, "\n\n** TESTING UPDATECOINS() **\n\n");
    
    // testing all players
    
    for (player = 0; player < numPlayers; player++) {
        fprintf(fp, "\nTesting player %d out of %d w/ coppers...\n\n", player + 1, numPlayers);
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
        
        // testing all bonus sizes up to MAX_BONUS
        // testing hand of all coppers
        
        for (bonus = 0; bonus <= MAX_BONUS; bonus++) {
            for (handPos = 0; handPos <= HAND_SIZE; handPos++) {
                g->hand[player][handPos] = copper;
            }
            g->handCount[player] = HAND_SIZE;
            updateCoins(player, g, bonus);
            fprintf(fp, "Expected Coins: %d Actual Coins: %d\n", HAND_SIZE * 1 + bonus, g->coins);
            if (assertTrue(g->coins == HAND_SIZE * 1 + bonus)) {
                fprintf(fp, "HAND W/ COPPERS: TEST PASSED.\n");
            } else {
                fprintf(fp, "HAND W/ COPPERS: TEST FAILED.\n");
            }
        }
        free(g);
    }
    
    // testing all players
    
    for (player = 0; player < numPlayers; player++) {
        fprintf(fp, "\nTesting player %d out of %d w/ silvers...\n\n", player + 1, numPlayers);
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
        
        // testing all bonus sizes up to MAX_BONUS
        // testing hand of all silvers
        
        for (bonus = 0; bonus < MAX_BONUS; bonus++) {
            for (handPos = 0; handPos < HAND_SIZE; handPos++) {
                g->hand[player][handPos] = silver;
            }
            g->handCount[player] = HAND_SIZE;
            updateCoins(player, g, bonus);
            fprintf(fp, "Expected Coins: %d Actual Coins: %d\n", HAND_SIZE * 2 + bonus, g->coins);
            if (assertTrue(g->coins == HAND_SIZE * 2 + bonus)) {
                fprintf(fp, "HAND W/ SILVERS: TEST PASSED.\n");
            } else {
                fprintf(fp, "HAND W/ SILVERS: TEST FAILED.\n");
            }
        }
        free(g);
    }
    
    for (player = 0; player < numPlayers; player++) {
        fprintf(fp, "\nTesting player %d out of %d w/ golds...\n\n", player + 1, numPlayers);
        for (bonus = 0; bonus < MAX_BONUS; bonus++) {
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
            
            // testing all bonus sizes up to MAX_BONUS
            // testing hand of all golds
            
            for (handPos = 0; handPos < HAND_SIZE; handPos++) {
                g->hand[player][handPos] = gold;
            }
            g->handCount[player] = HAND_SIZE;
            updateCoins(player, g, bonus);
            fprintf(fp, "Expected Coins: %d Actual Coins: %d\n", HAND_SIZE * 3 + bonus, g->coins);
            if (assertTrue(g->coins == HAND_SIZE * 3 + bonus)) {
                fprintf(fp, "HAND W/ GOLD: TEST PASSED.\n");
            } else {
                fprintf(fp, "HAND W/ GOLD: TEST FAILED.\n");
            }
            free(g);
        }
    }
    
    fclose(fp);
    
    return;
}