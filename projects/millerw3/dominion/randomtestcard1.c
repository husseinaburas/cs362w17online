//  Author: William Miller - cs362
//  Filename: randomtestcard1.c
//
//  Tests effect of village card (draw 1 cards, discard village, reduce player deck by 1, add 2 actions)
//
//      Random Tests:
//          player hand is increased by 0 (net total)
//          player deck is is reduced by 1
//          village card is discarded
//          player action count increased by 2


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
    int numPlayers = rand() % (MAX_PLAYERS - 1) + 2;   // selects betwen 2 and 4 players (boundary constraints of domininon.c)
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
        g->hand[player][i] = rand() % 27;
    }
    
    // ensuring that one card is hand is village and saving its position
    
    *handPos = rand() % handCount;
    
    g->hand[player][*handPos] = village;
    
    
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
    fp = fopen("randomtestcard1.out", "a+");
    srand((int) atof(argv[1]));
    struct gameState* g;
    
    // running tests
    
    for (i = 0; i < MAX_TESTS; i++) {
        g = createTestState(&handPos);
        
        player = g->whoseTurn;
        
        handCount = g->handCount[player];
        actionCount = g->numActions;
        deckCount = g->deckCount[player];
                
        cardEffect(village, choice1, choice2, choice3, g, handPos, &bonus);
        
        handCountAfter = g->handCount[player];
        actionCountAfter = g->numActions;
        deckCountAfter = g->deckCount[player];
        
        // testing hand count
        
        fprintf(fp, "Num of cards in hand before village played: %d"
                "\nNum of cards in hand after village played: %d\n", handCount, handCountAfter);
        
        if (handCount == handCountAfter) {
            fprintf(fp, "HAND COUNT: TEST PASSED.\n");
        } else {
            fprintf(fp, "HAND COUNT: TEST FAILED.\n");
        }

        
        // testing deck count
        
        fprintf(fp, "Num of cards in deck before village played: %d"
                "\nNum of cards in deck after village played: %d\n", deckCount, deckCountAfter);
        
        if (deckCount - 1 == deckCountAfter) {
            fprintf(fp, "DECK COUNT: TEST PASSED.\n");
        } else {
            fprintf(fp, "DECK COUNT: TEST FAILED.\n");
        }
        
        
        // testing action count
        
        fprintf(fp, "Num of actions in hand before village played: %d"
                "\nNum of actions in hand after village played: %d\n", actionCount, actionCountAfter);
        
        if (actionCount + 2 == actionCountAfter) {
            fprintf(fp, "ACTION COUNT: TEST PASSED.\n");
        } else {
            fprintf(fp, "ACTION COUNT: TEST FAILED.\n");
        }
        
        // testing discard
        
        if (g->hand[player][handPos] != village) {
            fprintf(fp, "DISCARD TEST; LAST CARD NOT VILLAGE: TEST PASSED.\n");
        } else {
            fprintf(fp, "DISCARD TEST; LAST CARD STILL VILLAGE: TEST FAILED.\n");
        }
        free(g);
    }
    
    fclose(fp);
    return 0;
}
