/* 
 * Name: Thomas Adamcewicz
 * Due Date: 2/18/17
 * Function: playSmithy(int currentPlayer, struct gameState *state, int handPos)
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

    printf("\n**** playSmithy() RANDOM TESTING BEGINNING ****\n");
    int j, k;
    srand(time(NULL));
    struct gameState G;
    int seed = argv[1];
    long long tests[4][7];

    for (j = 0; j < 4; j++) {
        for(k = 0; k < 7; k++) {
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
        //int turns = 5;

        while (turns > 0) {

        	if (isGameOver(&G)) {
        		break;
        	}

            int numSmithys = 0;
            int smithyPos;
            for (i = 0; i < G.handCount[player]; i++) {
                if (G.hand[player][i] == smithy) {
                    numSmithys++;
                    smithyPos = i;
                }
            }

            if (numSmithys == 0) {
            	smithyPos = rand() % 5;
                G.hand[player][smithyPos] = smithy;
                numSmithys++;
            }

            if (numSmithys > 0) {
            //G.hand[player][0] = adventurer;
                for (i = 0; i < numPlayers; i++) {
                    initDeckSize[i] = G.deckCount[i];
                    initHandSize[i] = G.handCount[i];
                    initDiscardSize[i] = G.discardCount[i];
                }


                playSmithy(player, &G, smithyPos);
        
                //TEST-1: Test playSmithy() after game initialized
                //printf("**CALLING playSmithy() WITH player AND CHECKING CHANGED VARS**\n");

                //printf("Check p1 discardCount > initial discardCount: ");
                if (G.discardCount[player] != initDiscardSize[player])
                {
                	tests[player][0]++;
                }
                    //printf("Check player discardCount == initial discardCount: FAILED\n");

                if(G.handCount[player] != initHandSize[player] + 2){
                	tests[player][1]++;
                }
                    //printf("Check player handSize is == initial hand size of player + 2: FAILED\n");

    			if(G.hand[player][G.handCount[player]] != -1) {
    				tests[player][2]++;
    			}
    				//printf("Check value of p1 hand at current handCount is == -1 (discard): FAILED\n");

    			if(G.deckCount[player] != initDeckSize[player] - 3) {
    				tests[player][3]++;
    			}
    				//printf("Check deckCount is equal to initial deckCount - 3 for player: FAILED \n");


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
                	tests[player][4]++;
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
                	tests[player][5]++;
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
                	tests[player][6]++;
                }
                    //printf("Check nothing in other players discard changed: FAILED\n");
                tFlag = 0;



            }

            endTurn(&G);
            player = whoseTurn(&G);

            turns--;
        }

    }
    printf("**CALLING playSmithy() WITH player AND CHECKING CHANGED VARS**\n");
    for (j = 0; j < 4; j++) {
        if (tests[j][0] > 0) {
            printf("TEST-1:\n");
            printf("Check player discardCount == initial discardCount: FAILED %lld times for player %d\n", tests[j][0], j + 1);
        }
        if (tests[j][1] > 0) {
            printf("TEST-2:\n");
            printf("Check player handSize is == initial hand size of player + 2: FAILED %lld times for player %d\n", tests[j][1], j + 1);
        }
        if (tests[j][2] > 0) {
            printf("TEST-3:\n");
            printf("Check value of player hand at current handCount is == -1 (discard): FAILED %lld times for player %d\n", tests[j][2], j + 1);
        }
        if (tests[j][3] > 0) {
            printf("TEST-4:\n");
            printf("Check deckCount is equal to initial deckCount - 3 for player: FAILED %lld times for player %d\n", tests[j][3], j + 1);
        }
        if (tests[j][4] > 0) {
            printf("TEST-5:\n");
            printf("Check nothing in other players deck changed: FAILED %lld times for player %d\n", tests[j][4], j + 1);
        }
        if (tests[j][5] > 0) {
            printf("TEST-6:\n");
            printf("Check nothing in other players hand changed: FAILED %lld times for player %d\n", tests[j][5], j + 1);
        }
        if (tests[j][6] > 0) {
            printf("TEST-7:\n");
            printf("Check nothing in other players discard changed: FAILED %lld times for player %d\n", tests[j][6], j + 1);
        }
    }

    printf("\n**** playSmithy() TESTING COMPLETE ****\n");
    return 0;

}