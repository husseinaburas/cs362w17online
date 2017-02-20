#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"

int main (int argc, char** argv) {
    
    /* make sure user passes in argument */
    if (argc != 2) {
		printf("USAGE: randomtestadventurer <seed>\n");
		exit(1);
	}

    srand(time(NULL));
    
    /* we will run a for loop 1000 times to test different random values for the adventurer card */
    int testsCount = 1000;
    
    /* initialize the game variables */
 	struct gameState game;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int seed = atoi(argv[1]);
    
 	/* test name and purpose */
 	printf("-----\nStart of Random Adventurer Test:\n-----\n");
 	printf("\nThis test will cover the adventurer card in Dominion.\n");
    printf("We will pass the adventurer card to the cardEffect function and assert whether 0 is returned.\n");
    printf("We will also test whether 2 cards were drawn and that the cards are not treasure cards.\n");
    
    /* we will loop 1000 times with random number of players and game states */
    for (int i = 0; i < testsCount; i++){
        
        /* initialize random number of players */
        int players = rand() % (4 - 1) + 2;

        /* start the game */
        int result = initializeGame(players, k, seed, &game);

        /* test whether game initialized correctly */
        if(result != 0){
            printf("TEST FAILED: NON ZERO VALUE RETURNED FROM INITIALIZE GAME\n");
        }

        /* get a random player */
        int player = rand() % players;
        game.whoseTurn = player;
        
        
        /* test whether random player selected is current player */
        if(player != game.whoseTurn){
            printf("TEST FAILED: RANDOM PLAYER SELECTED IS NOT CURRENT PLAYER\n");
        }
        
        /* random integer amounts for bonus, choice1, choice2, choice3 and handPos */
        int bonus = rand() % 50, choice1 = rand() % 50, choice2 = rand() % 50, choice3 = rand() % 50, handPos = rand() % 9;
        
        
        /* initialize game states */
		game.deckCount[player] =	    rand() % 5;
		game.discardCount[player] =     rand() % 5;
		game.handCount[player] =	    rand() % 9;
        game.hand[player][handPos] =    adventurer;
        
        /* copy the game state for future comparison */
        struct gameState copy;
        memcpy(&copy, &game, sizeof(struct gameState));

        int effect = playCard(handPos, choice1, choice2, choice3, &game);
        int expectedHandCount = copy.handCount[player] + 2;
        
        /* test whether return from cardEffect was 0 */
        if(effect != 0){
            printf("TEST FAILED: NON ZERO VALUE RETURNED FROM CARD EFFECT\n");
        }
        
        /* compare handCounts */
        if(game.handCount[player] != copy.handCount[player] + 2){
            printf("TEST FAILED: PLAYER %d DRAWS %d CARDS. EXPECTED %d \n", player, game.handCount[player], expectedHandCount);
        }
        
        /* get the last card drawn */
        int cardDrawn1 = game.hand[player][game.handCount[player] - 1];
        
        /* make sure the last card drawn is not a treasure card */
        if(cardDrawn1 != copper && cardDrawn1 != silver && cardDrawn1 != gold){
            printf("TEST FAILED: PLAYER %d's DREW A TREASURE CARD.\n", player);
        }
        
        /* get the first card drawn */
        int cardDrawn2 = game.hand[player][game.handCount[player] - 2];
        
        /* make sure the first card drawn is also not a treasure card */
        if(cardDrawn2 != copper && cardDrawn2 != silver && cardDrawn2 != gold){
            printf("TEST FAILED: PLAYER %d's DREW A TREASURE CARD.\n", player);
        }
    }

    printf("\n-----\nEnd of Adventurer Card Test. All Tests Completed.\n-----\n");
}