/*
Name: Shirley Bunton
Date: 02/07/2017
Assignment: Assignment 3
Course: CS362 Software Engineering II
Description: Unit Test for scoreFor*/

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
    int i, p, r;
    int estates[MAX_DECK];
    int duchies[MAX_DECK];
    int provinces[MAX_DECK];
    int cards[MAX_DECK];
    int cardCount, card;
    int returnScore, score;
    int pass = 1;

    for (i = 0; i < MAX_DECK; i++)
    {
        estates[i] = estate;
        duchies[i] = duchy;
        provinces[i] = province;
    }

    r = initializeGame(MAX_PLAYERS, k, 1, &G); // initialize a new game
    assert(r == 0);

    printf ("TESTING scoreFor():\n");

    //check that switching to a different person doesn't effect the results
    //as in like player 2 specific bugs
    for(p = 0; p < MAX_PLAYERS; p++){
        //check that all cards are giving appropriate values
        for(card = 0; card < treasure_map + 1; card++){
            //set the cards with the current card type
            for (i = 0; i < MAX_DECK; i++)
            {
                cards[i] = card;
            }

            //check different cardCount sizes don't have a problem
            for(cardCount = 10; cardCount < MAX_DECK + 1; cardCount++){



                    /**Check hand**/
                    score = 0;//clear the score

                    G.handCount[0] = cardCount;
                    G.handCount[1] = cardCount;
                    G.handCount[2] = cardCount;
                    G.handCount[3] = cardCount;
                    G.discardCount[0] = 0;
                    G.discardCount[1] = 0;
                    G.discardCount[2] = 0;
                    G.discardCount[3] = 0;
                    G.deckCount[0] = 0;
                    G.deckCount[1] = 0;
                    G.deckCount[2] = 0;
                    G.deckCount[3] = 0;

                    //give all players different coin cards to make sure other players' hands are
                    //not influencing the result
                    if(p != 0)
                        memcpy(G.hand[0], estates, sizeof(int) * cardCount);
                    if(p > 1)
                        memcpy(G.hand[1], duchies, sizeof(int) * cardCount);
                    else if(p != 1)
                        memcpy(G.hand[1], estates, sizeof(int) * cardCount);
                    if(p == 3)
                        memcpy(G.hand[2], provinces, sizeof(int) * cardCount);
                    else if(p != 2)
                        memcpy(G.hand[2], duchies, sizeof(int) * cardCount);
                    if(p != 3)
                        memcpy(G.hand[3], provinces, sizeof(int) * cardCount);


                    memcpy(G.hand[p], cards, sizeof(int) * cardCount);

                    //check that the current card works
                    memcpy(&pre, &G, sizeof(struct gameState));
                    returnScore = scoreFor(p, &G);
                    score = 0;
                    if(card == curse)
                        score -= cardCount;
                    else if(card == estate)
                        score += cardCount;
                    else if(card == duchy)
                        score += 3 * cardCount;
                    else if(card == province)
                        score += 6 * cardCount;
                    else if(card == great_hall)
                        score += cardCount;
                    else if(card == gardens)
                        score += cardCount/10 * cardCount;

                    //check the score is correct
                    if(score != returnScore){
                        if(DEBUG)
                            printf("TEST FAILED: hand scoreFor %d card %ds returned is %d and should be %d\n", cardCount, card, returnScore, score);
                        pass =  0;
                    }
                    //check that getting the score didn't effect the gamestate
                    if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
                        if(DEBUG)
                            printf("TEST FAILED: scoreFor for hand  for %d card %ds changed the gameState\n",cardCount, card);
                        pass = 0;
                    }


                    /**Check discard pile**/
                    score = 0;

                    G.handCount[0] = 0;
                    G.handCount[1] = 0;
                    G.handCount[2] = 0;
                    G.handCount[3] = 0;
                    G.discardCount[0] = cardCount;
                    G.discardCount[1] = cardCount;
                    G.discardCount[2] = cardCount;
                    G.discardCount[3] = cardCount;
                    G.deckCount[0] = 0;
                    G.deckCount[1] = 0;
                    G.deckCount[2] = 0;
                    G.deckCount[3] = 0;

                    //give all players different coin cards to make sure other players' hands are
                    //not influencing the result
                    if(p != 0)
                        memcpy(G.discard[0], estates, sizeof(int) * cardCount);
                    if(p > 1)
                        memcpy(G.discard[1], duchies, sizeof(int) * cardCount);
                    else if(p != 1)
                        memcpy(G.discard[1], estates, sizeof(int) * cardCount);
                    if(p == 3)
                        memcpy(G.discard[2], provinces, sizeof(int) * cardCount);
                    else if(p != 2)
                        memcpy(G.discard[2], duchies, sizeof(int) * cardCount);
                    if(p != 3)
                        memcpy(G.discard[3], provinces, sizeof(int) * cardCount);

                    memcpy(G.discard[p], cards, sizeof(int) * cardCount);

                    //check that the current card works
                    memcpy(&pre, &G, sizeof(struct gameState));
                    returnScore = scoreFor(p, &G);
                    score = 0;
                    if(card == curse)
                        score -= cardCount;
                    else if(card == estate)
                        score += cardCount;
                    else if(card == duchy)
                        score += 3 * cardCount;
                    else if(card == province)
                        score += 6 * cardCount;
                    else if(card == great_hall)
                        score += cardCount;
                    else if(card == gardens)
                        score += 50;

                    //check the score is correct
                    if(score != returnScore){
                        if(DEBUG)
                            printf("TEST FAILED: discard score for %d card %d returned is %d and should be %d\n", G.discardCount[p], card, returnScore, score);
                        pass = 0;
                    }
                    //check that getting the score didn't change the gamestate
                    if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
                        if(DEBUG)
                            printf("TEST FAILED: scoreFor for discard  for %d card %d changed the gameState\n", G.discardCount[p], card);
                        pass = 0;
                    }

                    /**Check deck pile**/
                    score = 0;

                    G.handCount[0] = 0;
                    G.handCount[1] = 0;
                    G.handCount[2] = 0;
                    G.handCount[3] = 0;
                    G.discardCount[0] = 0;
                    G.discardCount[1] = 0;
                    G.discardCount[2] = 0;
                    G.discardCount[3] = 0;
                    G.deckCount[0] = cardCount;
                    G.deckCount[1] = cardCount;
                    G.deckCount[2] = cardCount;
                    G.deckCount[3] = cardCount;

                    //give all players different coin cards to make sure other players' hands are
                    //not influencing the result
                    if(p != 0)
                        memcpy(G.deck[0], estates, sizeof(int) * cardCount);
                    if(p > 1)
                        memcpy(G.deck[1], duchies, sizeof(int) * cardCount);
                    else if(p != 1)
                        memcpy(G.deck[1], estates, sizeof(int) * cardCount);
                    if(p == 3)
                        memcpy(G.deck[2], provinces, sizeof(int) * cardCount);
                    else if(p != 2)
                        memcpy(G.deck[2], duchies, sizeof(int) * cardCount);
                    if(p != 3)
                        memcpy(G.deck[3], provinces, sizeof(int) * cardCount);


                    memcpy(G.deck[p], cards, sizeof(int) * cardCount);

                    //check that the current card works
                    memcpy(&pre, &G, sizeof(struct gameState));
                    returnScore = scoreFor(p, &G);
                    score = 0;
                    if(card == curse)
                        score -= cardCount;
                    else if(card == estate)
                        score += cardCount;
                    else if(card == duchy)
                        score += 3 * cardCount;
                    else if(card == province)
                        score += 6 * cardCount;
                    else if(card == great_hall)
                        score += cardCount;
                    else if(card == gardens)
                        score += 50;

                    //check the score is correct
                    if(score != returnScore){
                        if(DEBUG)
                            printf("TEST FAILED: deck score  for %d card %d returned is %d and should be %d\n", G.deckCount[p], card, returnScore, score);
                        pass = 0;
                    }
                    //check that the scoreFor didn't change the gamestate
                    if(memcmp(&pre, &G, sizeof(struct gameState)) != 0){
                        if(DEBUG)
                            printf("TEST FAILED: scoreFor for deck  for %d card %d changed the gameState\n", G.deckCount[p], card);
                        pass = 0;
                    }
            }
        }
    }
    if(pass)
        printf("scoreFor() tests passed!\n");
    else
        printf("scoreFor tests failed!\n");
    return 0;
}