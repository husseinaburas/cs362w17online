/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   unittest1.c
 * Author: corwinperren
 *
 * Created on February 1, 2017, 9:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testing_assert(int expression);

int main(int argc, char** argv) {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};

    initializeGame(4, k, 65432, &G);
    
    unsigned int arbitrary_hand_count_max = MAX_HAND - 10;
    
    printf("Hand: %d\n", G.handCount[0]);
    drawCard(0, &G);
    printf("Hand: %d\n", G.handCount[0]);
    G.numActions++;
    discardCard(0, 0, &G, 0);
    printf("Hand: %d\n\n", G.handCount[0]);
    
    printf("Hand: %d\n", G.handCount[0]);
    playGreat_Hall(&G, 0);
    printf("Hand: %d\n\n", G.handCount[0]);
    
    return (EXIT_SUCCESS);
}

int testing_assert(int expression) {
    if (expression) {
        printf("TEST SUCCEEDED!\n");
        return 1;
    } else {
        printf("TEST FAILED!\n");
        return 0;
    }
}

