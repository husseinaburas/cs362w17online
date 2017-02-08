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
    struct gameState G, G_copy;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};

    
    unsigned int arbitrary_hand_count_max = MAX_HAND - 3;
    
    for(int l = 0 ; l < 4 ; l++){
        for(int i = 1 ; i < arbitrary_hand_count_max ; i++){
            initializeGame(4, k, 65432, &G);
            G.handCount[0] = arbitrary_hand_count_max;
            G.whoseTurn = l;

            G_copy = G;

            drawCard(0, &G_copy);
            drawCard(0, &G_copy);
            drawCard(0, &G_copy);
            discardCard(i, l, &G_copy, 0);

            playSmithy(&G, i);

            testing_assert(G.handCount[l] == G_copy.handCount[l]);

            for(int j = 0 ; j < arbitrary_hand_count_max ; j++){
                testing_assert((G.hand[l][j] >= curse) && (G.hand[l][j] <= treasure_map));
                testing_assert((G_copy.hand[l][j] >= curse) && (G_copy.hand[l][j] <= treasure_map));
            }

        }
    }
    
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


