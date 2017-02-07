#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main() {

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int player, numDiscard, choice2[4], choice3[4], seed, stewardHandPos[4], bonus;

	struct gameState Gbefore, Gafter;

	srand(time(NULL));
	printf("Running Random Card Test for Steward...\n");
	printf("Option 1: draw 2 cards | Optoin 2: gain 2 coins | Option 3: discard 2 cards\n\n");

	for (int i = 0; i < 1000; i++) {

		seed = rand();		//pick random seed	
		initializeGame(4, k, seed, &Gafter);	//initialize Gamestate
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
				if (Gafter.handCount[player] != Gbefore.handCount[player] + 1)
					printf("OPTION 1 FAILED FOR PLAYER %d: handCount should be %d but it is %d.\n", player, Gbefore.handCount[player] + 1, Gafter.handCount[player]);

				if (Gbefore.deckCount[player] >= 2) {
					if (Gafter.discardCount[player] != Gbefore.discardCount[player] + 1)
						printf("OPTION 1 FAILED FOR PLAYER %d: discardCount should be %d but it is %d.\n", player, Gbefore.discardCount[player] + 1, Gafter.discardCount[player]);
				}
				else {
					if (Gafter.discardCount[player] != 1) {
						printf("OPTION 1 FAILED FOR PLAYER %d: discardCount should be %d but it is %d.\n", player, 1, Gafter.discardCount[player]);
					}
				}
					
				if (Gbefore.deckCount[player] >= 2) { 	
					if (Gafter.deckCount[player] != Gbefore.deckCount[player] - 2)
						printf("OPTION 1 FAILED FOR PLAYER %d: deckCount should be %d but it is %d.\n", player, Gbefore.deckCount[player] - 2, Gafter.deckCount[player]);
					for (int j = 0; j < Gbefore.deckCount[player] - 2; j++)
						if (Gbefore.deck[player][j] != Gafter.deck[player][j])
							printf("OPTION 1 FAILED FOR PLAYER %d: deck[%d] should be %d but is %d.\n", player, j, Gbefore.deck[player][j], Gafter.deck[player][j]);
				}
				else
					if (Gafter.deckCount[player] != Gbefore.deckCount[player] + Gbefore.discardCount[player] - 2)
						printf("2TEST 1 FAILURE FOR PLAYER %d: deckCount should be %d but it is %d.\n", player, Gbefore.deckCount[player] + Gbefore.discardCount[player] - 2, Gafter.deckCount[player]);

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
							else
								printf("OPTION 1 FAILED FOR PLAYER %d: hand[%d] is %d but cannot find that card in previous hand.\n", player, j, Gafter.hand[player][j]);
						}
					}
				}

				if (Gafter.discardCount[player] > Gbefore.discardCount[player]) {
					for (int j = 0; j < Gbefore.discardCount[player]; j++)
						if (Gbefore.discard[player][j] != Gafter.discard[player][j])
							printf("OPTION 1 FAILED FOR PLAYER %d: discard[%d] should be %d but is %d.\n", player, j, Gbefore.discard[player][j], Gafter.discard[player][j]);
				}
				if (Gafter.discard[player][Gafter.discardCount[player] - 1] != steward)
						printf("OPTION 1 FAILED FOR PLAYER %d: discard[%d] should be %d but is %d.\n", player, Gafter.discardCount[player] - 1, steward, Gafter.discard[player][Gafter.discardCount[player] -1]);

	
				if (Gafter.coins != Gbefore.coins + bonus)
					printf("OPTION 1 FAILED FOR PLAYER %d: Coins should be %d but are %d.\n", player, Gbefore.coins + bonus, Gafter.coins);
				if (Gafter.numActions != 0)
					printf("OPTION 1 FAILED FOR PLAYER %d: numActions should be %d but are %d.\n", player, 0, Gafter.numActions);
			}


			else if (i < 2 * 1000 / 3) {
				bonus = 2;
				playCard(stewardHandPos[player], 2, choice2[player], choice3[player], &Gafter); 

				if (Gafter.deckCount[player] != Gbefore.deckCount[player])
					printf("TEST 2 FAILURE FOR PLAYER %d: deckCount should be %d but it is %d.\n", player, Gbefore.deckCount[player], Gafter.deckCount[player]);
				if (Gafter.handCount[player] != Gbefore.handCount[player] - 1)
					printf("TEST 2 FAILURE FOR PLAYER %d: handCount should be %d but it is %d.\n", player, Gbefore.handCount[player] - 1, Gafter.handCount[player]);
				if (Gafter.discardCount[player] != Gbefore.discardCount[player] + 1)
					printf("TEST 2 FAILURE FOR PLAYER %d: discardCount should be %d but it is %d.\n", player, Gbefore.discardCount[player] + 1, Gafter.discardCount[player]);

				for (int j = 0; j < Gbefore.deckCount[player]; j++)
					if (Gbefore.deck[player][j] != Gafter.deck[player][j])
						printf("TEST 2 FAILURE FOR PLAYER %d: deck[%d] should be %d but is %d.\n", player, j, Gbefore.deck[player][j], Gafter.deck[player][j]);

				for (int j = 0, flag; j < Gafter.handCount[player]; j++) {
					flag = 0;
					for (int l = 0; l < Gbefore.handCount[player]; l++) {
						if (Gafter.hand[player][j] == Gbefore.hand[player][l]) {
							Gbefore.hand[player][l] = -1;
							flag = 1;
							break;
						}
					}
					if (!flag)
						printf("TEST 2 FAILURE FOR PLAYER %d: hand[%d] is %d but cannot find that card in previous hand.\n", player, j, Gafter.hand[player][j]);
				}

				for (int j = 0; j < Gbefore.discardCount[player]; j++)
					if (Gbefore.discard[player][j] != Gafter.discard[player][j])
						printf("TEST 2 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", player, j, Gbefore.discard[player][j], Gafter.discard[player][j]);

				if (Gafter.discard[player][Gbefore.discardCount[player]] != steward)
						printf("TEST 2 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", player, Gbefore.discardCount[player], steward, Gafter.discard[player][Gbefore.discardCount[player]]);

	
				if (Gafter.coins != Gbefore.coins + bonus)
					printf("TEST 2 FAILURE FOR PLAYER %d: Coins should be %d but are %d.\n", player, Gbefore.coins + bonus, Gafter.coins);
				if (Gafter.numActions != 0)
					printf("TEST 2 FAILURE FOR PLAYER %d: numActions should be %d but are %d.\n", player, 0, Gafter.numActions);
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


				if (playCard(stewardHandPos[player], 3, choice2[player], choice3[player], &Gafter) < 0) {
					printf("playCard() failed on iteration %d, player %d, for TEST 3.\n", i, player);
					exit(EXIT_FAILURE);
				}

				if (Gafter.deckCount[player] != Gbefore.deckCount[player])
					printf("TEST 3 FAILURE FOR PLAYER %d: deckCount should be %d but it is %d.\n", player, Gbefore.deckCount[player], Gafter.deckCount[player]);
				if (Gafter.handCount[player] != Gbefore.handCount[player] - numDiscard)
					printf("TEST 3 FAILURE FOR PLAYER %d: handCount should be %d but it is %d.\n", player, Gbefore.handCount[player] - numDiscard, Gafter.handCount[player]);
				if (Gafter.discardCount[player] != Gbefore.discardCount[player] + 1){
					printf("TEST 3 FAILURE FOR PLAYER %d: discardCount should be %d but it is %d.\n", player, Gbefore.discardCount[player] + 1, Gafter.discardCount[player]);

printf("originalCount: %d, choice2: %d %d, choice3: %d %d, stewardPos: %d\n", Gbefore.handCount[player], choice2[player], Gbefore.hand[player][choice2[player]], choice3[player], Gbefore.hand[player][choice3[player]], stewardHandPos[player]);
}
				for (int j = 0; j < Gbefore.deckCount[player]; j++) {
					if (Gbefore.deck[player][j] != Gafter.deck[player][j])
						printf("TEST 3 FAILURE FOR PLAYER %d: deck[%d] should be %d but is %d.\n", player, j, Gbefore.deck[player][j], Gafter.deck[player][j]);
				}
				for (int j = 0; j < Gbefore.discardCount[player]; j++) {
					if (Gbefore.discard[player][j] != Gafter.discard[player][j])
						printf("TEST 3 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", player, j, Gbefore.discard[player][j], Gafter.discard[player][j]);
				}

				if (Gafter.discard[player][Gafter.discardCount[player] - 1] != steward)
						printf("TEST 3 FAILURE FOR PLAYER %d: discard[%d] should be %d but is %d.\n", player, Gafter.discardCount[player] - 1, steward, Gafter.discard[player][Gbefore.discardCount[player] - 1]);

				if (Gafter.coins != Gbefore.coins ) {
					printf("TEST 3 FAILURE FOR PLAYER %d: Coins should be %d but are %d.\n", player, Gbefore.coins , Gafter.coins);
				}
				if (Gafter.numActions != 0)
					printf("TEST 3 FAILURE FOR PLAYER %d: numActions should be %d but are %d.\n", player, 0, Gafter.numActions);

				for (int j = 0, flag; j < Gafter.handCount[player]; j++) {
					flag = 0;
					for (int l = 0; l < Gbefore.handCount[player]; l++) {
						if (Gafter.hand[player][j] == Gbefore.hand[player][l]) {
							Gbefore.hand[player][l] = -1;
							flag = 1;
							break;
						}
					}
					if (!flag)
						printf("TEST 3 FAILURE FOR PLAYER %d: hand[%d] is %d but cannot find that card in previous hand.\n", player, j, Gafter.hand[player][j]);
				}
			}
		}
	}

	printf("\nTests Complete\n");
	return 0;
}