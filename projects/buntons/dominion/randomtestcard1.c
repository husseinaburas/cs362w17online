/*
Name: Shirley Bunton
Date: 02/19/2017
Assignment: Assignment 4
Course: CS362 Software Engineering II
Description: Random Test for Smithy card*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

#define DEBUG 0
#define ITER 10000

int main(){
    struct gameState G, pre;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int i, j, p, r, s;
    int bonus = 0;
    int pass = 1;
    int seedUsed = 0;
    int cardPos = -1;
    int num = 0;
    int pos = -1;

    seedUsed = time(NULL);
    srand(seedUsed);

    r = initializeGame(MAX_PLAYERS, k, 1, &G); // initialize a new game
    assert(r == 0);

    printf("TESTING smithy card with seed %d:\n", seedUsed);

    for(i = 0; i < ITER; i++){

        printf("\nTEST %d:\n", i);

        //pick a player to look at
        G.whoseTurn = rand() % MAX_PLAYERS;

        //set up each players entire game state
        for(p = 0; p < MAX_PLAYERS; p++){

            pos = -1;

            //set up the hand for each player
            //last smithy card added is the one being discarded
            //if no smithy card is added then a random card is changed to smithy
            G.handCount[p] = rand() % MAX_DECK + 1;
            for(j = 0; j < G.handCount[p]; j++){
                G.hand[p][j] = rand() % (treasure_map + 1);
                if(G.hand[p][j] == smithy){
                    pos == j;
                }
            }
            if(pos < 0){
                pos = rand() % G.handCount[p];
                G.hand[p][pos] = smithy;
            }
            if(p == G.whoseTurn){
                cardPos = pos;
                assert(cardPos >= 0);
            }

            //set up the deck for each player
            if(MAX_DECK - G.handCount[p] > 0){
                G.deckCount[p] = rand() % (MAX_DECK - G.handCount[p]) + 1;
                for(j = 0; j < G.deckCount[p]; j++){
                    G.hand[p][j] = rand() % (treasure_map + 1);
                }
            }
            else{
                G.deckCount[p] = 0;
            }

            //set up the discard for each player
            if(MAX_DECK - G.handCount[p] - G.deckCount[p] > 0){
                G.discardCount[p] = rand() % (MAX_DECK - G.handCount[p] - G.deckCount[p]) + 1;
                for(j = 0; j < G.discardCount[p]; j++){
                    G.hand[p][j] = rand() % (treasure_map + 1);
                }
            }
            else{
                G.discardCount[p] = 0;
            }


            printf("Player %d has %d, %d, %d cards in their hand, deck, and discard respectively\n",
                   p, G.handCount[p], G.deckCount[p], G.discardCount[p]);
        }

        memcpy(&pre, &G, sizeof(struct gameState));

        printf("Testing player %d's smithy card at position %d.\n", G.whoseTurn, cardPos);

        r = cardEffect(smithy, 0, 0, 0, &G, cardPos, &bonus);
        assert(r == 0);

        //check all players
        for(p = 0; p < MAX_PLAYERS; p++){

            printf("Player %d has %d, %d, %d cards in their hand, deck, and discard respectively\n",
                   p, G.handCount[p], G.deckCount[p], G.discardCount[p]);

            if(p == G.whoseTurn){//test player p specific tests

                //test that 3 cards are taken from the deck and no other changes occurred to it.
                if(G.deckCount[p] != pre.deckCount[p] - 3){
                    if(DEBUG)
                        printf("TEST FAILED: smithy did not take 3 cards from the deck for player %d\n", p);
                    pass = 0;
                }
                for(s = 0; s < G.deckCount[p]; s++){
                    if(G.deck[p][s] != pre.deck[p][s]){
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
                for(s = 0; s < pre.discardCount[p]; s++){
                    if(G.discard[p][s] != pre.discard[p][s]){
                        if(DEBUG)
                            printf("TEST FAILED: smithy altered the discard of for player %d\n", p);
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
                if(G.deckCount[p] != pre.deckCount[p]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's smithy altered the deck of player %d\n", G.whoseTurn, p);
                    pass = 0;
                }
                for(s = 0; s < G.deckCount[p]; s++){
                    if(G.deck[p][s] != pre.deck[p][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's smithy altered the deck of player %d\n", G.whoseTurn, p);
                        pass = 0;
                    }
                }

                //check the hand
                if(G.handCount[p] != pre.handCount[p]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's smithy altered the hand of player %d\n", G.whoseTurn, p);
                    pass = 0;
                }
                for(s = 0; s < G.handCount[p]; s++){
                    if(G.hand[p][s] != pre.hand[p][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's smithy altered the hand of player %d\n", G.whoseTurn, p);
                        pass = 0;
                    }
                }

                //check the discard
                if(G.discardCount[p] != pre.discardCount[p]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's smithy altered the discard of player %d\n", G.whoseTurn, p);
                    pass = 0;
                }
                for(s = 0; s < G.discardCount[p] - 1; s++){
                    if(G.discard[p][s] != pre.discard[p][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's smithy altered the discard of player %d\n", G.whoseTurn, p);
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