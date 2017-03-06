/* 
 * Name: Steven Hunt
 * Due Date: 2/19/17
 * Function: playSmithy(int currentPlayer, struct gameState *state, int handPos)
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

    printf("\n**** Random test: playSmithy() ****\n");
    int j, k;
    srand(time(NULL));
    struct gameState G;
    int seed = argv[1];
    long long test[4][7];

    for (j = 0; j < 4; j++) {
        for(k = 0; k < 7; k++) {
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
            //G.hand[player][0] = smithy;
                for (i = 0; i < numPlayers; i++) {
                    initializeDeckSize[i] = G.deckCount[i];
                    initializeHandSize[i] = G.handCount[i];
                    initializeDiscardSize[i] = G.discardCount[i];
                }

                playSmithy(player, &G, smithyPos);

                if (G.discardCount[player] != initializeDiscardSize[player])
                {
                	test[player][0]++;
                }
                if(G.handCount[player] != initializeHandSize[player] + 2){
                	test[player][1]++;
                }
    			if(G.hand[player][G.handCount[player]] != -1) {
    				test[player][2]++;
    			}
    			if(G.deckCount[player] != initializeDeckSize[player] - 3) {
    				test[player][3]++;
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
                	test[player][4]++;
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
                	test[player][5]++;
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
                	test[player][6]++;
                }
                tFlag = 0;
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
            printf("Check player discardCount equals initial discardCount: FAILED %lld times for player %d\n", test[j][0], j + 1);
        }
        if (test[j][1] > 0) {
            printf("Test 2:\n");
            printf("Check player handSize is equals initial hand size of player + 2: FAILED %lld times for player %d\n", test[j][1], j + 1);
        }
        if (test[j][2] > 0) {
            printf("Test 3:\n");
            printf("Check value of player hand at current handCount is equal to -1 (discard): FAILED %lld times for player %d\n", test[j][2], j + 1);
        }
        if (test[j][3] > 0) {
            printf("Test 4:\n");
            printf("Check deckCount is equal to initial deckCount - 3 for player: FAILED %lld times for player %d\n", test[j][3], j + 1);
        }
        if (test[j][4] > 0) {
            printf("Test 5:\n");
            printf("Check nothing in other players deck changed: FAILED %lld times for player %d\n", test[j][4], j + 1);
        }
        if (test[j][5] > 0) {
            printf("Test 6:\n");
            printf("Check nothing in other players hand changed: FAILED %lld times for player %d\n", test[j][5], j + 1);
        }
        if (test[j][6] > 0) {
            printf("Test 7:\n");
            printf("Check nothing in other players discard changed: FAILED %lld times for player %d\n", test[j][6], j + 1);
        }
    }

    printf("\nplaySmithy() testing complete.\n");
    return 0;
}