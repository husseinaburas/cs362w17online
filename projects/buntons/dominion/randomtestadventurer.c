/*
Name: Shirley Bunton
Date: 02/19/2017
Assignment: Assignment 4
Course: CS362 Software Engineering II
Description: Random Test for Adventurer card*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

#define DEBUG 1
#define ITER 10000

int main(){
    struct gameState G, pre;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int i, j, p, r, s;
    int bonus = 0;
    int pass = 1;
    int seedUsed = 0;
    int cardPos = 0;
    int num = 0;
    int pos = 0;

    seedUsed = time(NULL);
    srand(seedUsed);

    r = initializeGame(MAX_PLAYERS, k, 1, &G); // initialize a new game
    assert(r == 0);

    printf("TESTING adventurer card with seed %d:\n", seedUsed);

    for(i = 0; i < ITER; i++){

        printf("\nTEST %d:\n", i);

        //pick a player to look at
        G.whoseTurn = rand() % MAX_PLAYERS;

        for(p = 0; p < MAX_PLAYERS; p++){

            //set up the hand for each player and make at most 10 cards adventurer
            //last adventurer added to player whose turn it is is the card being exchanged
            G.handCount[p] = rand() % (MAX_DECK - 1) + 1;
            for(j = 0; j < G.handCount[p]; j++){
                G.hand[p][j] = rand() % (treasure_map + 1);
                if(G.hand[p][j] == copper || G.hand[p][j] == silver
                   || G.hand[p][j] == gold || G.hand[p][j] == adventurer){
                    j--;
                }
            }
            num = rand() % (G.handCount[p] % 10 + 1);
            for(j = 0; j <= num; j++){
                pos = rand() % G.handCount[p];
                G.hand[p][pos] = adventurer;
            }
            if(p == G.whoseTurn)
                cardPos = pos;
            assert(cardPos >= 0);

            //set up the deck for each player and set up at most 10 treasure cards
            if(MAX_DECK - G.handCount[p] > 0){
                G.deckCount[p] = rand() % (MAX_DECK - G.handCount[p]) + 1;
                for(j = 0; j < G.deckCount[p]; j++){
                    G.hand[p][j] = rand() % (treasure_map + 1);
                    if(G.hand[p][j] == copper || G.hand[p][j] == silver
                       || G.hand[p][j] == gold || G.hand[p][j] == adventurer){
                        j--;
                    }
                }
                num = rand() % (G.deckCount[p] % 10 + 1);
                for(j = 0; j < num; j++){
                    pos = rand() % G.deckCount[p];
                    G.deck[p][pos] = rand() % 3 + copper;
                }
            }
            else{
                G.deckCount[p] = 0;
            }

            //set up the discard for each player and place at most 10 treasure cards
            if(MAX_DECK - G.handCount[p] - G.deckCount[p] > 0){
                G.discardCount[p] = rand() % (MAX_DECK - G.handCount[p] - G.deckCount[p]) + 1;
                for(j = 0; j < G.discardCount[p]; j++){
                    G.hand[p][j] = rand() % (treasure_map + 1);
                    if(G.hand[p][j] == copper || G.hand[p][j] == silver
                       || G.hand[p][j] == gold || G.hand[p][j] == adventurer){
                        j--;
                    }
                }
                num = rand() % (G.discardCount[p] % 10 + 1);
                for(j = 0; j < num; j++){
                    pos = rand() % G.discardCount[p];
                    G.discard[p][pos] = rand() % 3 + copper;
                }
            }
            else{
                G.discardCount[p] = 0;
            }

            printf("Player %d has %d, %d, %d cards in their hand, deck, and discard respectively\n",
                   p, G.handCount[p], G.deckCount[p], G.discardCount[p]);
        }

        memcpy(&pre, &G, sizeof(struct gameState));

        r = cardEffect(adventurer, 0, 0, 0, &G, cardPos, &bonus);
        assert(r == 0);

        printf("Testing player %d's adventurer card.\n", G.whoseTurn);

        //check all players
        for(p = 0; p < MAX_PLAYERS; p++){

            printf("Player %d has %d, %d, %d cards in their hand, deck, and discard respectively\n",
                   p, G.handCount[p], G.deckCount[p], G.discardCount[p]);

            if(p == G.whoseTurn){
                //since the discard may be shuffled and unknown number of cards added to it,
                //hard to compare it to pre
                if(G.discard[p][G.discardCount[p] - 1] != adventurer){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's adventurer did not add adventurer to discard\n", p);
                    pass = 0;
                }
                //since the deck is shuffled, I don't know where in the deck the two victory cards are, so I can't
                //tell how many cards either the deck or discard will end up with

                //check that the had has 1 more card (since discards adventurer)
                if(G.handCount[p] != pre.handCount[p] + 1){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's adventurer did not add 2 cards to the hand\n", p);
                    pass = 0;
                }

                //check that no cards have been trashed
                if(G.handCount[p] + G.deckCount[p] + G.discardCount[p] !=
                   pre.handCount[p] + pre.deckCount[p] + pre.discardCount[p]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's adventurer trashed cards\n", p);
                    pass = 0;
                }
            }
            else{//check all other player besides whose turn it is

                //check no change to deck
                if(G.deckCount[p] != pre.deckCount[p]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's adventurer altered the deck of player %d\n", G.whoseTurn, p);
                    pass = 0;
                }
                for(s = 0; s < G.deckCount[p]; s++){
                    if(G.deck[p][s] != pre.deck[p][s]){
                        printf("TEST FAILED: player %d's adventurer altered the deck of player %d\n", G.whoseTurn, p);
                        pass = 0;
                    }
                }

                //check no change to hand
                if(G.handCount[p] != pre.handCount[p]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's adventurer altered the hand of player %d\n", G.whoseTurn, p);
                    pass = 0;
                }
                for(s = 0; s < G.handCount[p]; s++){
                    if(G.hand[p][s] != pre.hand[p][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's adventurer altered the hand of player %d\n", G.whoseTurn, p);
                        pass = 0;
                    }
                }

                //check no change to discard
                if(G.discardCount[p] != pre.discardCount[p]){
                    if(DEBUG)
                        printf("TEST FAILED: player %d's adventurer altered the discard of player %d\n", G.whoseTurn, p);
                    pass = 0;
                }
                for(s = 0; s < G.discardCount[p] - 1; s++){
                    if(G.discard[p][s] != pre.discard[p][s]){
                        if(DEBUG)
                            printf("TEST FAILED: player %d's adventurer altered the discard of player %d\n", G.whoseTurn, p);
                        pass = 0;
                    }
                }
            }
        }
    }
    if(pass)
        printf("adventurer card tests passed!\n");
    else
        printf("adventurer tests failed!\n");
    return 0;
}