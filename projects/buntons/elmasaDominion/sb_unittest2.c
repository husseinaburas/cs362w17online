/*
Name: Shirley Bunton
Date: 02/07/2017
Assignment: Assignment 3
Course: CS362 Software Engineering II
Description: Unit Test for updateCoins*/

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
    int i, p, r;
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int cards[MAX_HAND];
    int hand, bonus, card;
    int pass = 1;

    //make a prehand for each type of treasure card
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    r = initializeGame(MAX_PLAYERS, k, 1, &G); // initialize a new game
    assert(r == 0);


    printf ("TESTING updateCoins() This will take a bit, please wait :\n");

    //check different hand sizes don't have a problem
    for(hand = 10; hand < MAX_HAND + 1; hand++){
        //check that switching to a different person doesn't effect the results
        //as in like player 2 specific bugs
        for(p = 0; p < MAX_PLAYERS; p++){
            G.handCount[0] = hand;
            G.handCount[1] = hand;
            G.handCount[2] = hand;
            G.handCount[3] = hand;
            //give all players different coin cards to make sure other players' hands are
            //not influencing the result
            if(p != 0)
                memcpy(G.hand[0], coppers, sizeof(int) * hand);
            if(p > 1)
                memcpy(G.hand[1], silvers, sizeof(int) * hand);
            else if(p != 1)
                memcpy(G.hand[1], coppers, sizeof(int) * hand);
            if(p == 3)
                memcpy(G.hand[2], golds, sizeof(int) * hand);
            else if(p != 2)
                memcpy(G.hand[2], silvers, sizeof(int) * hand);
            if(p != 3)
                memcpy(G.hand[3], golds, sizeof(int) * hand);

            //check that all cards are giving appropriate values
            for(card = 0; card < treasure_map + 1; card++){
                /*check that different bonuses effect the results appropriately
                  assuming a max bonus of 500 because max hand is 500 so pretty sure
                  it is impossible to get 500 bonus coins with these cards*/
                for(bonus = 0; bonus < MAX_HAND; bonus++){

                        G.coins = 0;//clear the coins

                        //set the hand with the current card
                        for (i = 0; i < MAX_HAND; i++)
                        {
                            cards[i] = card;
                        }
                        memcpy(G.hand[p], cards, sizeof(int) * hand);

                        //check that the current card works
                        memcpy(&pre, &G, sizeof(struct gameState));
                        updateCoins(p, &G, bonus);
                        pre.coins = bonus;
                        if(card == copper)
                            pre.coins += hand;
                        else if(card == silver)
                            pre.coins += 2 * hand;
                        else if(card == gold)
                            pre.coins += 3 * hand;
                        if(pre.coins != G.coins){
                            if(DEBUG)
                                printf("TEST FAILED: G.coins is %d and should be %d\n", G.coins, pre.coins);
                            pass = 0;
                        }

                        //check that updateCoins didn't change anything besides gamestate.coins
                        if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
                            if(DEBUG)
                                printf("TEST FAILED: updateCoins changed the gameState by more than just gameState.coins\n");
                            pass = 0;
                        }
                }
            }
        }
    }
    if(pass)
        printf("updateCoins() tests passed!\n");
    else
        printf("updateCoins tests failed!\n");
    return 0;
}