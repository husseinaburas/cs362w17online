//  Author: William Miller - cs362
//  Filename: cardtest4.c
//
//  Tests effect of great hall card (draw 1 cards, discard great hall, reduce player deck by 1, add 1 actions)
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
//          great hall card is discarded
//          player action count increased by 1

#include "cardtest4.h"

#include <stdio.h>
#include <stdlib.h>
#include "cardtest2.h"
#include "testFunctions.h"
#include "dominion.h"
#include "dominion_helpers.h"


void testGreatHall(struct gameState* g) {
    
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
    int handPos = g->handCount[player] - 1;
    int lastCard = g->hand[player][g->handCount[player] - 1];

    FILE* fp;
    fp = fopen("unittestresults.out", "a+");
    
    fprintf(fp, "\n\n** TESTING GREAT HALL: PLAYER %d of %d**\n\n", player + 1, g->numPlayers);

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
    if (assertTrue(lastCard == great_hall)) {
        fprintf(fp, "last card great hall OK...\n");
    } else {
        fprintf(fp, "last card not great hall!\n");
    }
    
    cardEffect(great_hall, choice1, choice2, choice3, g, handPos, &bonus);
    
    // hand, deck and action counts after effect applied recorded
    
    lastCard = g->hand[player][g->handCount[player] - 1];
    handCountAfter = g->handCount[player];
    deckCountAfter = g->deckCount[player];
    actionCountAfter = g->numActions;
    
    fprintf(fp, "Num of cards in hand before great hall played: %d"
           "\nNum of cards in hand after great hall played: %d\n", handCount, handCountAfter);
    
    // testing hand count
    
    if (assertTrue(handCount == handCountAfter)) {
        fprintf(fp, "HAND COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "HAND COUNT: TEST FAILED.\n");
    }
    
    fprintf(fp, "Num of cards in deck before great hall played: %d"
           "\nNum of cards in deck after great hall played: %d\n", deckCount, deckCountAfter);
    
    // testing deck count
    
    if (assertTrue(deckCount - 1 == deckCountAfter)) {
        fprintf(fp, "DECK COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "DECK COUNT: TEST FAILED.\n");
    }
    
    // testing action count
    
    if (assertTrue(actionCount + 1 == actionCountAfter)) {
        fprintf(fp, "ACTION COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "ACTION COUNT: TEST FAILED.\n");
    }
    
    // testing whether great hall discarded
    
    if (assertTrue(lastCard != great_hall)) {
        fprintf(fp, "DISCARD TEST; LAST CARD NOT GREAT HALL: TEST PASSED.\n");
    } else {
        fprintf(fp, "DISCARD TEST; LAST CARD STILL GREAT HALL: TEST FAILED.\n");
    }

    fclose(fp);
    return;
}
