/*
Name: Shirley Bunton
Date: 02/07/2017
Assignment: Assignment 3
Course: CS362 Software Engineering II
Description: Adventurer Card Test */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

int main(){
    struct gameState G, pre, test;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int i, p, r, v, s;
    int precards[MAX_DECK];
    int bonus = 0;
    int cardCount;
    int pass = 1;

    r = initializeGame(MAX_PLAYERS, k, 1, &G); // initialize a new game
    assert(r == 0);

    for(i = 0; i < MAX_DECK; i++){
        precards[i] = estate;
    }

    printf ("TESTING adventurer card:\n");
    //set deck with 2 treasure at front
    //set deck with 2 treasure at back
    //set empty deck
    //check all players
    for(i = 0; i < MAX_PLAYERS; i++){
        G.whoseTurn = i;
        //check different cardCount sizes don't have a problem
        for(cardCount = 10; cardCount < MAX_DECK + 1; cardCount++){

            //set up the initial game for each player so that everyone has 1 adventurer
            //, and the rest are estates in the deck
            for(p = 0; p < MAX_PLAYERS; p++){
                G.handCount[p] = 1;
                G.hand[p][0] = adventurer;
                G.discardCount[p] = 0;
                G.deckCount[p] = cardCount - 1;
                memcpy(G.deck[p], precards, sizeof(int) * (cardCount - 1));
            }

            memcpy(&pre, &G, sizeof(struct gameState));

            //loop through each possible treasure card
            for(v = copper; v <= gold; v++){

                //set up the first scenario
                memcpy(&G, &pre, sizeof(struct gameState));
                G.deck[i][G.deckCount[i] - 1] = v;
                G.deck[i][G.deckCount[i] - 2] = v;
                memcpy(&test, &G, sizeof(struct gameState));

                r = cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus);
                assert(r == 0);

                //loop through all player to make sure nothing happens exect to player i
                for(p = 0; p < MAX_PLAYERS; p++){
                    if(p == i){

                        //check that the deck only lacking the first two cards
                        if(G.deckCount[i] != test.deckCount[i] - 2){
                            if(DEBUG)
                                printf("A TEST FAILED: adventurer did not take exactly the top 2 cards from the deck which were %d cards for player %d\n", v, i);
                            pass = 0;
                        }
                        for(s = 0; s < G.deckCount[i]; s++){
                            if(G.deck[i][s] != pre.deck[i][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the deck besides taking the top two treasure cards\n", p);
                                pass = 0;
                            }
                        }

                        //check that the discard only has the adventurer card
                        if(G.discardCount[i] != test.discardCount[i] + 1){
                            if(DEBUG)
                                printf("A TEST FAILED: adventurer did not discard a card from the hand for player %d\n", i);
                            pass = 0;
                        }
                        for(s = 0; s < test.discardCount[i]; s++){
                            if(G.discard[i][s] != test.discard[i][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the discard when only 2 cards were drawn\n", i);
                                pass = 0;
                            }
                        }
                        if(G.discard[i][G.discardCount[i] - 1] != adventurer){
                            if(DEBUG)
                                printf("A TEST FAILED: adventurer did not discard adventurer card from the hand for player %d\n", i);
                            pass = 0;
                        }

                        //check that the hand has 1 more card (2 treasures - 1 adventurer)
                        if(G.handCount[i] != test.handCount[i] + 1){
                            if(DEBUG)
                                printf("A TEST FAILED: adventurer did not add 2 cards which were %d from the deck for player %d\n", v, i);
                            pass = 0;
                        }
                    }
                    else{ //check other players
                        //check nothing happened to the deck
                        if(G.deckCount[p] != pre.deckCount[p]){
                            if(DEBUG)
                                printf("A TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.deckCount[p]; s++){
                            if(G.deck[p][s] != pre.deck[p][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                                pass = 0;
                            }
                        }

                        //check nothing happened to the hand
                        if(G.handCount[p] != pre.handCount[p]){
                            if(DEBUG)
                                printf("A TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.handCount[p]; s++){
                            if(G.hand[p][s] != pre.hand[p][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                                pass = 0;
                            }
                        }

                        //check nothing happened to the discard pile
                        if(G.discardCount[p] != pre.discardCount[p]){
                            if(DEBUG)
                                printf("A TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.discardCount[p] - 1; s++){
                            if(G.discard[p][s] != pre.discard[p][s]){
                                if(DEBUG)
                                    printf("A TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                                pass = 0;
                            }
                        }
                    }
                }

                //set up second scenario (2 treasure at the end of deck)
                memcpy(&G, &pre, sizeof(struct gameState));
                G.deck[i][0] = v;
                G.deck[i][1] = v;
                memcpy(&test, &G, sizeof(struct gameState));

                r = cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus);
                assert(r == 0);

                //loop through all players to make sure nothing happened it wasn't supposed to
                for(p = 0; p < MAX_PLAYERS; p++){
                    if(p == i){
                        //check that the deck was emptied
                        if(G.deckCount[i] != 0){
                            if(DEBUG)
                                printf("B TEST FAILED: adventurer did not take all the cards from the deck for player %d\n", i);
                            pass = 0;
                        }

                        //check that the discard pile now has all but two of the draw pile as well as the adventurer card
                        if(G.discardCount[i] != test.discardCount[i] + test.deckCount[i] - 1){
                            if(DEBUG)
                                printf("B TEST FAILED: adventurer did not discard the right number of cards from the hand and deck for player %d\n", i);
                            pass = 0;
                        }
                        for(s = 0; s < test.discardCount[i]; s++){
                            if(G.discard[i][s] != test.discard[i][s]){
                                if(DEBUG)
                                    printf("B TEST FAILED: player %d's adventurer altered the discard when all cards were drawn\n", i);
                                pass = 0;
                            }
                        }
                        if(G.discard[i][G.discardCount[i] - 1] != adventurer){
                            if(DEBUG)
                                printf("B TEST FAILED: adventurer did not discard adventurer card from the hand for player %d\n", i);
                            pass = 0;
                        }

                        //check that the hand has 1 more card
                        if(G.handCount[i] != test.handCount[i] + 1){
                            if(DEBUG)
                                printf("B TEST FAILED: adventurer did not add 2 cards which were %d from the deck for player %d\n", v, i);
                            pass = 0;
                        }

                    }
                    else{
                        //check for no changes in the deck
                        if(G.deckCount[p] != pre.deckCount[p]){
                            if(DEBUG)
                                printf("B TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.deckCount[p]; s++){
                            if(G.deck[p][s] != pre.deck[p][s]){
                                if(DEBUG)
                                    printf("B TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                                pass = 0;
                            }
                        }

                        //check for no changes in the hand
                        if(G.handCount[p] != pre.handCount[p]){
                            if(DEBUG)
                                printf("B TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.handCount[p]; s++){
                            if(G.hand[p][s] != pre.hand[p][s]){
                                if(DEBUG)
                                    printf("B TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                                pass = 0;
                            }
                        }

                        //check for no changes in the discard
                        if(G.discardCount[p] != pre.discardCount[p]){
                            if(DEBUG)
                                printf("B TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.discardCount[p] - 1; s++){
                            if(G.discard[p][s] != pre.discard[p][s]){
                                if(DEBUG)
                                    printf("B TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                                pass = 0;
                            }
                        }
                    }
                }

                //set up the third scenario (2 treasure cards in discard)
                memcpy(&G, &pre, sizeof(struct gameState));
                G.deckCount[i] = 0;
                G.discardCount[i] = cardCount - 1;
                memcpy(G.discard[i], precards, sizeof(int) * (cardCount - 1));
                G.discard[i][0] = v;
                G.discard[i][1] = v;
                memcpy(&test, &G, sizeof(struct gameState));

                r = cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus);
                assert(r == 0);

                //loop through all players to make sure only what is meant to happen happens
                for(p = 0; p < MAX_PLAYERS; p++){
                    if(p == i){
                        //since the discard is shuffled, hard to compare the two to test if no cards have been changed
                        //since the deck is shuffled, I don't know where in the deck the two victory cards are, so I can't
                        //tell how many cards either the deck or discard will end up with

                        //check that the had has 1 more card
                        if(G.handCount[i] != test.handCount[i] + 1){
                            if(DEBUG)
                                printf("C TEST FAILED: adventurer did not add 2 cards which were %d from the deck for player %d\n", v, i);
                            pass = 0;
                        }
                    }
                    else{//check all other player besides i
                        //check no change to deck
                        if(G.deckCount[p] != pre.deckCount[p]){
                            if(DEBUG)
                                printf("C TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.deckCount[p]; s++){
                            if(G.deck[p][s] != pre.deck[p][s]){
                                printf("C TEST FAILED: player %d's adventurer altered the deck of player %d\n", i, p);
                                pass = 0;
                            }
                        }

                        //check no change to hand
                        if(G.handCount[p] != pre.handCount[p]){
                            if(DEBUG)
                                printf("C TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.handCount[p]; s++){
                            if(G.hand[p][s] != pre.hand[p][s]){
                                if(DEBUG)
                                    printf("C TEST FAILED: player %d's adventurer altered the hand of player %d\n", i, p);
                                pass = 0;
                            }
                        }

                        //check no change to discard
                        if(G.discardCount[p] != pre.discardCount[p]){
                            if(DEBUG)
                                printf("C TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                            pass = 0;
                        }
                        for(s = 0; s < G.discardCount[p] - 1; s++){
                            if(G.discard[p][s] != pre.discard[p][s]){
                                if(DEBUG)
                                    printf("C TEST FAILED: player %d's adventurer altered the discard of player %d\n", i, p);
                                pass = 0;
                            }
                        }
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