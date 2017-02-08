#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main() {
	printf("******begin random testing on steward card******\n");
	
	struct gameState Gbefore, Gafter;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int player, numDiscard, choice2[4], choice3[4], seed, stewardHandPos[4], bonus;
	int errorCount = 0;
	srand(time(NULL));

	for (int i = 0; i < 1000; i++) {
		printf("\nrandom testing round #%d:\n", i+1);
		printf("randomly generating one of the following 3 tests:\n");
		printf("TEST 1: draw 2 cards\n");
		printf("TEST 2: gain 2 coins\n");
		printf("TEST 3: discard 2 cards\n");
		seed = rand();		
		initializeGame(4, k, seed, &Gafter);	
		for (int player = 0; player < Gafter.numPlayers; player++) {
			memset((void *)Gafter.deck[player], -1, sizeof(int)*500);
			memset((void *)Gafter.hand[player], -1, sizeof(int)*500);
			memset((void *)Gafter.discard[player], -1, sizeof(int)*500);

			Gafter.deckCount[player] = rand() % 500;
			Gafter.handCount[player] = rand() % 500;
			Gafter.discardCount[player] = rand() % 500;

			for (int j = 0; j < Gafter.deckCount[player]; j++)
				Gafter.deck[player][j] = rand() % treasure_map + 1;
			for (int j = 0; j < Gafter.handCount[player]; j++)
				Gafter.hand[player][j] = rand() % treasure_map + 1;
			for (int j = 0; j < Gafter.discardCount[player]; j++)
				Gafter.discard[player][j] = rand() % treasure_map + 1;

			choice2[player] = rand() % 500;
			choice3[player] = rand() % 500;
			if (Gafter.handCount[player] > 10) {
				do {
					stewardHandPos[player] = rand() % Gafter.handCount[player] - 1;
				} while (stewardHandPos[player] == choice2[player] || stewardHandPos[player] == choice3[player]);
				Gafter.hand[player][stewardHandPos[player]] = steward;
			}
			else {
				stewardHandPos[player] = Gafter.handCount[player];
				Gafter.hand[player][Gafter.handCount[player]] = steward;
				Gafter.handCount[player]++;
			}
		}
		memcpy(&Gbefore, &Gafter, sizeof(struct gameState));
		
		printf("\ntesting supply and vicotry piles.\n");
		printf("testing supply count on curse cards: ");
		if(Gafter.supplyCount[curse] == Gbefore.supplyCount[curse]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of curse cards\n", player);
			errorCount++;
		}
		printf("testing supply count on estate cards: ");
		if(Gafter.supplyCount[estate] == Gbefore.supplyCount[estate]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of estate cards\n", player);
			errorCount++;
		}
		printf("testing supply count on duchy cards: ");
		if(Gafter.supplyCount[duchy] == Gbefore.supplyCount[duchy]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of duchy cards\n", player);
			errorCount++;
		}
		printf("testing supply count on province cards: ");
		if(Gafter.supplyCount[province] == Gbefore.supplyCount[province]) printf("TEST SUCCESSFULLY COMPLETED.\n");
		else{
			printf("TEST FAILED: player %d's adventurer card incorrectly changed count of province cards\n", player);
			errorCount++;
		}
		
		printf("\nTEST FAILURES: ('n/a' means did not exit in original gameState)\n");
		printf("TEST #	PLAYER #	VARIABLE		INTENDED VALUE	TEST VALUE\n");
				
		for (int player = 0; player < Gafter.numPlayers; player++) {
			Gafter.whoseTurn = player;
			Gafter.numActions = 1;
			Gbefore.coins = 0;
			for (int j = 0; j < Gbefore.handCount[player]; j++) {
				if (Gbefore.hand[player][j] == copper)
					Gbefore.coins += 1;
				else if (Gbefore.hand[player][j] == silver)
					Gbefore.coins += 2;
				else if (Gbefore.hand[player][j] == gold)
					Gbefore.coins += 3;
			}
			
			if (i < 1000 / 3) {
				bonus = 0;
				for (int j = Gbefore.deckCount[player]; j >= Gbefore.deckCount[player] - 2; --j) {
					if (Gbefore.deck[player][j] == copper)
						bonus += 1;
					else if (Gbefore.deck[player][j] == silver)
						bonus += 2;
					else if (Gbefore.deck[player][j] == gold)
						bonus += 3;
				}
				playCard(stewardHandPos[player], 1, choice2[player], choice3[player], &Gafter); 
				if (Gafter.handCount[player] != Gbefore.handCount[player] + 1){
					printf("TEST 1	player %d	hand count		%d				%d\n", player, Gbefore.handCount[player] + 1, Gafter.handCount[player]);
					errorCount++;
				}
				if (Gbefore.deckCount[player] >= 2) {
					if (Gafter.discardCount[player] != Gbefore.discardCount[player] + 1){
						printf("TEST 1	player %d	discard count	%d				%d\n", player, Gbefore.discardCount[player] + 1, Gafter.discardCount[player]);
						errorCount++;
					}
				}
				else {
					if (Gafter.discardCount[player] != 1) {
						printf("TEST 1	player %d	discard count 	%d				%d\n", player, 1, Gafter.discardCount[player]);
						errorCount++;
					}
				}
					
				if (Gbefore.deckCount[player] >= 2) { 	
					if (Gafter.deckCount[player] != Gbefore.deckCount[player] - 2){
						printf("TEST 1 	player %d	deck count		%d				%d\n", player, Gbefore.deckCount[player] - 2, Gafter.deckCount[player]);
						errorCount++;
					}
					for (int j = 0; j < Gbefore.deckCount[player] - 2; j++)
						if (Gbefore.deck[player][j] != Gafter.deck[player][j]){
							printf("TEST 1	player %d	deck[%d]		%d				%d\n", player, j, Gbefore.deck[player][j], Gafter.deck[player][j]);
							errorCount++;
						}
				}
				else
					if (Gafter.deckCount[player] != Gbefore.deckCount[player] + Gbefore.discardCount[player] - 2){
						printf("TEST 1	player %d	deck count 	%d			%d\n", player, Gbefore.deckCount[player] + Gbefore.discardCount[player] - 2, Gafter.deckCount[player]);
						errorCount++;
					}
				if (Gbefore.deckCount[player] >= 2) {
					for (int j = 0, flag; j < Gafter.handCount[player]; j++) {
						flag = 0;
						for (int l = 0; l < Gbefore.handCount[player]; l++) {
							if (Gafter.hand[player][j] == Gbefore.hand[player][l]) {
								Gbefore.hand[player][l] = -1;
								flag = 1;
								break;
							}
						}
						if (!flag) {
							if (Gafter.hand[player][j] == Gbefore.deck[player][Gbefore.deckCount[player]-1]) 
								Gbefore.deck[player][Gbefore.deckCount[player]-1] = -1;
							else if (Gafter.hand[player][j] == Gbefore.deck[player][Gbefore.deckCount[player]-2]) 
								Gbefore.deck[player][Gbefore.deckCount[player]-2] = -1;
							else{
								printf("TEST 1 	player %d	hand[%d]		n/a				%d\n", player, j, Gafter.hand[player][j]);
								errorCount++;
							}
						}
					}
				}

				if (Gafter.discardCount[player] > Gbefore.discardCount[player]) {
					for (int j = 0; j < Gbefore.discardCount[player]; j++)
						if (Gbefore.discard[player][j] != Gafter.discard[player][j]){
							printf("TEST 1	player %d	discard[%d]		%d				%d\n", player, j, Gbefore.discard[player][j], Gafter.discard[player][j]);
							errorCount++;
						}
				}
				if (Gafter.discard[player][Gafter.discardCount[player] - 1] != steward){
						printf("TEST 1	player %d	discard[%d]		%d				%d\n", player, Gafter.discardCount[player] - 1, steward, Gafter.discard[player][Gafter.discardCount[player] -1]);
						errorCount++;
				}	
				if (Gafter.coins != Gbefore.coins + bonus){
					printf("TEST 1	player %d	coin count		%d				%d\n", player, Gbefore.coins + bonus, Gafter.coins);
					errorCount++;
				}
				if (Gafter.numActions != 0){
					printf("TEST 1	player %d	# of actions	%d				%d\n", player, 0, Gafter.numActions);
					errorCount++;
				}
			}


			else if (i < 2 * 1000 / 3) {
				bonus = 2;
				playCard(stewardHandPos[player], 2, choice2[player], choice3[player], &Gafter); 

				if (Gafter.deckCount[player] != Gbefore.deckCount[player]){
					printf("TEST 2	player %d	deck count		%d				%d\n", player, Gbefore.deckCount[player], Gafter.deckCount[player]);
					errorCount++;
				}
				if (Gafter.handCount[player] != Gbefore.handCount[player] - 1){
					printf("TEST 2	player %d	hand count		%d				%d\n", player, Gbefore.handCount[player] - 1, Gafter.handCount[player]);
					errorCount++;
				}
				if (Gafter.discardCount[player] != Gbefore.discardCount[player] + 1){
					printf("TEST 2	player %d	discard count	%d				%d\n", player, Gbefore.discardCount[player] + 1, Gafter.discardCount[player]);
					errorCount++;
				}
				for (int j = 0; j < Gbefore.deckCount[player]; j++){
					if (Gbefore.deck[player][j] != Gafter.deck[player][j]){
						printf("TEST 2	player %d	deck[%d]		%d				%d\n", player, j, Gbefore.deck[player][j], Gafter.deck[player][j]);
						errorCount++;
					}
				}
				for (int j = 0, flag; j < Gafter.handCount[player]; j++) {
					flag = 0;
					for (int l = 0; l < Gbefore.handCount[player]; l++) {
						if (Gafter.hand[player][j] == Gbefore.hand[player][l]) {
							Gbefore.hand[player][l] = -1;
							flag = 1;
							break;
						}
					}
					if (!flag){
						printf("TEST 2	player %d	hand[%d]		n/a				%d\n", player, j, Gafter.hand[player][j]);
						errorCount++;
					}
				}

				for (int j = 0; j < Gbefore.discardCount[player]; j++)
					if (Gbefore.discard[player][j] != Gafter.discard[player][j]){
						printf("TEST 2	player %d	discard[%d]		%d				%d\n", player, j, Gbefore.discard[player][j], Gafter.discard[player][j]);
						errorCount++;
					}
				if (Gafter.discard[player][Gbefore.discardCount[player]] != steward){
					printf("TEST 2	player %d	discard[%d]		%d				%d\n", player, Gbefore.discardCount[player], steward, Gafter.discard[player][Gbefore.discardCount[player]]);
					errorCount++;
				}
				if (Gafter.coins != Gbefore.coins + bonus){
					printf("TEST 2	player %d	coin count		%d				%d\n", player, Gbefore.coins + bonus, Gafter.coins);
					errorCount++;
				}
				if (Gafter.numActions != 0){
					printf("TEST 2	player %d	# of actions	%d				%d\n", player, 0, Gafter.numActions);
					errorCount++;
				}
			}


			else {
				numDiscard = 1;

				if (choice2[player] < Gbefore.handCount[player]) numDiscard++;
				if (choice3[player] < Gbefore.handCount[player]) numDiscard++;

				if (choice2[player] < Gbefore.handCount[player]) {
					if (Gbefore.hand[player][choice2[player]] == copper)
						Gbefore.coins -= 1;
					else if (Gbefore.hand[player][choice2[player]] == silver)
						Gbefore.coins -= 2;
					else if (Gbefore.hand[player][choice2[player]] == gold)
						Gbefore.coins -= 3;
				}
				if (choice3[player] < Gbefore.handCount[player]) {
					if (Gbefore.hand[player][choice3[player]] == copper)
						Gbefore.coins -= 1;
					else if (Gbefore.hand[player][choice3[player]] == silver)
						Gbefore.coins -= 2;
					else if (Gbefore.hand[player][choice3[player]] == gold)
						Gbefore.coins -= 3;
				}

				playCard(stewardHandPos[player], 3, choice2[player], choice3[player], &Gafter);
				if (Gafter.deckCount[player] != Gbefore.deckCount[player]){
					printf("TEST 3	player %d	deck count		%d				%d\n", player, Gbefore.deckCount[player], Gafter.deckCount[player]);
					errorCount++;
				}
				if (Gafter.handCount[player] != Gbefore.handCount[player] - numDiscard){
					printf("TEST 3	player %d	hand count		%d				%d\n", player, Gbefore.handCount[player] - numDiscard, Gafter.handCount[player]);
					errorCount++;
				}
				if (Gafter.discardCount[player] != Gbefore.discardCount[player] + 1){
					printf("TEST 3	player %d	discard count	%d				%d\n", player, Gbefore.discardCount[player] + 1, Gafter.discardCount[player]);
					errorCount++;
				}
				for (int j = 0; j < Gbefore.deckCount[player]; j++) {
					if (Gbefore.deck[player][j] != Gafter.deck[player][j]){
						printf("TEST 3	player %d	deck[%d]		%d				%d\n", player, j, Gbefore.deck[player][j], Gafter.deck[player][j]);
						errorCount++;
					}
				}
				for (int j = 0; j < Gbefore.discardCount[player]; j++) {
					if (Gbefore.discard[player][j] != Gafter.discard[player][j]){
						printf("TEST 3	player %d	discard[%d]		%d				%d\n", player, j, Gbefore.discard[player][j], Gafter.discard[player][j]);
						errorCount++;
					}
				}
				if (Gafter.discard[player][Gafter.discardCount[player] - 1] != steward){
					printf("TEST 3	player %d	discard[%d]		%d				%d\n", player, Gafter.discardCount[player] - 1, steward, Gafter.discard[player][Gbefore.discardCount[player] - 1]);
					errorCount++;
				}
				if (Gafter.coins != Gbefore.coins ) {
					printf("TEST 3	player %d	coin count		%d				%d\n", player, Gbefore.coins , Gafter.coins);
					errorCount++;
				}
				if (Gafter.numActions != 0){
					printf("TEST 3	player %d	# of actions	%d				%d\n", player, 0, Gafter.numActions);
					errorCount++;
				}
				for (int j = 0, flag; j < Gafter.handCount[player]; j++) {
					flag = 0;
					for (int l = 0; l < Gbefore.handCount[player]; l++) {
						if (Gafter.hand[player][j] == Gbefore.hand[player][l]) {
							Gbefore.hand[player][l] = -1;
							flag = 1;
							break;
						}
					}
					if (!flag){
						printf("TEST 3	player %d	hand[%d]		n/a				%d\n", player, j, Gafter.hand[player][j]);
						errorCount++;
					}
				}
			}
		}
	}
	
	printf("\nOut of 1000 rounds of random testing, steward card produced %d errors.\n", errorCount);
	printf("Note that number of errors are not limited to 1 per round.\n");
		
	printf("******end random testing on steward card******\n");
	return 0;
}