/*
Name: Shirley Bunton
Date: 02/07/2017
Assignment: Assignment 3
Course: CS362 Software Engineering II
Description: Gardens Card Test */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

int main(){
    struct gameState G, pre;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int p, r;
    int bonus = 0;
    int pass = 1;

    r = initializeGame(MAX_PLAYERS, k, 1, &G); // initialize a new game
    assert(r == 0);

    memcpy(&pre, &G, sizeof(struct gameState));

    printf ("TESTING gardens card:\n");
    //loop through all players to check for any player specific bugs
    for(p = 0; p < MAX_PLAYERS; p++){
        pre.whoseTurn = p;
        G.whoseTurn = p;
        r = cardEffect(gardens, 0, 0, 0, &G, 0, &bonus);
        assert(r == -1); //gardens is not an action card so should not be able to be played

        //check that the attempt to play gardens does not change the gamestate
        if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
            if(DEBUG)
                printf("TEST FAILED: gardens changed the gameState for player %d\n", p);
            pass = 0;
        }
    }
    if(pass)
        printf("gardens card tests passed!\n");
    else
        printf("gardens tests failed!\n");
    return 0;
}