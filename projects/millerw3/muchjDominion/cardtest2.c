//  Author: William Miller - cs362
//  Filename: cardtest2.c
//
//  Tests effect of adventurer card (draw 2 cards (treasure), discard adventurer, reduce player deck by 2)
//
//  Tests performed:
//      Preconditions:
//          valid game state
//          valid hand count
//          inserted card == adventurer
//
//      Tests:
//          player hand is increased by 1 (net total) (both treasure cards)
//          player deck is is reduced by 2
//          adventurer card is discarded

#include <stdio.h>
#include <stdlib.h>
#include "cardtest2.h"
#include "testFunctions.h"
#include "dominion.h"
#include "dominion_helpers.h"

void testAdventurer(struct gameState* g) {
    
    // hands, game, etc. initialized; deck and hand counts recorded
    
    int player = whoseTurn(g);
    int handCount = g->handCount[player];
    int handCountAfter;
    int deckCountAfter;
    int deckCount = g->deckCount[player];
    int choice1, choice2, choice3, bonus;
    choice1 = choice2 = choice3 = bonus = 0;
    int lastCard = g->hand[player][g->handCount[player] - 1];
    int handPos = g->handCount[player] - 1;
    int secondLastCard;
    
    FILE* fp;
    fp = fopen("unittestresults.out", "a+");
    
    fprintf(fp, "\n\n** TESTING ADVENTURER: PLAYER %d of %d**\n\n", player + 1, g->numPlayers);

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
    if (assertTrue(lastCard == adventurer)) {
        fprintf(fp, "last card adventurer OK...\n");
    } else {
        fprintf(fp, "last card not adventurer!\n");
    }
    cardEffect(adventurer, choice1, choice2, choice3, g, handPos, &bonus);
    
    // hand and deck counts after effect applied recorded, last card type and second to last card type recorded
    
    lastCard = g->hand[player][g->handCount[player] - 1];
    secondLastCard = g->hand[player][g->handCount[player] - 2];
    handCountAfter = g->handCount[player];
    deckCountAfter = g->deckCount[player];
    
    fprintf(fp, "Num of cards in hand before adventurer played: %d"
           "\nNum of cards in hand after adventurer played: %d\n", handCount, handCountAfter);
    
    // testing hand count
    
    if (assertTrue(handCount + 1 == handCountAfter)) {
        fprintf(fp, "HAND COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "HAND COUNT: TEST FAILED.\n");
    }
    
    fprintf(fp, "Num of cards in deck before adventurer played: %d"
           "\nNum of cards in deck after adventurer played: %d\n", deckCount, deckCountAfter);
    
    // testing deck count
    
    if (assertTrue(deckCount - 2 == deckCountAfter)) {
        fprintf(fp, "DECK COUNT: TEST PASSED.\n");
    } else {
        fprintf(fp, "DECK COUNT: TEST FAILED.\n");
    }
    
    // testing presence of treasure cards
    
    if (assertTrue((lastCard == copper || lastCard == silver || lastCard == gold) &&
                   (secondLastCard == copper || secondLastCard == silver || secondLastCard == gold))) {
        fprintf(fp, "CHECKED HAND FOR TREASURE; TEST PASSED.\n");
    } else {
        fprintf(fp, "CHECKED HAND FOR TREASURE; TEST FAILED.\n");
    }
    
    // testing whether last card adventurer
    
    if (assertTrue(lastCard != adventurer)) {
        fprintf(fp, "DISCARD TEST; LAST CARD NOT ADVENTURER: TEST PASSED.\n");
    } else {
        fprintf(fp, "DISCARD TEST; LAST CARD STILL ADVENTURER: TEST FAILED.\n");
    }
    
    fclose(fp);
    return;
}