#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rngs.h"
#include <math.h>
#include <time.h>
#include "assert.h"

int main(){
	printf("Begin testing Adventure card ...\n");

	struct gameState preState, postState;
	int k[10] = {adventurer
    , council_room
    , feast
    , gardens
    , mine
    , remodel
    , smithy
    , village
    , baron
    , great_hall};
	int i, j, player, results, discardPosition, errorCount;
	int bonus = 0;
	int cardPos = 0;
	int num = 0;
	int pos = 0;
	int seed = rand();
	srand(time(NULL));

	printf("Test init ... ");
	results = initializeGame(4, k, seed, &postState);
	assert(results == 0);

	for(i = 0, errorCount = 0; i < 1000; i++){
		printf("\nRandom testing iteration %d ...\n", i+1);
		postState.whoseTurn = rand() % 4;
		for(player = 0; player < 4; player++){
			postState.handCount[player] = rand() % (500 - 1) + 1;
			for(j = 0; j < postState.handCount[player]; j++){
				postState.hand[player][j] = rand() % (treasure_map + 1);
				if(postState.hand[player][j] == copper || postState.hand[player][j] == silver
						|| postState.hand[player][j] == gold || postState.hand[player][j] == adventurer){
					j--;
				}
			}
			num = rand() % (postState.handCount[player] % 10 + 1);
			for(j = 0; j <= num; j++){
				pos = rand() % postState.handCount[player];
				postState.hand[player][pos] = adventurer;
			}
			if(player == postState.whoseTurn) cardPos = pos;
			printf("Test whether player%d's card position matches ... ", player);
			assert(cardPos >= 0);

			if(500 - postState.handCount[player] > 0){
				postState.deckCount[player] = rand() % (500 - postState.handCount[player]) + 1;
				for(j = 0; j < postState.deckCount[player]; j++){
					postState.hand[player][j] = rand() % (treasure_map + 1);
					if(postState.hand[player][j] == copper || postState.hand[player][j] == silver
							|| postState.hand[player][j] == gold || postState.hand[player][j] == adventurer){
						j--;
					}
				}
				num = rand() % (postState.deckCount[player] % 10 + 1);
				for(j = 0; j < num; j++){
					pos = rand() % postState.deckCount[player];
					postState.deck[player][pos] = rand() % 3 + copper;
				}
			}
			else postState.deckCount[player] = 0;

			if(500 - postState.handCount[player] - postState.deckCount[player] > 0){
				postState.discardCount[player] = rand() % (500 - postState.handCount[player] - postState.deckCount[player]) + 1;
				for(j = 0; j < postState.discardCount[player]; j++){
					postState.hand[player][j] = rand() % (treasure_map + 1);
					if(postState.hand[player][j] == copper || postState.hand[player][j] == silver
							|| postState.hand[player][j] == gold || postState.hand[player][j] == adventurer){
						j--;
					}
				}
				num = rand() % (postState.discardCount[player] % 10 + 1);
				for(j = 0; j < num; j++){
					pos = rand() % postState.discardCount[player];
					postState.discard[player][pos] = rand() % 3 + copper;
				}
			}
			else postState.discardCount[player] = 0;
		}

		memcpy(&preState, &postState, sizeof(struct gameState));

		if(cardEffect(adventurer, 0, 0, 0, &postState, cardPos, &bonus) != 0){
			printf("[FAIL]: player %d did not successfully play adventurer card\n", postState.whoseTurn);
			errorCount++;
		}

		if(postState.handCount[player] + postState.deckCount[player] + postState.discardCount[player] !=
				preState.handCount[player] + preState.deckCount[player] + preState.discardCount[player]){
			printf("[FAIL]: player %d's adventurer card incorrectly trashed player %d's cards\n", player, player);
			errorCount++;
		}

		printf("\nTest supply and victory piles.\n");
		printf("Test supply count on curse cards ... ");
		if(postState.supplyCount[curse] == preState.supplyCount[curse]) printf("[OK]\n");
		else{
			printf("[FAIL]: player %d's adventurer card incorrectly changed count of curse cards\n", player);
			errorCount++;
		}
		printf("Test supply count on estate cards ... ");
		if(postState.supplyCount[estate] == preState.supplyCount[estate]) printf("[OK]\n");
		else{
			printf("[FAIL]: player %d's adventurer card incorrectly changed count of estate cards\n", player);
			errorCount++;
		}
		printf("Test supply count on duchy cards ... ");
		if(postState.supplyCount[duchy] == preState.supplyCount[duchy]) printf("[OK]\n");
		else{
			printf("[FAIL]: player %d's adventurer card incorrectly changed count of duchy cards\n", player);
			errorCount++;
		}
		printf("Test supply count on province cards ... ");
		if(postState.supplyCount[province] == preState.supplyCount[province]) printf("[OK]\n");
		else{
			printf("[FAIL]: player %d's adventurer card incorrectly changed count of province cards\n", player);
			errorCount++;
		}

		printf("\nTest failures:\n");
		printf("Player #	Variable		   Intended value      Test value\n");
		for(player = 0; player < 4; player++){
			if(player == postState.whoseTurn){
				if(postState.discard[player][postState.discardCount[player] - 1] != adventurer){
					printf("player %d	discard pile	adventurer		null\n", player);
					errorCount++;
				}

				if(postState.handCount[player] != preState.handCount[player] + 1){
					printf("player %d	hand			%d				%d\n", player, preState.handCount[player] + 1, postState.handCount[player]);
					errorCount++;
				}
			}
			else{
				if(postState.deckCount[player] != preState.deckCount[player]){
					printf("player %d	deck count		%d				%d\n", player, preState.deckCount[player], postState.deckCount[player]);
					errorCount++;
				}
				for(discardPosition = 0; discardPosition < postState.deckCount[player]; discardPosition++){
					if(postState.deck[player][discardPosition] != preState.deck[player][discardPosition]){
						printf("player %d	discard position	%d				%d\n", player, preState.deck[player][discardPosition], postState.deck[player][discardPosition]);
						errorCount++;
					}
				}

				if(postState.handCount[player] != preState.handCount[player]){
					printf("player %d	hand count		%d				%d\n", postState.whoseTurn, preState.handCount[player], postState.handCount[player]);
					errorCount++;
				}
				for(discardPosition = 0; discardPosition < postState.handCount[player]; discardPosition++){
					if(postState.hand[player][discardPosition] != preState.hand[player][discardPosition]){
						printf("player %d	hand position	%d				%d\n", player, preState.hand[player][discardPosition], postState.hand[player][discardPosition]);
						errorCount++;
					}
				}

				if(postState.discardCount[player] != preState.discardCount[player]){
					printf("player %d	discard count	%d				%d\n", player, preState.discardCount[player], postState.discardCount[player]);
					errorCount++;
				}
				for(discardPosition = 0; discardPosition < postState.discardCount[player] - 1; discardPosition++){
					if(postState.discard[player][discardPosition] != preState.discard[player][discardPosition]){
						printf("player %d	discard position	%d				%d\n", player, preState.discard[player][discardPosition], postState.discard[player][discardPosition]);
						errorCount++;
					}
				}
			}
		}
	}

	printf("\nOut of 1000 rounds of random testing, adventurer card produced %d errors.\n", errorCount);
	printf("There can be multiple errors per round.\n");

	printf("End test of adventurer card.\n");
	return 0;
}
