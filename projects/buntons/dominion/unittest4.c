/*
Name: Shirley Bunton
Date: 02/07/2017
Assignment: Assignment 3
Course: CS362 Software Engineering II
Description: Unit Test for isGameOver*/

#include "dominion.h"
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
    int last;
    int pass = 1;

    r = initializeGame(2, k, 1, &G); // initialize a new game
    assert(r == 0);

    for(i = 0; i < treasure_map + 1; i++){
        G.supplyCount[i] = -1;
    }

    printf ("TESTING isGameOver():\n");

    //test the 0 provinces is working
    G.supplyCount[province] = 0;
    memcpy(&pre, &G, sizeof(struct gameState));
    if(isGameOver(&G) != 1){
        if(DEBUG)
            printf("TEST FAILED: isGameOver did not return true when no more provinces available\n");
        pass = 0;
    }
    //check for no change in gamestate
    if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
        if(DEBUG)
            printf("TEST FAILED: isGameOver for checking provinces changed the gameState\n");
        pass = 0;
    }

    //Test the first 3 cards having no cards
    G.supplyCount[province] = 1;
    G.supplyCount[0] = 0;
    G.supplyCount[1] = 0;
    G.supplyCount[2] = 0;
    memcpy(&pre, &G, sizeof(struct gameState));
    if(isGameOver(&G) != 1){
        if(DEBUG)
                printf("TEST FAILED: isGameOver did not return true when first 3 \ncard types were empty\n");
        pass = 0;
    }
    if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
        if(DEBUG)
                printf("TEST FAILED: isGameOver for checking first 3 empty piles \nchanged the gameState\n");
        pass = 0;
    }


    //Test all other cards (leaving the first two cards with no cards)
    //allows makes it so that it is easier to tell what is wrong if
    //something goes wrong
    last = province;
    G.supplyCount[2] = -1;

    while(last < treasure_map){

        G.supplyCount[++last] = 0;
        memcpy(&pre, &G, sizeof(struct gameState));
        if(isGameOver(&G) != 1){
            if(DEBUG)
                printf("TEST FAILED: isGameOver did not return true when the %d card + \n2 others were empty\n", last);
            pass = 0;
        }
        if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
            if(DEBUG)
                printf("TEST FAILED: isGameOver for checking the %d card + 2 other empty \npiles changed the gameState\n", last);
            pass = 0;
        }
        G.supplyCount[last] = -1;
    }
    if(pass)
        printf("isGameOver() tests passed!\n");
    else
        printf("isGameOver tests failed!\n");
    return 0;
}