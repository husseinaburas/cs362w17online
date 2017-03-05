/* 
 * Name: Thomas Adamcewicz
 * Due Date: 3/5/17
 * Function: playAdventurer(struct gameState *state)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>



int main(int argc, char* argv[]) {

    printf("\n**** playAdventurer() RANDOM TESTING BEGINNING ****\n");
    int j, k;
    srand(time(NULL));
    struct gameState G;
    int seed = argv[1];
    long long tests[4][13];

    for (j = 0; j < 4; j++) {
        for(k = 0; k < 13; k++) {
            tests[j][k] = 0;
        }
    }

	for (j = 0; j < 1000; j++) {
        memset(&G, 23, sizeof(struct gameState));
        int tFlag = 0;
        int i;
 
        int numPlayers = (rand() % 4) + 1;
        while (numPlayers < 2) {
            numPlayers = (rand() % 4) + 1;
        }


        int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
        int z = 0;
        int tempHand[MAX_HAND];
        int cardDrawn;

        int initialSupplyCount[treasure_map + 1];

        //start game
        int initDeckSize[numPlayers];
        int initDiscardSize[numPlayers];
        int initHandSize[numPlayers];

        initializeGame(numPlayers, cards, seed, &G);


        int player = whoseTurn(&G);
        int turns = rand() % 10 + 1;

        while (turns > 0) {

            if (isGameOver(&G)) {
                break;
            }

            int numAdventurers = 0;
            int adventurerPos;
            for (i = 0; i < G.handCount[player]; i++) {
                if (G.hand[player][i] == adventurer) {
                    numAdventurers++;
                    adventurerPos = i;
                }
            }

            if (numAdventurers == 0) {
                G.hand[player][rand() % 5] = adventurer;
                numAdventurers++;
            }

            if (numAdventurers > 0) {
            //G.hand[player][0] = adventurer;
                for (i = 0; i < numPlayers; i++) {
                    initDeckSize[i] = G.deckCount[i];
                    initHandSize[i] = G.handCount[i];
                    initDiscardSize[i] = G.discardCount[i];
                }

        
                int drawntreasure = 0;
                int initHandTreasure = 0;


                //get initial treasure in hand for p1
                for (i = 0; i < G.handCount[player]; i++) {
                    if (G.hand[player][i] == copper) initHandTreasure++;
                    if (G.hand[player][i] == silver) initHandTreasure++;
                    if (G.hand[player][i] == gold) initHandTreasure++;
                }

                int deckTreasure = 0;
                int discardTreasure = 0;
                for (i = 0; i < G.deckCount[player]; i++) {
                    if (G.deck[player][i] == copper) deckTreasure++;
                    if (G.deck[player][i] == silver) deckTreasure++;
                    if (G.deck[player][i] == gold) deckTreasure++;
                }
                for (i = 0; i < G.discardCount[player]; i++) {
                    if (G.discard[player][i] == copper) discardTreasure++;
                    if (G.discard[player][i] == silver) discardTreasure++;
                    if (G.discard[player][i] == gold) discardTreasure++;
                }


                playAdventurer(&G);
        
                //TEST-1: Test playAventurer() after game initialized
                //printf("**CALLING playAdventurer() WITH player AND CHECKING CHANGED VARS**\n");

                if (drawntreasure != 0) {
                    tests[player][0]++;
                }
                    //printf("Check drawntreasure == 0: FAILED\n");

                if (G.discardCount[player] != initDiscardSize[player]){
                    tests[player][1]++;
                }
                    //printf("Check player discardCount != initial discardCount: FAILED\n");

                int currHandTreasure = 0;
                for (i = 0; i < G.handCount[player]; i++) {
                    if (G.hand[player][i] == copper) currHandTreasure++;
                    if (G.hand[player][i] == silver) currHandTreasure++;
                    if (G.hand[player][i] == gold) currHandTreasure++;
                }

                for (i = 0; i < numPlayers; i++) {
                    if (i == player) {

                    } else {
                        if (initDeckSize[i] != G.deckCount[i]) {
                            tFlag = 1;
                            break;
                        }
                    }
                }
                if(tFlag != 0) {
                    tests[player][2]++;
                }
                    //printf("Check nothing in other players deck changed: FAILED\n");
                tFlag = 0;
                for (i = 0; i < numPlayers; i++) {
                    if (i == player) {

                    } else {
                        if (initHandSize[i] != G.handCount[i]) {
                            tFlag = 1;
                            break;
                        }
                    }
                }
                if(tFlag != 0) {
                    tests[player][3]++;
                }
                    //printf("Check nothing in other players hand changed: FAILED\n");
                tFlag = 0;
        //printf("Check nothing in other players discard changed: ");
                for (i = 0; i < numPlayers; i++) {
                    if (i == player) {

                    } else {
                        if (initDiscardSize[i] != G.discardCount[i]) {
                            tFlag = 1;
                            break;
                        }
                    }
                }
                if(tFlag != 0) {
                    tests[player][4]++;
                }
                    //printf("Check nothing in other players discard changed: FAILED\n");
                tFlag = 0;

                int adventurerFound = 0;
                for (i = 0; i < G.handCount[player]; i++) {
                    if (G.hand[player][i] == adventurer) adventurerFound++;
                }
                if(adventurerFound != 0) {
                    tests[player][5]++;
                }
                    //printf("Check adventurer was discarded from player hand: FAILED\n");

                if(G.discard[player][G.discardCount[player] - 1] < 0 ||  G.discard[player][G.discardCount[player] - 1] > treasure_map) {
                    tests[player][6]++;
                }
                    //printf("Check cards in discard hand are in kingdom Cards (due to bug introduced): FAILED\n");


                if (deckTreasure >= 2 || discardTreasure >= 2) {
                    if (initHandTreasure + 2 != currHandTreasure) {
                        tests[player][7]++;
                    }
                        //printf("Check player initial hand treasure + 2 == current hand treasure for player: FAILED\n");
                    if (G.handCount[player] != initHandSize[player] + 1) {
                        tests[player][8]++;
                    }
                        //printf("Check player handCount == initial handCount + 1 (-1 adventurer +2 treasure): FAILED\n");
                } else if ((deckTreasure == 1 && discardTreasure == 0) || (deckTreasure == 0 && discardTreasure == 1)) {
                    if(initHandTreasure + 1 != currHandTreasure) {
                        tests[player][9]++;
                    }
                        //printf("Check player initial hand treasure + 1 == current hand treasure for player: FAILED\n");
                    if (G.handCount[player] != initHandSize[player]) {
                        tests[player][10]++;
                    }
                        //printf("Check player handCount == initial handCount (-1 adventurer +1 treasure): FAILED\n");
                } else if (deckTreasure == 0 && discardTreasure == 0) {
                    if(initHandTreasure != currHandTreasure) {
                        tests[player][11]++;
                    }
                        //printf("Check player initial hand treasure == current hand treasure for player: FAILED\n");
                    if (G.handCount[player] != initHandSize[player] - 1) {
                        tests[player][12]++;
                    }
                        //printf("Check player handCount == initial handCount - 1 (-1 adventurer no treasure): FAILED\n");
                }
            }

            endTurn(&G);
            player = whoseTurn(&G);

            turns--;
        }

    }
    printf("**CALLING playAdventurer() WITH player AND CHECKING CHANGED VARS**\n");
    for (j = 0; j < 4; j++) {
        if (tests[j][0] > 0) {
            printf("TEST-1:\n");
            printf("Check drawntreasure == 0: FAILED %lld times for player %d\n", tests[j][0], j + 1);
        }
        if (tests[j][1] > 0) {
            printf("TEST-2:\n");
            printf("Check player discardCount != initial discardCount: FAILED %lld times for player %d\n", tests[j][1], j + 1);
        }
        if (tests[j][2] > 0) {
            printf("TEST-3:\n");
            printf("Check nothing in other players deck changed: FAILED %lld times for player %d\n", tests[j][2], j + 1);
        }
        if (tests[j][3] > 0) {
            printf("TEST-4:\n");
            printf("Check nothing in other players hand changed: FAILED %lld times for player %d\n", tests[j][3], j + 1);
        }
        if (tests[j][4] > 0) {
            printf("TEST-5:\n");
            printf("Check nothing in other players discard changed: FAILED %lld times for player %d\n", tests[j][4], j + 1);
        }
        if (tests[j][5] > 0) {
            printf("TEST-6:\n");
            printf("Check adventurer was discarded from player hand: FAILED %lld times for player %d\n", tests[j][5], j + 1);
        }
        if (tests[j][6] > 0) {
            printf("TEST-7:\n");
            printf("Check cards in discard hand are in kingdom Cards (due to bug introduced): FAILED %lld times for player %d\n", tests[j][6], j + 1);
        }
        if (tests[j][7] > 0) {
            printf("TEST-8:\n");
            printf("Check player initial hand treasure + 2 == current hand treasure for player: FAILED %lld times for player %d\n", tests[j][7], j + 1);
        }
        if (tests[j][8] > 0) {
            printf("TEST-9:\n");
            printf("Check player handCount == initial handCount + 1 (-1 adventurer +2 treasure): FAILED %lld times for player %d\n", tests[j][8], j + 1);
        }
        if (tests[j][9] > 0) {
            printf("TEST-10:\n");
            printf("Check player initial hand treasure + 1 == current hand treasure for player: FAILED %lld times for player %d\n", tests[j][9], j + 1);
        }
        if (tests[j][10] > 0) {
            printf("TEST-11:\n");
            printf("Check player handCount == initial handCount (-1 adventurer +1 treasure): FAILED %lld times for player %d\n", tests[j][10], j + 1);
        }
        if (tests[j][11] > 0) {
            printf("TEST-12:\n");
            printf("Check player initial hand treasure == current hand treasure for player: FAILED %lld times for player %d\n", tests[j][11], j + 1);
        }
        if (tests[j][12] > 0) {
            printf("TEST-13:\n");
            printf("Check player handCount == initial handCount - 1 (-1 adventurer no treasure): FAILED %lld times for player %d\n", tests[j][12], j + 1);
        }
    }

    printf("\n**** playAdventurer() TESTING COMPLETE ****\n");
    return 0;

}