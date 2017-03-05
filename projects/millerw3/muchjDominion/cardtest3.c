//  Author: William Miller - cs362
//  Filename: cardtest3.c
//
//  Tests effect of village card (draw 1 cards, discard village, reduce player deck by 1, add 2 actions)
//
//  Tests performed:
//      Preconditions:
//          valid game state
//          valid hand count
//          inserted card == village
//
//      Tests:
//          player hand is increased by 0 (net total)
//          player deck is is reduced by 1
//          village card is discarded
//          player action count increased by 2


#include <stdio.h>
#include <stdlib.h>
#include "cardtest2.h"
#include "testFunctions.h"
#include "dominion.h"
#include "dominion_helpers.h"

void testVillage(struct gameState* g) {
    
    // hands, game, etc. initialized; deck, action and hand counts recorded
    
    int player = whoseTurn(g);
    int handCount = g->handCount[player];
    int handCountAfter;
    int deckCountAfter;
    int deckCount = g->deckCount[player];
    int actionCount = g->numActions;
    int actionCountAfter;
    int choice1, choice2, choice3, bonus;
    choice1 = choice2 = choice3 = bonus = 0;
    int lastCard = g->hand[player][g->handCount[player] - 1];
    int handPos = g->handCount[player] - 1;
    
    FILE* fp;
    fp = fopen("unittestresults.out", "a+");
    
    fprintf(fp, "\n\n** TESTING VILLAGE: PLAYER %d of %d**\n\n", player + 1, g->numPlayers);
    
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
    if (assertTrue(lastCard == village)) {
        fprintf(fp, "last card village OK...\n");
    } else {
        fprintf(fp, "last card not village!\n");
    }
    cardEffect(village, choice1, choice2, choice3, g, handPos, &bonus);
    
    // hand, deck and action counts after effect applied recorded
    
    lastCard = g->hand[player][g->handCount[player] - 1];
    handCountAfter = g->handCount[player];
    deckCountAfter = g->deckCount[player];
    actionCountAfter = g->numActions;
    
    // testing hand count
    
    fprintf(fp, "Num of cards in hand before village played: %d"
           "\nNum of cards in hand after village played: %d\n", handCount, handCountAfter);
    
    if (assertTrue(handCount == handCountAfter)) {
        fprintf(fp, "HAND COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "HAND COUNT: TEST FAILED.\n");
    }
    
    // testing action count
    
    if (assertTrue(actionCount + 2 == actionCountAfter)) {
        fprintf(fp, "ACTION COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "ACTION COUNT: TEST FAILED.\n");
    }
    
    fprintf(fp, "Num of cards in deck before village played: %d"
           "\nNum of cards in deck after village played: %d\n", deckCount, deckCountAfter);
    
    // testing deck count
    
    if (assertTrue(deckCount - 1 == deckCountAfter)) {
        fprintf(fp, "DECK COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "DECK COUNT: TEST FAILED.\n");
    }
    
    if (assertTrue(lastCard != village)) {
        fprintf(fp, "DISCARD TEST; LAST CARD NOT VILLAGE: TEST PASSED.\n");
    } else {
        fprintf(fp, "DISCARD TEST; LAST CARD STILL VILLAGE: TEST FAILED.\n");
    }
    
    fclose(fp);
    return;
}