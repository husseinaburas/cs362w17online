/*
Name: Shirley Bunton
Date: 02/07/2017
Assignment: Assignment 3
Course: CS362 Software Engineering II
Description: Unit Test for getCost*/

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
    int i, r;
    int pass = 1;
    int costReturned = 0;
    int cardCosts[] = {-1, 0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4,
                       3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4, -1};

    r = initializeGame(2, k, 1, &G);
    assert(r == 0);
    memcpy (&pre, &G, sizeof(struct gameState));

    printf ("TESTING getCost():\n");
    /*check card values of -1 - 27 to make sure they return the right number
      -1 and 27 are nonexistent cards so should return -1
      check that no change to the gamestate occurs with the call*/
    for(i = -1; i < 28; i++){
        costReturned = 0;
        costReturned = getCost(i);

        //check that the right value is returned
        if(costReturned != cardCosts[i + 1]){
            pass = 0;
            if(DEBUG)
                printf("TEST FAILED: getCost returned %d for card %d and should have returned %d\n", costReturned, i, cardCosts[i]);
        }
        //check the function didn't change the gamestate
        if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
            pass = 0;
            if(DEBUG)
                printf("TEST FAILED: getCost changed the gameState\n");
        }
    }

    if(pass)
        printf("getCost() tests passed!\n");
    else
        printf("getCost tests failed!\n");

    return 0;
}