//
//  randomtestadventurer.c
//  Assignment 4
//
//  Random testing generator for the Smithy card
//


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>

int failNum;
int passNum;
void assert_true(int);


int main(int argc, char* args[]){
    
    
    srand(time(NULL));
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    
    int seed = 500;
    int i, j, n, s;
    
    printf("\nTesting Smithy card\n");
    
    // random test for smithy, 500 runs
    for (int i=0; i<500; i++) {
        
        int cardNum;
        int deckCount, handCount = 0;
        
        initializeGame(2, k, seed, &G);
        
        // Random deck size (500 max, should be higher than 4)
        deckCount = (rand() % 495) + 5;
        // random hand size
        handCount = (rand() % (deckCount +1));
        
        G.handCount[0] = handCount;
        G.deckCount[0] = deckCount - handCount;
        
        // random card contents
        for (int n=0; n<2; n++) {
            for (int j=0; j<G.deckCount[n]; j++) {
                cardNum = rand() % 101;
                // kingdom cards
                if (cardNum < 50) {
                    cardNum = rand() % 10;
                    G.deck[n][j] = k[cardNum];
                }
                // victory cards
                else if (cardNum >= 50 && cardNum < 80) {
                    if (cardNum < 55) {
                        G.deck[n][j] = estate;
                    }
                    else if (cardNum < 65) {
                        G.deck[n][j] = duchy;
                    }
                    else {
                        G.deck[n][j] = province;
                    }
                }
                // coins
                else {
                    if (cardNum < 90) {
                        G.deck[n][j] = copper;
                    }
                    else if (cardNum < 96) {
                        G.deck[n][j] = silver;
                    }
                    else {
                        G.deck[n][j] = gold;
                    }
                }
            }
            for (int s=1; s<G.handCount[n]; s++) {
                cardNum = rand() % 101;
                // kingdom cards
                if (cardNum < 50) {
                    cardNum = rand() % 10;
                    G.hand[n][s] = k[cardNum];
                }
                // victory cards
                else if (cardNum >= 50 && cardNum < 80) {
                    if (cardNum < 55) {
                        G.hand[n][s] = estate;
                    }
                    else if (cardNum < 65) {
                        G.hand[n][s] = duchy;
                    }
                    else {
                        G.hand[n][s] = province;
                    }
                }
                // coins
                else {
                    if (cardNum < 90) {
                        G.hand[n][s] = copper;
                    }
                    else if (cardNum < 96) {
                        G.hand[n][s] = silver;
                    }
                    else {
                        G.hand[n][s] = gold;
                    }
                }
            }
            G.hand[n][0] = smithy;
        }
        cardEffect(smithy, 0, 0, 0, &G, 0, 0);
        
        assert_true(handCount == G.handCount[G.whoseTurn] + 2);
        assert_true(deckCount == G.deckCount[G.whoseTurn] - 3);
        
        
        
    }
    
    printf("Number of tests run: 500\n Passed Tests: %d \n Failed Tests: %d\n", passNum, failNum);
    
    
    return 0;
}



void assert_true(int result) {
    
    if (result != 0) {
        passNum++;
    }
    else {
        failNum++;
    }
    
    return;
}
