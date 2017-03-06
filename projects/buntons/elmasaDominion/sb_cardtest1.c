/*
Name: Shirley Bunton
Date: 02/07/2017
Assignment: Assignment 3
Course: CS362 Software Engineering II
Description: Smithy Card Test */


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
    int i, p, r, s;
    int bonus = 0;
    int pass = 1;
    r = initializeGame(2, k, 1, &G); // initialize a new game
    assert(r == 0);


    printf ("TESTING smithy card:\n");
    memcpy(&pre, &G, sizeof(struct gameState)); //copy G into pre as a saved reference of G

    //loop through each player to make sure no player has it's own bugs
    for(p = 0; p < MAX_PLAYERS; p++){
        pre.whoseTurn = p;
        pre.handCount[p] = 1;
        pre.hand[p][0] = smithy;
        memcpy(&G, &pre, sizeof(struct gameState)); //make sure G is the original state

        r = cardEffect(smithy, 0, 0, 0, &G, 0, &bonus);
        assert(r == 0);

        //loop through all the players to make sure the smithy is only effecting player p
        for(i = 0; i < MAX_PLAYERS; i++){
            if(i == p){//test player p specific tests

                //test that 3 cards are taken from the deck and no other changes occurred to it.
                if(G.deckCount[p] != pre.deckCount[p] - 3){
                    if(DEBUG)
                        printf("TEST FAILED: smithy did not take 3 cards from the deck for player %d\n", p);
                    pass = 0;
                }
                for(s = 0; s < G.deckCount[i]; s++){
                    if(G.deck[i][s] != pre.deck[i][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's smithy altered the deck besides taking 3 cards\n", p);
                        pass = 0;
                    }
                }

                //test that the hand now has the three new cards and 1 less smithy card
                if(G.handCount[p] != pre.handCount[p] + 2){
                    if(DEBUG)
                        printf("TEST FAILED: smithy did not add 3 cards from the deck for player %d\n", p);
                    pass = 0;
                }

                //test that the discard has the smithy card and no other changes to it have occurred
                if(G.discardCount[p] != pre.discardCount[p] + 1){
                    if(DEBUG)
                        printf("TEST FAILED: smithy did not discard a card from the hand for player %d\n", p);
                    pass = 0;
                }
                for(s = 0; s < pre.discardCount[i]; s++){
                    if(G.discard[i][s] != pre.discard[i][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's smithy altered the discard of for player %d\n", p, i);
                        pass = 0;
                    }
                }
                if(G.discard[p][G.discardCount[p] - 1] != smithy){
                    if(DEBUG)
                        printf("TEST FAILED: smithy did not discard smithy card from the hand for player %d\n", p);
                    pass = 0;
                }
            }
            else{ //check that nothing happened to the other players
                //check the deck
                if(G.deckCount[i] != pre.deckCount[i]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's smithy altered the deck of player %d\n", p, i);
                    pass = 0;
                }
                for(s = 0; s < G.deckCount[i]; s++){
                    if(G.deck[i][s] != pre.deck[i][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's smithy altered the deck of player %d\n", p, i);
                        pass = 0;
                    }
                }

                //check the hand
                if(G.handCount[i] != pre.handCount[i]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's smithy altered the hand of player %d\n", p, i);
                    pass = 0;
                }
                for(s = 0; s < G.handCount[i]; s++){
                    if(G.hand[i][s] != pre.hand[i][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's smithy altered the hand of player %d\n", p, i);
                        pass = 0;
                    }
                }

                //check the discard
                if(G.discardCount[i] != pre.discardCount[i]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's smithy altered the discard of player %d\n", p, i);
                    pass = 0;
                }
                for(s = 0; s < G.discardCount[i] - 1; s++){
                    if(G.discard[i][s] != pre.discard[i][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's smithy altered the discard of player %d\n", p, i);
                        pass = 0;
                    }
                }
            }
        }
    }
    if(pass)
        printf("smithy card tests passed!\n");
    else
        printf("smithy tests failed!\n");
    return 0;
}