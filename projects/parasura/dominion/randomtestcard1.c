#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "rngs.h"
#include "assert.h"

int main(){
	printf("Begin testing Smithy card ...\n");

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
	int cardPosition = -1;
	int position = -1;
	int seed = rand();
	srand(time(NULL));

	printf("Test init ... ");
	results = initializeGame(4, k, seed, &postState);
	assert(results == 0);

	//begin testing
	for(i = 0, errorCount = 0; i < 1000; i++){
		printf("\nRandom test iteration %d ... \n", i+1);

		postState.whoseTurn = rand() % 4;
		for(player = 0; player < 4; player++){
			position = -1;
			postState.handCount[player] = rand() % 500 + 1;
			for(j = 0; j < postState.handCount[player]; j++){
				postState.hand[player][j] = rand() % (treasure_map + 1);
				if(postState.hand[player][j] == smithy){
					position == j;
				}
			}
			if(position < 0){
				position = rand() % postState.handCount[player];
				postState.hand[player][position] = smithy;
			}
			if(player == postState.whoseTurn){
				cardPosition = position;
				printf("testing whether player %d successfully played smithy card ... ", player);
				assert(cardPosition >= 0);
			}
			if(500 - postState.handCount[player] > 0){
				postState.deckCount[player] = rand() % (500 - postState.handCount[player]) + 1;
				for(j = 0; j < postState.deckCount[player]; j++){
					postState.hand[player][j] = rand() % (treasure_map + 1);
				}
			}
			else postState.deckCount[player] = 0;
			if(500 - postState.handCount[player] - postState.deckCount[player] > 0){
				postState.discardCount[player] = rand() % (500 - postState.handCount[player] - postState.deckCount[player]) + 1;
				for(j = 0; j < postState.discardCount[player]; j++){
					postState.hand[player][j] = rand() % (treasure_map + 1);
				}
			}
			else postState.discardCount[player] = 0;
		}

		memcpy(&preState, &postState, sizeof(struct gameState));

		if(cardEffect(smithy, 0, 0, 0, &postState, cardPosition, &bonus) != 0){
			printf("[FAIL]: player %d did not successfully play smithy card\n", postState.whoseTurn);
			errorCount++;
		}

		printf("\nTest supply and vicotry piles.\n");
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
		printf("Player #	Variable		Intended Value	Test Value\n");
		for(player = 0; player < 4; player++){
			if(player == postState.whoseTurn){
				if(postState.deckCount[player] != preState.deckCount[player] - 3){
					printf("player %d	deck count		%d			%d\n", player, preState.deckCount[player] - 3, postState.deckCount[player]);
					errorCount++;
				}
				for(discardPosition = 0; discardPosition < postState.deckCount[player]; discardPosition++){
					if(postState.deck[player][discardPosition] != preState.deck[player][discardPosition]){
						printf("player %d	discard position	%d			%d\n", player, preState.deck[player][discardPosition], postState.deck[player][discardPosition]);
						errorCount++;
					}
				}
				if(postState.handCount[player] != preState.handCount[player] + 2){
					printf("player %d	hand count		%d			%d\n", player, preState.handCount[player] + 2, postState.handCount[player]);
					errorCount++;
				}
				if(postState.discardCount[player] != preState.discardCount[player] + 1){
					printf("player %d	discard count	%d			%d\n", player, preState.discardCount[player] + 1, postState.discardCount[player]);
					errorCount++;
				}
				for(discardPosition = 0; discardPosition < preState.discardCount[player]; discardPosition++){
					if(postState.discard[player][discardPosition] != preState.discard[player][discardPosition]){
						printf("player %d	discard position	%d			%d\n", player, preState.discard[player][discardPosition], postState.discard[player][discardPosition]);
						errorCount++;
					}
				}
				if(postState.discard[player][postState.discardCount[player] - 1] != smithy){
					printf("player %d	discard pile	smithy		null\n", player);
					errorCount++;
				}
			}
			else{
				if(postState.deckCount[player] != preState.deckCount[player]){
					printf("player %d	deck count		%d			%d\n", player, preState.deckCount[player], postState.deckCount[player]);
					errorCount++;
				}
				for(discardPosition = 0; discardPosition < postState.deckCount[player]; discardPosition++){
					if(postState.deck[player][discardPosition] != preState.deck[player][discardPosition]){
						printf("player %d	deck position	%d			%d\n", player, preState.deck[player][discardPosition], postState.deck[player][discardPosition]);
						errorCount++;
					}
				}

				if(postState.handCount[player] != preState.handCount[player]){
					printf("player %d	hand count		%d			%d\n", player, preState.handCount[player], postState.handCount[player]);
					errorCount++;
				}
				for(discardPosition = 0; discardPosition < postState.handCount[player]; discardPosition++){
					if(postState.hand[player][discardPosition] != preState.hand[player][discardPosition]){
						printf("player %d	hand position	%d			%d\n", player, preState.hand[player][discardPosition], postState.hand[player][discardPosition]);
						errorCount++;
					}
				}
				if(postState.discardCount[player] != preState.discardCount[player]){
					printf("player %d discard count	%d				%d\n", player, preState.discardCount[player], postState.discardCount[player]);
					errorCount++;
				}
				for(discardPosition = 0; discardPosition < postState.discardCount[player] - 1; discardPosition++){
					if(preState.discard[player][discardPosition] != preState.discard[player][discardPosition]){
						printf("player %d	discard position	%d			%d\n", player, preState.discard[player][discardPosition], preState.discard[player][discardPosition]);
						errorCount++;
					}
				}
			}
		}
	}

	printf("\nIn 1000 rounds of random testing, Smithy card produced %d errors.\n", errorCount);
	printf("There can be multiple errors per round.\n");

	printf("End test of Smithy card.\n");
	return 0;
}
