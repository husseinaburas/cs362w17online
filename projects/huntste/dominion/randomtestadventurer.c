/* 
 * Name: Steven Hunt
 * Due Date: 2/19/17
 * Function: playAdventurer(int currentPlayer, struct gameState *state, int cardDrawn, int drawntreasure, int z, int temphand[MAX_HAND])
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char* argv[]) {

    printf("\n**** Random test: playAdventurer() ****\n");
    int j, k;
    srand(time(NULL));
    struct gameState G;
    int seed = argv[1];
    long long test[4][13];

    for (j = 0; j < 4; j++) {
        for(k = 0; k < 13; k++) {
            test[j][k] = 0;
        }
    }

	for (j = 0; j < 1000; j++) {
        memset(&G, 23, sizeof(struct gameState));
        int tFlag = 0;
        int i; 
        int numPlayers = (rand() % 7) + 1;
        while (numPlayers < 2) {
            numPlayers = (rand() % 7) + 1;
        }
        int card[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
        int z = 0;
        int tempHand[MAX_HAND];
        int cardDrawn;
        int initialSupplyCount[treasure_map + 1];

        //start game
        int initializeDeckSize[numPlayers];
        int initializeDiscardSize[numPlayers];
        int initializeHandSize[numPlayers];

        initializeGame(numPlayers, card, seed, &G);


        int player = activePlayer(&G);
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
                    initializeDeckSize[i] = G.deckCount[i];
                    initializeHandSize[i] = G.handCount[i];
                    initializeDiscardSize[i] = G.discardCount[i];
                }

				//zero out treasure
                int drawntreasure = 0;
                int initHandTreasure = 0;

                //generate treasure in player one's hand
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

                playAdventurer(player, &G, cardDrawn, drawntreasure, z, tempHand);

                if (drawntreasure != 0) {
                    test[player][0]++;
                }

                if (G.discardCount[player] != initializeDiscardSize[player]){
                    test[player][1]++;
                }

                int currentHandTreasure = 0;
                for (i = 0; i < G.handCount[player]; i++) {
                    if (G.hand[player][i] == copper) currentHandTreasure++;
                    if (G.hand[player][i] == silver) currentHandTreasure++;
                    if (G.hand[player][i] == gold) currentHandTreasure++;
                }

                for (i = 0; i < numPlayers; i++) {
                    if (i == player) {

                    } else {
                        if (initializeDeckSize[i] != G.deckCount[i]) {
                            tFlag = 1;
                            break;
                        }
                    }
                }
                if(tFlag != 0) {
                    test[player][2]++;
                }

                tFlag = 0;
                for (i = 0; i < numPlayers; i++) {
                    if (i == player) {

                    } else {
                        if (initializeHandSize[i] != G.handCount[i]) {
                            tFlag = 1;
                            break;
                        }
                    }
                }
                if(tFlag != 0) {
                    test[player][3]++;
                }

                tFlag = 0;

                for (i = 0; i < numPlayers; i++) {
                    if (i == player) {

                    } else {
                        if (initializeDiscardSize[i] != G.discardCount[i]) {
                            tFlag = 1;
                            break;
                        }
                    }
                }
                if(tFlag != 0) {
                    test[player][4]++;
                }

                tFlag = 0;

                int adventurerFound = 0;
                for (i = 0; i < G.handCount[player]; i++) {
                    if (G.hand[player][i] == adventurer) adventurerFound++;
                }
                if(adventurerFound != 0) {
                    test[player][5]++;
                }

                if(G.discard[player][G.discardCount[player] - 1] < 0 ||  G.discard[player][G.discardCount[player] - 1] > treasure_map) {
                    test[player][6]++;
                }

                if (deckTreasure >= 2 || discardTreasure >= 2) {
                    if (initHandTreasure + 2 != currentHandTreasure) {
                        test[player][7]++;
                    }

                    if (G.handCount[player] != initializeHandSize[player] + 1) {
                        test[player][8]++;
                    }

                } else if ((deckTreasure == 1 && discardTreasure == 0) || (deckTreasure == 0 && discardTreasure == 1)) {
                    if(initHandTreasure + 1 != currentHandTreasure) {
                        test[player][9]++;
                    }

                    if (G.handCount[player] != initializeHandSize[player]) {
                        test[player][10]++;
                    }

                } else if (deckTreasure == 0 && discardTreasure == 0) {
                    if(initHandTreasure != currentHandTreasure) {
                        test[player][11]++;
                    }

                    if (G.handCount[player] != initializeHandSize[player] - 1) {
                        test[player][12]++;
                    }

                }
            }

            endTurn(&G);
            player = activePlayer(&G);

            turns--;
        }
    }
    printf("Altering player and checking...\n");
    for (j = 0; j < 4; j++) {
        if (test[j][0] > 0) {
            printf("Test 1:\n");
            printf("Check drawntreasure == 0: FAILED %lld times for player %d\n", test[j][0], j + 1);
        }
        if (test[j][1] > 0) {
            printf("Test 2:\n");
            printf("Check player discardCount != initial discardCount: FAILED %lld times for player %d\n", test[j][1], j + 1);
        }
        if (test[j][2] > 0) {
            printf("Test 3:\n");
            printf("Check nothing in other players deck changed: FAILED %lld times for player %d\n", test[j][2], j + 1);
        }
        if (test[j][3] > 0) {
            printf("Test 4:\n");
            printf("Check nothing in other players hand changed: FAILED %lld times for player %d\n", test[j][3], j + 1);
        }
        if (test[j][4] > 0) {
            printf("Test 5:\n");
            printf("Check nothing in other players discard changed: FAILED %lld times for player %d\n", test[j][4], j + 1);
        }
        if (test[j][5] > 0) {
            printf("Test 6:\n");
            printf("Check adventurer was discarded from player hand: FAILED %lld times for player %d\n", test[j][5], j + 1);
        }
        if (test[j][6] > 0) {
            printf("Test 7:\n");
            printf("Check card in discard hand are in kingdom Cards (due to bug introduced): FAILED %lld times for player %d\n", test[j][6], j + 1);
        }
        if (test[j][7] > 0) {
            printf("Test 8:\n");
            printf("Check player initial hand treasure + 2 == current hand treasure for player: FAILED %lld times for player %d\n", test[j][7], j + 1);
        }
        if (test[j][8] > 0) {
            printf("Test 9:\n");
            printf("Check player handCount == initial handCount + 1 (-1 adventurer +2 treasure): FAILED %lld times for player %d\n", test[j][8], j + 1);
        }
        if (test[j][9] > 0) {
            printf("Test 10:\n");
            printf("Check player initial hand treasure + 1 == current hand treasure for player: FAILED %lld times for player %d\n", test[j][9], j + 1);
        }
        if (test[j][10] > 0) {
            printf("Test 11:\n");
            printf("Check player handCount == initial handCount (-1 adventurer +1 treasure): FAILED %lld times for player %d\n", test[j][10], j + 1);
        }
        if (test[j][11] > 0) {
            printf("Test 12:\n");
            printf("Check player initial hand treasure == current hand treasure for player: FAILED %lld times for player %d\n", test[j][11], j + 1);
        }
        if (test[j][12] > 0) {
            printf("Test 13:\n");
            printf("Check player handCount == initial handCount - 1 (-1 adventurer no treasure): FAILED %lld times for player %d\n", test[j][12], j + 1);
        }
    }

    printf("\nplayAdventurer() testing complete.\n");
    return 0;
}