//  Author: William Miller - cs362
//  Filename: cardtest1.c
//
//  Tests effect of smithy card (draw 3 cards, discard smithy, reduce player deck by 3)
//
//  Tests performed:
//      Preconditions:
//          valid game state
//          valid hand count
//          inserted card == smithy
//
//      Tests:
//          player hand is increased by 2 (net total)
//          player deck is is reduced by 3
//          smithy card is discarded

#include <stdio.h>
#include <stdlib.h>
#include "cardtest1.h"
#include "testFunctions.h"
#include "dominion.h"
#include "dominion_helpers.h"

void testSmithy(struct gameState* g) {
    
    // hands, game, etc. initialized; deck and hand counts recorded
    
    int player = whoseTurn(g);
    int handCount = g->handCount[player];
    int deckCount = g->deckCount[player];
    int handCountAfter;
    int deckCountAfter;
    int choice1, choice2, choice3, bonus;
    choice1 = choice2 = choice3 = bonus = 0;
    int lastCard = g->hand[player][g->handCount[player] - 1];
    int handPos = g->handCount[player] - 1;    
    FILE* fp;
    fp = fopen("unittestresults.out", "a+");
    
    fprintf(fp, "\n\n** TESTING SMITHY: PLAYER %d of %d**\n\n", player + 1, g->numPlayers);
    
    //  preconditions
    
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
    if (assertTrue(lastCard == smithy)) {
        fprintf(fp, "last card smithy OK...\n");
    } else {
        fprintf(fp, "last card not smithy!\n");
        fprintf(fp, "%d", lastCard);
    }
    
    cardEffect(smithy, choice1, choice2, choice3, g, handPos, &bonus);
    
    // hand and deck counts after effect applied recorded
    
    deckCountAfter = g->deckCount[player];
    handCountAfter = g->handCount[player];
    
    // testing hand count
    
    fprintf(fp, "Num of cards in hand before smithy played: %d"
           "\nNum of cards in hand after smithy played: %d\n", handCount, handCountAfter);

    if (assertTrue(handCount + 2 == handCountAfter)) {
        fprintf(fp, "HAND COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "HAND COUNT: TEST FAILED.\n");
    }
    
    // testing deck count
    
    fprintf(fp, "Num of cards in deck before smithy played: %d"
           "\nNum of cards in deck after smithy played: %d\n", deckCount, deckCountAfter);
    
    if (assertTrue(deckCount - 3 == deckCountAfter)) {
        fprintf(fp, "DECK COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "DECK COUNT: TEST FAILED.\n");
    }
    
    // testing whether smithy discarded
    
    if (assertTrue(lastCard != smithy)) {
        fprintf(fp, "DISCARD TEST; LAST CARD NOT SMITHY: TEST PASSED.\n");
    } else {
        fprintf(fp, "DISCARD TEST; LAST CARD STILL SMITHY: TEST FAILED.\n");
    }
    
    fclose(fp);
    return;
}



