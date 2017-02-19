#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"

int main (int argc, char** argv) {

    srand(time(NULL));
    
    /* we will run a for loop 1000 times to test different random values for the adventurer card */
    int testsCount = 1000, playerLoop, maxHand = 9, maxDeck = 5, expectedHandCount = 0;
    
    /* initialize the game variables */
 	struct gameState game;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, smithy, council_room};

 	/* test name and purpose */
 	printf("-----\nStart of Random Council Room Test:\n-----\n");
 	printf("\nThis test will cover the council room card in Dominion.\n");
    printf("We will pass the council room card to the cardEffect function and assert whether 0 is returned.\n");
    printf("We will also test whether the current player's hand count is 3 after the card is played.\n");
    
    /* we will loop 1000 times with random number of players and game states */
    for (int i = 0; i < testsCount; i++){
        
        /* initialize random number of players */
        int players = rand() % (4 - 1) + 2;
		
        /* start the game */
        initializeGame(players, k, rand(), &game);

        /* get a random player */
        int player = rand() % players;
        game.whoseTurn = player;
        
        /* random integer amounts for bonus, choice1, choice2, choice3 and handPos */
        int bonus = rand() % 50, choice1 = rand() % 50, choice2 = rand() % 50, choice3 = rand() % 50, handPos = rand() % maxHand;
		
		/* initialize game states */
		game.deckCount[player] =	rand() % maxDeck;
		game.discardCount[player] = rand() % maxDeck;
		game.handCount[player] =	rand() % maxHand;
		
        /* copy the game state for future comparison */
        struct gameState copy;
        memcpy(&copy, &game, sizeof(struct gameState));
		
		if(game.deckCount[player] > 0 && game.discardCount[player] > 0 && game.handCount[player] > 0){
			if(game.handCount[player] > game.discardCount[player]){
				expectedHandCount = game.handCount[player] + 3;
			}
			else if(game.discardCount[player] == game.handCount[player]){
				expectedHandCount = game.discardCount[player] + game.handCount[player];
			}else if(game.deckCount[player] == game.handCount[player]){
				expectedHandCount = game.discardCount[player] + game.handCount[player];
			}else{
				expectedHandCount = (game.handCount[player] + game.discardCount[player]) - 1;
			}
		}else if(game.deckCount[player] > 0 && game.discardCount[player] == 0 && game.handCount[player] > 0){
			expectedHandCount = (game.deckCount[player] + game.handCount[player]) - 1;
		}
		else if(game.handCount[player] == 0){
			expectedHandCount = 3;
		}else if(game.discardCount[player] > 0){
			expectedHandCount = (game.handCount[player] + game.discardCount[player]) - 1;
		}

        int effect = cardEffect(council_room, choice1, choice2, choice3, &game, handPos, &bonus);
        
        /* test whether return from cardEffect was 0 */
        if(effect != 0){
            printf("\nTEST FAILED: NON ZERO VALUE RETURNED FROM CARD EFFECT\n");
        }
        
        /* test whether game buys is +1 */
        if(game.numBuys != (copy.numBuys + 1)){
            printf("TEST FAILED: GAME BUYS DID NOT INCREMENT BY 1\n");
        }
        
        /* test whether handcount for current player is correct */
        if(game.handCount[player] != expectedHandCount){
            printf("TEST FAILED: CURRENT HAND COUNT DOES NOT MATCH EXPECTED HAND COUNT\n");
        }
        
        /* test whether each other player draws a card */
        for (playerLoop = 0; playerLoop < players; playerLoop++){
        	if(playerLoop != player){
		        if(game.handCount[playerLoop] != (copy.handCount[playerLoop] + 1)){
		            printf("TEST FAILED: CURRENT HAND COUNT FOR PLAYER DOES NOT MATCH EXPECTED HAND COUNT\n");
		        }
        	}
        }
        
    }

    printf("\n-----\nEnd of Random Council Room Card Test. All Tests Completed.\n-----\n");
}