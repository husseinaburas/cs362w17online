#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"



void assertTrue(int val){
    if(val) printf("TEST SUCCESSFUL\n");
    else printf("TEST FAILED.\n");
    return;
}

int main(){
    printf("----------------------Begin random test on Smithy----------------------\n");
	
	//initialize game state
	int i, j, player, results, discardPos, num_errors;
	struct gameState game_before, game_after;
	int k[10] = {feast, gardens, mine, remodel, smithy, adventurer, council_room, village, great_hall, baron};
    int bonus = 0;
    int cardPos = -1;
    int pos = -1;
	int seed = rand();
    srand(time(NULL));
	
	printf("Testing that game has been successfully initialized ");
	results = initializeGame(4, k, seed, &game_after); 
    assertTrue(results == 0);

	//begin testing
    for(i = 0, num_errors = 0; i < 1000; i++){       
        game_after.whoseTurn = rand() % 4;
        for(player = 0; player < 4; player++){
            pos = -1;
            game_after.handCount[player] = rand() % 500 + 1;
            for(j = 0; j < game_after.handCount[player]; j++){
                game_after.hand[player][j] = rand() % (treasure_map + 1);
                if(game_after.hand[player][j] == smithy){
                    pos == j;
                }
            }
            if(pos < 0){
                pos = rand() % game_after.handCount[player];
                game_after.hand[player][pos] = smithy;
            }
            if(player == game_after.whoseTurn){
                cardPos = pos;
				printf("testing if player %d successfully played smithy card: ", player);
                assertTrue(cardPos >= 0);
            }
            if(500 - game_after.handCount[player] > 0){
                game_after.deckCount[player] = rand() % (500 - game_after.handCount[player]) + 1;
                for(j = 0; j < game_after.deckCount[player]; j++){
                    game_after.hand[player][j] = rand() % (treasure_map + 1);
                }
            }
            else game_after.deckCount[player] = 0;
            if(500 - game_after.handCount[player] - game_after.deckCount[player] > 0){
                game_after.discardCount[player] = rand() % (500 - game_after.handCount[player] - game_after.deckCount[player]) + 1;
                for(j = 0; j < game_after.discardCount[player]; j++){
                    game_after.hand[player][j] = rand() % (treasure_map + 1);
                }
            }
            else game_after.discardCount[player] = 0;
        }

        memcpy(&game_before, &game_after, sizeof(struct gameState));

        if(cardEffect(smithy, 0, 0, 0, &game_after, cardPos, &bonus) != 0){
			printf("TEST FAILED: player %d did not successfully play smithy card\n", game_after.whoseTurn);
			num_errors++;
		}

       
		printf("testing supply count on estate cards: ");
		if(game_after.supplyCount[estate] == game_before.supplyCount[estate]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of estate cards\n", player);
			num_errors++;
		}
		printf("testing supply count on duchy cards: ");
		if(game_after.supplyCount[duchy] == game_before.supplyCount[duchy]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of duchy cards\n", player);
			num_errors++;
		}
		printf("testing supply count on province cards: ");
		if(game_after.supplyCount[province] == game_before.supplyCount[province]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of province cards\n", player);
			num_errors++;
		}
		
		 printf("\ntesting supply and victory piles.\n");
		printf("testing supply count on curse cards: ");
		if(game_after.supplyCount[curse] == game_before.supplyCount[curse]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of curse cards\n", player);
			num_errors++;
		}
		
		printf("\nTEST FAILURES: \n");
		printf("PLAYER #	VARIABLE		INTENDED VALUE	TEST VALUE\n");
		for(player = 0; player < 4; player++){
            if(player == game_after.whoseTurn){
                if(game_after.deckCount[player] != game_before.deckCount[player] - 3){
                    printf("player %d	deck count		%d				%d\n", player, game_before.deckCount[player] - 3, game_after.deckCount[player]);
					num_errors++;
                }
                for(discardPos = 0; discardPos < game_after.deckCount[player]; discardPos++){
                    if(game_after.deck[player][discardPos] != game_before.deck[player][discardPos]){
						printf("player %d	discard position	%d				%d\n", player, game_before.deck[player][discardPos], game_after.deck[player][discardPos]);
						num_errors++;
                    }
                }
                if(game_after.handCount[player] != game_before.handCount[player] + 2){
                    printf("player %d	hand count		%d				%d\n", player, game_before.handCount[player] + 2, game_after.handCount[player]);
					num_errors++;
                }
                if(game_after.discardCount[player] != game_before.discardCount[player] + 1){
                    printf("player %d	discard count	%d				%d\n", player, game_before.discardCount[player] + 1, game_after.discardCount[player]);
					num_errors++;
                }
                for(discardPos = 0; discardPos < game_before.discardCount[player]; discardPos++){
                    if(game_after.discard[player][discardPos] != game_before.discard[player][discardPos]){
						printf("player %d	discard position	%d				%d\n", player, game_before.discard[player][discardPos], game_after.discard[player][discardPos]);
						num_errors++;
                    }
                }
                if(game_after.discard[player][game_after.discardCount[player] - 1] != smithy){
                    printf("player %d	discard pile	smithy			n/a\n", player);
					num_errors++;
                }
            }
            else{
                if(game_after.deckCount[player] != game_before.deckCount[player]){
                    printf("player %d	deck count		%d				%d\n", player, game_before.deckCount[player], game_after.deckCount[player]);
					num_errors++;
                }
                for(discardPos = 0; discardPos < game_after.deckCount[player]; discardPos++){
                    if(game_after.deck[player][discardPos] != game_before.deck[player][discardPos]){
						printf("player %d	deck position	%d				%d\n", player, game_before.deck[player][discardPos], game_after.deck[player][discardPos]);
						num_errors++;
                    }
                }

                if(game_after.handCount[player] != game_before.handCount[player]){
                    printf("player %d	hand count		%d				%d\n", player, game_before.handCount[player], game_after.handCount[player]);
					num_errors++;
                }
                for(discardPos = 0; discardPos < game_after.handCount[player]; discardPos++){
                    if(game_after.hand[player][discardPos] != game_before.hand[player][discardPos]){
						printf("player %d	hand position	%d				%d\n", player, game_before.hand[player][discardPos], game_after.hand[player][discardPos]);
						num_errors++;
                    }
                }
                if(game_after.discardCount[player] != game_before.discardCount[player]){
                    printf("player %d discard count	%d				%d\n", player, game_before.discardCount[player], game_after.discardCount[player]);
					num_errors++;
                }
                for(discardPos = 0; discardPos < game_after.discardCount[player] - 1; discardPos++){
                    if(game_before.discard[player][discardPos] != game_before.discard[player][discardPos]){
                        printf("player %d	discard position	%d				%d\n", player, game_before.discard[player][discardPos], game_before.discard[player][discardPos]);
						num_errors++;
                    }
                }
            }
        }
    }
	
    printf("\nOut of 1000 random tests, smithy card produced %d errors.\n", num_errors);
	
	printf("--------------------End random testing on Smithy!---------------------------------------\n");
    return 0;
}