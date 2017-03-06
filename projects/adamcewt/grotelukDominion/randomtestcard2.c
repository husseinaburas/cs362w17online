/* 
 * Name: Thomas Adamcewicz
 * Due Date: 3/5/17
 * Function: cardEffect(great_hall, choice1, choice2, choice3, gameState *state, handPos, *bonus)
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

    printf("\n**** playGreat_hall() RANDOM TESTING BEGINNING ****\n");
    int j, k;
    srand(time(NULL));
    struct gameState G;
    int seed = argv[1];
    long long tests[4][9];
    for (j = 0; j < 4; j++) {
        for(k = 0; k < 9; k++) {
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
        int choice1, choice2, choice3;
        //int *bonus;
        int initialSupplyCount[treasure_map + 1];

        //start game
        int initDeckSize[numPlayers];
        int initDiscardSize[numPlayers];
        int initHandSize[numPlayers];

        initializeGame(numPlayers, cards, seed, &G);


        int player = whoseTurn(&G);
        int turns = rand() % 10 + 1;
        //int turns = 5;

        while (turns > 0) {
            int initActions = G.numActions;

        	if (isGameOver(&G)) {
        		break;
        	}

            int numGHs = 0;
            int gHPos;
            for (i = 0; i < G.handCount[player]; i++) {
                if (G.hand[player][i] == great_hall) {
                    numGHs++;
                    gHPos = i;
                }
            }

            if (numGHs == 0) {
            	gHPos = rand() % 5;
                G.hand[player][gHPos] = great_hall;
                numGHs++;
            }

            if (numGHs > 0) {
            //G.hand[player][0] = adventurer;
                for (i = 0; i < numPlayers; i++) {
                    initDeckSize[i] = G.deckCount[i];
                    initHandSize[i] = G.handCount[i];
                    initDiscardSize[i] = G.discardCount[i];
                }


                //playGreat_hall(player, &G, gHPos);
                cardEffect(great_hall, choice1, choice2, choice3, &G, gHPos, 0);
        
                //TEST-1: Test playGreat_hall() after game initialized
                //printf("**CALLING playGreat_hall() WITH player AND CHECKING CHANGED VARS**\n");

                //printf("Check p1 discardCount > initial discardCount: ");
                if (G.discardCount[player] != initDiscardSize[player]) {
                    tests[player][0]++;
                }
                    //printf("Check player discardCount == initial discardCount: FAILED\n");

                if(G.handCount[player] != initHandSize[player]) {
                    tests[player][1]++;
                }
                    //printf("Check player handSize is == initial hand size of player: FAILED\n");

    			if(G.hand[player][G.handCount[player]] != -1) {
                    tests[player][2]++;
                }
    				//printf("Check value of p1 hand at current handCount is == -1 (discard): FAILED\n");

    			if(G.deckCount[player] != initDeckSize[player] - 1) {
                    tests[player][3]++;
                }
    				//printf("Check deckCount is equal to initial deckCount - 1 for player: FAILED \n");

                if(G.numActions != 2) {
                    tests[player][4]++;
                }
                    //printf("Check numActions == 2 (original action + 1): FAILED\n");

                if (G.numActions <= initActions) {
                    tests[player][5]++;
                }
                    //printf("Check numActions > original num actions: FAILED\n");


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
                    tests[player][6]++;
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
                    tests[player][7]++;
                }
                    //printf("Check nothing in other players hand changed: FAILED\n");
                tFlag = 0;
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
                    tests[player][8]++;
                }
                    //printf("Check nothing in other players discard changed: FAILED\n");
                tFlag = 0;



            }

            endTurn(&G);
            player = whoseTurn(&G);

            turns--;
        }

    }
    printf("**CALLING playGreat_hall() WITH player AND CHECKING CHANGED VARS**\n");

    for (j = 0; j < 4; j++) {
        if (tests[j][0] > 0) {
            printf("TEST-1:\n");
            printf("Check player discardCount == initial discardCount: FAILED %lld times for player %d\n", tests[j][0], j + 1);
        }
        if (tests[j][1] > 0) {
            printf("TEST-2:\n");
            printf("Check player handSize is == initial hand size of player: FAILED %lld times for player %d\n", tests[j][1], j + 1);
        }
        if (tests[j][2] > 0) {
            printf("TEST-3:\n");
            printf("Check value of p1 hand at current handCount is == -1 (discard): FAILED %lld times for player %d\n", tests[j][2], j + 1);
        }
        if (tests[j][3] > 0) {
            printf("TEST-4:\n");
            printf("Check deckCount is equal to initial deckCount - 1 for player: FAILED %lld times for player %d\n", tests[j][3], j + 1);
        }
        if (tests[j][4] > 0) {
            printf("TEST-5:\n");
            printf("Check numActions == 2 (original action + 1): FAILED %lld times for player %d\n", tests[j][4], j + 1);
        }
        if (tests[j][5] > 0) {
            printf("TEST-6:\n");
            printf("Check numActions > original num actions: FAILED %lld times for player %d\n", tests[j][5], j + 1);
        }
        if (tests[j][6] > 0) {
            printf("TEST-7:\n");
            printf("Check nothing in other players deck changed: FAILED %lld times for player %d\n", tests[j][6], j + 1);
        }
        if (tests[j][7] > 0) {
            printf("TEST-8:\n");
            printf("Check nothing in other players hand changed: FAILED %lld times for player %d\n", tests[j][7], j + 1);
        }
        if (tests[j][8] > 0) {
            printf("TEST-9:\n");
            printf("Check nothing in other players discard changed: FAILED %lld times for player %d\n", tests[j][8], j + 1);
        }
    }

    printf("\n**** playGreat_hall() TESTING COMPLETE ****\n");
    return 0;

}