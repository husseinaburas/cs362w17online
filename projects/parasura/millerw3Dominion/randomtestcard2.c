#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main() {
	printf("Begin testing Steward card ... \n");

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
	int player, numDiscard, choice2[4], choice3[4], seed, stewardHandPosition[4], bonus;
	int errorCount = 0;
	srand(time(NULL));

	for (int i = 0; i < 1000; i++) {
		printf("\nRandom test iteration %d ... \n", i+1);
		printf("Randomly generating one of 3 tests\n");
		printf("-  draw 2 cards\n");
		printf("-  gain 2 coins\n");
		printf("-  discard 2 cards ...\n");

    seed = rand();
		initializeGame(4, k, seed, &postState);

    for (int player = 0; player < postState.numPlayers; player++) {
			memset((void *)postState.deck[player], -1, sizeof(int)*500);
			memset((void *)postState.hand[player], -1, sizeof(int)*500);
			memset((void *)postState.discard[player], -1, sizeof(int)*500);

			postState.deckCount[player] = rand() % 500;
			postState.handCount[player] = rand() % 500;
			postState.discardCount[player] = rand() % 500;

			for (int j = 0; j < postState.deckCount[player]; j++)
				postState.deck[player][j] = rand() % treasure_map + 1;
			for (int j = 0; j < postState.handCount[player]; j++)
				postState.hand[player][j] = rand() % treasure_map + 1;
			for (int j = 0; j < postState.discardCount[player]; j++)
				postState.discard[player][j] = rand() % treasure_map + 1;

			choice2[player] = rand() % 500;
			choice3[player] = rand() % 500;
			if (postState.handCount[player] > 10) {
				do {
					stewardHandPosition[player] = rand() % postState.handCount[player] - 1;
				} while (stewardHandPosition[player] == choice2[player] || stewardHandPosition[player] == choice3[player]);
				postState.hand[player][stewardHandPosition[player]] = steward;
			}
			else {
				stewardHandPosition[player] = postState.handCount[player];
				postState.hand[player][postState.handCount[player]] = steward;
				postState.handCount[player]++;
			}
		}
		memcpy(&preState, &postState, sizeof(struct gameState));

		printf("\nTest supply and vicotry piles ... \n");
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
		printf("Test #	Player #	Variable		  Intended Value	   Test Value\n");

		for (int player = 0; player < postState.numPlayers; player++) {
			postState.whoseTurn = player;
			postState.numActions = 1;
			preState.coins = 0;
			for (int j = 0; j < preState.handCount[player]; j++) {
				if (preState.hand[player][j] == copper)
					preState.coins += 1;
				else if (preState.hand[player][j] == silver)
					preState.coins += 2;
				else if (preState.hand[player][j] == gold)
					preState.coins += 3;
			}

			if (i < 1000 / 3) {
				bonus = 0;
				for (int j = preState.deckCount[player]; j >= preState.deckCount[player] - 2; --j) {
					if (preState.deck[player][j] == copper)
						bonus += 1;
					else if (preState.deck[player][j] == silver)
						bonus += 2;
					else if (preState.deck[player][j] == gold)
						bonus += 3;
				}
				playCard(stewardHandPosition[player], 1, choice2[player], choice3[player], &postState);
				if (postState.handCount[player] != preState.handCount[player] + 1){
					printf("draw 2	player %d	hand count		%d				%d\n", player, preState.handCount[player] + 1, postState.handCount[player]);
					errorCount++;
				}
				if (preState.deckCount[player] >= 2) {
					if (postState.discardCount[player] != preState.discardCount[player] + 1){
						printf("draw 2	player %d	discard count	%d				%d\n", player, preState.discardCount[player] + 1, postState.discardCount[player]);
						errorCount++;
					}
				}
				else {
					if (postState.discardCount[player] != 1) {
						printf("draw 2	player %d	discard count 	%d				%d\n", player, 1, postState.discardCount[player]);
						errorCount++;
					}
				}

				if (preState.deckCount[player] >= 2) {
					if (postState.deckCount[player] != preState.deckCount[player] - 2){
						printf("draw 2 	player %d	deck count		%d				%d\n", player, preState.deckCount[player] - 2, postState.deckCount[player]);
						errorCount++;
					}
					for (int j = 0; j < preState.deckCount[player] - 2; j++)
						if (preState.deck[player][j] != postState.deck[player][j]){
							printf("draw 2	player %d	deck[%d]		%d				%d\n", player, j, preState.deck[player][j], postState.deck[player][j]);
							errorCount++;
						}
				}
				else
					if (postState.deckCount[player] != preState.deckCount[player] + preState.discardCount[player] - 2){
						printf("draw 2	player %d	deck count 	%d			%d\n", player, preState.deckCount[player] + preState.discardCount[player] - 2, postState.deckCount[player]);
						errorCount++;
					}
				if (preState.deckCount[player] >= 2) {
					for (int j = 0, flag; j < postState.handCount[player]; j++) {
						flag = 0;
						for (int l = 0; l < preState.handCount[player]; l++) {
							if (postState.hand[player][j] == preState.hand[player][l]) {
								preState.hand[player][l] = -1;
								flag = 1;
								break;
							}
						}
						if (!flag) {
							if (postState.hand[player][j] == preState.deck[player][preState.deckCount[player]-1])
								preState.deck[player][preState.deckCount[player]-1] = -1;
							else if (postState.hand[player][j] == preState.deck[player][preState.deckCount[player]-2])
								preState.deck[player][preState.deckCount[player]-2] = -1;
							else{
								printf("draw 2 	player %d	hand[%d]		null				%d\n", player, j, postState.hand[player][j]);
								errorCount++;
							}
						}
					}
				}

				if (postState.discardCount[player] > preState.discardCount[player]) {
					for (int j = 0; j < preState.discardCount[player]; j++)
						if (preState.discard[player][j] != postState.discard[player][j]){
							printf("draw 2	player %d	discard[%d]		%d				%d\n", player, j, preState.discard[player][j], postState.discard[player][j]);
							errorCount++;
						}
				}
				if (postState.discard[player][postState.discardCount[player] - 1] != steward){
					printf("draw 2	player %d	discard[%d]		%d				%d\n", player, postState.discardCount[player] - 1, steward, postState.discard[player][postState.discardCount[player] -1]);
					errorCount++;
				}
				if (postState.coins != preState.coins + bonus){
					printf("draw 2	player %d	coin count		%d				%d\n", player, preState.coins + bonus, postState.coins);
					errorCount++;
				}
				if (postState.numActions != 0){
					printf("draw 2	player %d	# of actions	%d				%d\n", player, 0, postState.numActions);
					errorCount++;
				}
			}


			else if (i < 2 * 1000 / 3) {
				bonus = 2;
				playCard(stewardHandPosition[player], 2, choice2[player], choice3[player], &postState);

				if (postState.deckCount[player] != preState.deckCount[player]){
					printf("gain 2	player %d	deck count		%d				%d\n", player, preState.deckCount[player], postState.deckCount[player]);
					errorCount++;
				}
				if (postState.handCount[player] != preState.handCount[player] - 1){
					printf("gain 2	player %d	hand count		%d				%d\n", player, preState.handCount[player] - 1, postState.handCount[player]);
					errorCount++;
				}
				if (postState.discardCount[player] != preState.discardCount[player] + 1){
					printf("gain 2	player %d	discard count	%d				%d\n", player, preState.discardCount[player] + 1, postState.discardCount[player]);
					errorCount++;
				}
				for (int j = 0; j < preState.deckCount[player]; j++){
					if (preState.deck[player][j] != postState.deck[player][j]){
						printf("gain 2	player %d	deck[%d]		%d				%d\n", player, j, preState.deck[player][j], postState.deck[player][j]);
						errorCount++;
					}
				}
				for (int j = 0, flag; j < postState.handCount[player]; j++) {
					flag = 0;
					for (int l = 0; l < preState.handCount[player]; l++) {
						if (postState.hand[player][j] == preState.hand[player][l]) {
							preState.hand[player][l] = -1;
							flag = 1;
							break;
						}
					}
					if (!flag){
						printf("gain 2	player %d	hand[%d]		null				%d\n", player, j, postState.hand[player][j]);
						errorCount++;
					}
				}

				for (int j = 0; j < preState.discardCount[player]; j++)
					if (preState.discard[player][j] != postState.discard[player][j]){
						printf("gain 2	player %d	discard[%d]		%d				%d\n", player, j, preState.discard[player][j], postState.discard[player][j]);
						errorCount++;
					}
				if (postState.discard[player][preState.discardCount[player]] != steward){
					printf("gain 2	player %d	discard[%d]		%d				%d\n", player, preState.discardCount[player], steward, postState.discard[player][preState.discardCount[player]]);
					errorCount++;
				}
				if (postState.coins != preState.coins + bonus){
					printf("gain 2	player %d	coin count		%d				%d\n", player, preState.coins + bonus, postState.coins);
					errorCount++;
				}
				if (postState.numActions != 0){
					printf("gain 2	player %d	# of actions	%d				%d\n", player, 0, postState.numActions);
					errorCount++;
				}
			}


			else {
				numDiscard = 1;

				if (choice2[player] < preState.handCount[player]) numDiscard++;
				if (choice3[player] < preState.handCount[player]) numDiscard++;

				if (choice2[player] < preState.handCount[player]) {
					if (preState.hand[player][choice2[player]] == copper)
						preState.coins -= 1;
					else if (preState.hand[player][choice2[player]] == silver)
						preState.coins -= 2;
					else if (preState.hand[player][choice2[player]] == gold)
						preState.coins -= 3;
				}
				if (choice3[player] < preState.handCount[player]) {
					if (preState.hand[player][choice3[player]] == copper)
						preState.coins -= 1;
					else if (preState.hand[player][choice3[player]] == silver)
						preState.coins -= 2;
					else if (preState.hand[player][choice3[player]] == gold)
						preState.coins -= 3;
				}

				playCard(stewardHandPosition[player], 3, choice2[player], choice3[player], &postState);
				if (postState.deckCount[player] != preState.deckCount[player]){
					printf("toss 2	player %d	deck count		%d				%d\n", player, preState.deckCount[player], postState.deckCount[player]);
					errorCount++;
				}
				if (postState.handCount[player] != preState.handCount[player] - numDiscard){
					printf("toss 2	player %d	hand count		%d				%d\n", player, preState.handCount[player] - numDiscard, postState.handCount[player]);
					errorCount++;
				}
				if (postState.discardCount[player] != preState.discardCount[player] + 1){
					printf("toss 2	player %d	discard count	%d				%d\n", player, preState.discardCount[player] + 1, postState.discardCount[player]);
					errorCount++;
				}
				for (int j = 0; j < preState.deckCount[player]; j++) {
					if (preState.deck[player][j] != postState.deck[player][j]){
						printf("toss 2	player %d	deck[%d]		%d				%d\n", player, j, preState.deck[player][j], postState.deck[player][j]);
						errorCount++;
					}
				}
				for (int j = 0; j < preState.discardCount[player]; j++) {
					if (preState.discard[player][j] != postState.discard[player][j]){
						printf("toss 2	player %d	discard[%d]		%d				%d\n", player, j, preState.discard[player][j], postState.discard[player][j]);
						errorCount++;
					}
				}
				if (postState.discard[player][postState.discardCount[player] - 1] != steward){
					printf("toss 2	player %d	discard[%d]		%d				%d\n", player, postState.discardCount[player] - 1, steward, postState.discard[player][preState.discardCount[player] - 1]);
					errorCount++;
				}
				if (postState.coins != preState.coins ) {
					printf("toss 2	player %d	coin count		%d				%d\n", player, preState.coins , postState.coins);
					errorCount++;
				}
				if (postState.numActions != 0){
					printf("toss 2	player %d	# of actions	%d				%d\n", player, 0, postState.numActions);
					errorCount++;
				}
				for (int j = 0, flag; j < postState.handCount[player]; j++) {
					flag = 0;
					for (int l = 0; l < preState.handCount[player]; l++) {
						if (postState.hand[player][j] == preState.hand[player][l]) {
							preState.hand[player][l] = -1;
							flag = 1;
							break;
						}
					}
					if (!flag){
						printf("toss 2	player %d	hand[%d]		null				%d\n", player, j, postState.hand[player][j]);
						errorCount++;
					}
				}
			}
		}
	}

	printf("\nOut of 1000 rounds of random testing, Steward card produced %d errors.\n", errorCount);
	printf("There can be multiple errors per round.\n");

	printf("End test of Steward card.\n");
	return 0;
}
