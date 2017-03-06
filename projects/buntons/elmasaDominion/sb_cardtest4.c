/*
Name: Shirley Bunton
Date: 02/07/2017
Assignment: Assignment 3
Course: CS362 Software Engineering II
Description: Sea Hag Card Test */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG_CARD 0

int main(){
    struct gameState G, pre;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int i, s, p, r;
    int bonus = 0;
    int pass = 1;

    r = initializeGame(MAX_PLAYERS, k, 1, &G); // initialize a new game
    assert(r == 0);

    memcpy(&pre, &G, sizeof(struct gameState));

    printf ("TESTING sea hag card:\n");

    //loop through all players to check for player specific bugs
    for(i = 0; i < MAX_PLAYERS; i++){
        pre.whoseTurn = i;
        memcpy(&G, &pre, sizeof(struct gameState)); //reset G
        cardEffect(sea_hag, 0, 0, 0, &G, 0, &bonus);

        //loop through all players to makes sure player i doesn't effect the rest of the players
        for(p = 0; p < MAX_PLAYERS; p++){
            if(p != i){ //test each player besides the current player
                //test the deck to make sure the only change is the top card is now curse
                if(G.deckCount[i] != pre.deckCount[i]){
                    if(DEBUG_CARD)
                        printf("TEST FAILED: player %d's sea hag altered the deck of player %d\n beyond the top card\n", i, p);
                    pass = 0;
                }
                for(s = 0; s < G.deckCount[i] - 1; s++){
                    if(G.deck[i][s] != pre.deck[i][s]){
                        if(DEBUG_CARD)
                            printf("TEST FAILED: player %d's sea hag altered more than the top card\n of the deck of player %d\n", i, p);
                        pass = 0;
                    }
                }
                if(G.deck[i][G.deckCount[i] - 1] == curse){
                    if(DEBUG_CARD)
                        printf("TEST FAILED: player %d's sea hag didn't change the top card to curse for player %d\n", i, p);
                    pass = 0;
                }


                //test the discard to make sure the only change is that the decks top card was added to the discard pile
                if(G.discardCount[i] == pre.discardCount[i] + 1){
                    if(DEBUG_CARD)
                        printf("TEST FAILED: player %d's sea hag altered the discard of player %d beyond the top card\n", i, p);
                    pass = 0;
                }
                for(s = 0; s < pre.discardCount[i]; s++){
                    if(G.discard[i][s] != pre.discard[i][s]){
                        if(DEBUG_CARD)
                            printf("TEST FAILED: player %d's sea hag altered more than the top card of the discard pile of player %d\n", i, p);
                        pass = 0;
                    }
                }
                if(G.discard[i][G.discardCount[i] - 1] == pre.deck[i][pre.deckCount[i] - 1]){
                    if(DEBUG_CARD)
                        printf("TEST FAILED: player %d's sea hag didn't the right card to the discard pile for player %d\n", i, p);
                    pass = 0;
                }

                //test the hand to make sure no changes have been made
                if(G.handCount[i] != pre.handCount[i]){
                    if(DEBUG_CARD)
                        printf("TEST FAILED: player %d's sea hag altered the hand of player %d\n", i, p);
                    pass = 0;
                }
                for(s = 0; s < pre.handCount[i]; s++){
                    if(G.hand[i][s] != pre.hand[i][s]){
                        if(DEBUG_CARD)
                            printf("TEST FAILED: player %d's sea hag altered the hand of player %d\n", i, p);
                        pass = 0;
                    }
                }
            }
            else{
                //check that the deck is unchanged for player i
                if(G.deckCount[i] != pre.deckCount[i]){
                    if(DEBUG_CARD)
                        printf("TEST FAILED: player %d's sea hag altered the deck of player %d\n", i, p);
                    pass = 0;
                }
                for(s = 0; s < G.deckCount[i]; s++){
                    if(G.deck[i][s] != pre.deck[i][s]){
                        if(DEBUG_CARD)
                            printf("TEST FAILED: player %d's sea hag altered the deck of player %d\n", i, p);
                        pass = 0;
                    }
                }

                //test the discard to make sure the only change is that the sea hag was added
                if(G.discardCount[i] != pre.discardCount[i] + 1){
                    if(DEBUG_CARD)
                        printf("TEST FAILED: player %d's sea hag didn't add exactly 1 card to the discard of player %d\n", i, p);
                    pass = 0;
                }
                for(s = 0; s < pre.discardCount[i]; s++){
                    if(G.discard[i][s] != pre.discard[i][s]){
                        if(DEBUG_CARD)
                            printf("TEST FAILED: player %d's sea hag altered the discard of player %d\n", i, p);
                        pass = 0;
                    }
                }
                if(G.discard[i][G.discardCount[i] - 1] != sea_hag){
                    if(DEBUG_CARD)
                        printf("TEST FAILED: player %d's sea hag didn't discard the sea hag card of player %d\n", i, p);
                    pass = 0;
                }

                //test the hand to make sure no changes have been made beside discarding sea hag
                if(G.handCount[i] != pre.handCount[i] - 1){
                    if(DEBUG_CARD)
                        printf("TEST FAILED: player %d's sea hag didn't get rid of the sea hag card in the hand\n", i);
                    pass = 0;
                }
            }
        }
    }
    if(pass)
        printf("sea hag card tests passed!\n");
    else
        printf("sea hag tests failed!\n");
    return 0;
}