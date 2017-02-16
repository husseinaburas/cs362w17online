//  Author: William Miller - cs362
//  Filename: randomtestadventurer.c
//
//  Tests effect of adventurer card (draw 2 cards (treasure), discard adventurer, reduce player deck by 2)
//
//  Tests performed:
//
//      Random Tests:
//          player hand is increased by 1 (net total) (both treasure cards)
//          player deck is is reduced by 2
//          adventurer card is discarded

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
    int treasIdx1 = 0;
    int treasIdx2 = 0;
    int treasureType;
    int numPlayers = rand() % (MAX_PLAYERS - 1) + 2;   // selects betwen 2 and 4 players (boundary constraints of domininon.c)
    int seed = 100;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
    initializeGame(numPlayers, k, seed, g);
    
    // randomizing player, number of actions, hand count and deck count for that player
    
    g->whoseTurn = rand() % numPlayers;
    g->handCount[g->whoseTurn] = rand() % MAX_HAND + 1;
    g->deckCount[g->whoseTurn] = rand() % MAX_DECK + 1;
    
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
    
    // selecting random indices at which to store two random treasure cards
    
    while (treasIdx1 == treasIdx2) {
        treasIdx1 = rand() % g->handCount[player];
        treasIdx2 = rand() % g->handCount[player];
    }
    
    treasureType = rand() % 3 + 4;
    g->hand[player][treasIdx1] = treasureType;
    treasureType = rand() % 3 + 4;
    g->hand[player][treasIdx2] = treasureType;
    
    // ensuring that one card is hand is adventurer and saving its position
    
    *handPos = rand() % handCount;
    
    g->hand[player][*handPos] = adventurer;
    
    
    return g;
}


int countTreasureCards(struct gameState* g, int player) {
    int i;
    int treasureCount = 0;
    for (i = 0; i < g->handCount[player]; i++) {
        if (g->hand[player][i] == copper || g->hand[player][i] == silver || g->hand[player][i] == gold) {
            treasureCount++;
        }
    }
    return treasureCount;
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
    int deckCount;
    int deckCountAfter;
    int treasureCountBefore;
    int treasureCountAfter;
    
    FILE* fp;
    fp = fopen("randomtestadventurer.out", "a+");
    
    srand((int) atof(argv[1]));
    struct gameState* g;
    
    // running tests
    
    for (i = 0; i < MAX_TESTS; i++) {
        g = createTestState(&handPos);
        
        player = g->whoseTurn;
        
        handCount = g->handCount[player];
        deckCount = g->deckCount[player];
        treasureCountBefore = countTreasureCards(g, player);
        
        cardEffect(adventurer, choice1, choice2, choice3, g, handPos, &bonus);
        
        handCountAfter = g->handCount[player];
        deckCountAfter = g->deckCount[player];
        treasureCountAfter = countTreasureCards(g, player);
        
        // testing hand count
        
        fprintf(fp, "Num of cards in hand before adventurer played: %d"
                "\nNum of cards in hand after adventurer played: %d\n", handCount, handCountAfter);
        
        if (handCount + 1 == handCountAfter) {
            fprintf(fp, "HAND COUNT: TEST PASSED.\n");
        } else {
            fprintf(fp, "HAND COUNT: TEST FAILED.\n");
        }
        
        fprintf(fp, "Num of cards in deck before adventurer played: %d"
                "\nNum of cards in deck after adventurer played: %d\n", deckCount, deckCountAfter);
        
        // testing deck count
        if (deckCount - 2 == deckCountAfter) {
            fprintf(fp, "DECK COUNT: TEST PASSED.\n");
        } else {
            fprintf(fp, "DECK COUNT: TEST FAILED.\n");
        }
        fprintf(fp, "Checking hand for treasure...\n");
        
        // testing num of treasure cards in deck
        
        fprintf(fp, "Num of treasure cards in hand before adventurer played: %d"
                "\nNum of treasure cards in hand after adventurer played: %d\n", treasureCountBefore, treasureCountAfter);
        
        if (treasureCountBefore == treasureCountAfter - 2) {
            fprintf(fp, "TREASURE COUNT: TEST PASSED.\n");
        } else {
            fprintf(fp, "TREASURE COUNT: TEST FAILED.\n");
        }
        
        // testing discard
        
        if (g->hand[player][handPos] != adventurer) {
            fprintf(fp, "DISCARD TEST; LAST CARD NOT ADVENTURER: TEST PASSED.\n");
        } else {
            fprintf(fp, "DISCARD TEST; LAST CARD STILL ADVENTURER: TEST FAILED.\n");
        }
        free(g);
    }
    
    fclose(fp);
    return 0;
}
